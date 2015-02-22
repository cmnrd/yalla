################################################################################
#
# Project manager class
#
################################################################################

from SCons.Script import *

import glob

from scons.buildconfig import BuildConfig

class Project:
	def __init__(self, name, env, variant, device):
		self.name      = name
		self.isLibrary = False
		self.config    = BuildConfig()
		self.srcdirs   = ['.']
		self.env       = env
		self.variant   = variant
		self.device    = device
		self.dependencies = []

		self.config.cpppath  = ['#/include/' + name]
		self.config.cpppath += ['#/include/' + name + '/device/' + device]


# the project manager is responsible for keeping track of every project, its
# settings, and for setting up the build environment
class ProjectManager:

	def __init__(self, env, projects, devices, variants):
		self.globalEnv = env
		self.projects  = projects
		self.devices   = devices
		self.variants  = variants

	def SConscriptPath(self, project):
		return '#/src/' + project + '/SConscript'

	def __BuildAllProjects(self, deviceEnv, variant, device):
		for p in self.projects:
			env = deviceEnv.Clone()
			project = Project(p, env, variant, device)
			SConscript(self.SConscriptPath(p), exports=['project'])

	def __BuildAllDevices(self, variantEnv, variant):
		for device in self.devices:

			deviceEnv = variantEnv.Clone()

			# set mcu
			deviceEnv.Append(CPPDEFINES = ['MCU=\\\"' + device + '\\\"'])
			deviceEnv.Append(CFLAGS = ['-mmcu=' + device])
			deviceEnv.Append(CXXFLAGS = ['-mmcu=' + device])
			deviceEnv.Append(LINKFLAGS = ['-mmcu=' + device])

			self.__BuildAllProjects(deviceEnv, variant, device)

	def __BuildAllVariants(self):
		for variant in self.variants:
			variantEnv = self.globalEnv.Clone()
			self.variants[variant].AppendToEnvironment(variantEnv)
			self.__BuildAllDevices(variantEnv, variant)

	def BuildAll(self):
		self.__BuildAllVariants()

	def __ResolveDependencies(self, project):
		env = project.env

		for dep in project.dependencies:
			env.Append(CPPPATH = ['#/include/' + dep])
			env.Append(CPPPATH = ['#/include/' + dep + '/device/' + project.device])

			env.Append(LIBPATH = ['#/build.' + project.variant + '/' + project.device + '/lib/' + os.path.dirname(dep)])
			env.Append(LIBS = [dep])

	def BuildProject(self, project):

		env = project.env

		# set the build dir
		builddir = '#/build.' + project.variant + '/' + project.device + '/obj/' + project.name
		libdir   = '#/build.' + project.variant + '/' + project.device + '/lib/' + os.path.dirname(project.name)
		bindir   = '#/build.' + project.variant + '/' + project.device + '/bin/' + os.path.dirname(project.name)
		env.VariantDir(builddir, '.', duplicate=0)

		# append project configuration
		project.config.AppendToEnvironment(env)
		self.__ResolveDependencies(project)

		# add sources
		srclist = list()
		for directory in project.srcdirs:
			srclist += map(lambda x: builddir + '/' + x, glob.glob(directory + '/*.cpp'))
			srclist += map(lambda x: builddir + '/' + x, glob.glob(directory + '/*.c'))

		# Build it!
		if project.isLibrary:
			target = builddir + '/lib' + os.path.basename(project.name) + '.a'
			build = env.StaticLibrary(target, source=srclist)
			install = env.Install(libdir, build)
		else:
			target = builddir + '/' + os.path.basename(project.name) + '.elf'
			build = env.Program(target, source=srclist)
			install = env.Install(bindir, build)

			# create hex file
			target = builddir + '/' + os.path.basename(project.name) + '.hex'
			tmp = env.Command(target, build, 'avr-objcopy -j .text -j .data -O ihex $SOURCE $TARGET')
			env.Install(bindir, tmp)

			# add a simavr target
			if project.variant == 'sim':
				simavr = env.Command('#.scons/simavr/' + project.device + '/' + project.name, install, 'simavr ${SOURCE} -f ' + str(env['frequency']))
				env.Alias('simavr/' + project.device + '/' + project.name, simavr)

		if env['memusage']:
			memsize = env.Command(None, build, 'avr-size ${SOURCE}')
			env.Depends(install, memsize)
