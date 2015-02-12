################################################################################
#
# Project manager class
#
################################################################################

from scons import devices
from SCons.Script import *

import glob

# simple type collecting project specific data
class Project:

	def __init__(self, name):
		self.ccflags   = ''
		self.cxxflags  = ''
		self.linkflags = ''

		self.includepaths = list()
		self.userincludepaths = list()
		self.dependencies = list()

		self.libs = list()
		self.libpaths = list()

		self.srcdirs = list()

		self.devices = devices.list

		self.name = name
		self.basename = os.path.basename(name)

		self.isLibrary = False

		self.simavr = False

	def SConscriptPath(self):
		return '#/src/' + self.name + '/SConscript'

# the project manager is responsible for keeping track of every project, its
# settings, and for setting up the build environment
class ProjectManager:

	def __init__(self, env, devices):
		self.env = env
		self.devices = devices
		self.projects = dict()

	# add a project to the manager
	def AddProject(self, name):
		for device in self.devices:
			project = device + '/' + name

			# add project only if not already in the list
			if not project in self.projects:
				self.projects[project] = Project(name)
				SConscript(self.projects[project].SConscriptPath(), exports=['project', 'device'])

	# set the devices a project supports
	def SetSupportedDevices(self, project, devices):
		self.projects[project].devices = devices

	# add project specific CCFLAGS
	def AppendCCFlags(self, project, flags):
		self.projects[project].ccflags += flags

	# add project specific CXXFLAGS
	def AppendCXXFlags(self, project, flags):
		self.projects[project].cxxflags += flags

	# add project specific LINKFLAGS
	def AppendLinkFlags(self, project, flags):
		self.projects[project].linkflags += flags

	# change project to library project
	def IsLibrary(self, project):
		self.projects[project].isLibrary = True

	# add an include path to the project
	def AddIncludePath(self, project, path):
		self.projects[project].includepaths.append(path)

	# use this to specify include paths needed to use a library
	def AddUserIncludePath(self, project, path):
		self.projects[project].userincludepaths.append(path)

	# add a lib path to the project
	def AddLibPath(self, project, path):
		self.projects[project].libpaths.append(path)

	# add a lib to the project
	def AddLib(self, project, lib):
		self.projects[project].libs.append(lib)

	# add a source directory to the project (path relative to SConscript)
	def AddSrcDir(self, project, path):
		self.projects[project].srcdirs.append(path)

	# specify a library this project depends on
	def DependsOn(self, project, device, dependency):
		dep = device + '/' + dependency

		# add dependency as new project if it is not in the list yet
		if not dep in self.projects:
			self.AddProject(dependency)

		# dependency must be a library
		if not self.projects[dep].isLibrary:
					raise Exception('Dependecies must be libraries!')

		self.projects[project].dependencies.append(dep)

	# add dependency to simavr
	def DependsOnSimavr(self, project):
		self.projects[project].simavr = True


	#sets up the build for a given project
	def BuildProject(self, project, device):

		p = self.projects[project]

		# build only if current device is supported by the project
		if device in p.devices:

			base_builddir = '#/build/' + device
			objbuilddir   = base_builddir + '/obj/' + p.name
			libinstalldir = base_builddir + '/lib/'
			bininstalldir = base_builddir + '/bin/'

			# create a new local environment to setup the build
			localenv = self.env.Clone()

			# setup the environment
			localenv.Append(CPPPATH = p.includepaths)

			localenv.Append(CCFLAGS   = ' -mmcu=' + device)
			localenv.Append(LINKFLAGS = ' -mmcu=' + device)

			localenv.Append(CCFLAGS   = p.ccflags)
			localenv.Append(CXXFLAGS  = p.cxxflags)
			localenv.Append(LINKFLAGS = p.linkflags)

			localenv.Append(LIBS      = p.libs)
			localenv.Append(LIBPATHS  = p.libpaths)

			# add dependencies
			for dep in p.dependencies:
				localenv.Append(LIBS    = self.projects[dep].name)
				localenv.Append(LIBPATH = '#/build/' + device + '/obj/' + self.projects[dep].name)
				localenv.Append(CPPPATH = self.projects[dep].userincludepaths)

			# check for simavr
			if p.simavr:
				localenv.ParseConfig('pkg-config --cflags simavr')

			#specify the build directory
			localenv.VariantDir(objbuilddir, ".", duplicate=0)

			# add sources
			srclst =  map(lambda x: objbuilddir + '/' + x, glob.glob('*.cpp'))
			srclst += map(lambda x: objbuilddir + '/' + x, glob.glob('*.c'))

			for directory in p.srcdirs:
				srclst += map(lambda x: objbuilddir + '/' + x, glob.glob(directory + '/*.cpp'))
				srclst += map(lambda x: objbuilddir + '/' + x, glob.glob(directory + '/*.c'))

			# build it
			if p.isLibrary:
				target = objbuilddir + '/lib' + p.basename + '.a'
				out = localenv.StaticLibrary(target, source=srclst)
				out = localenv.Install(libinstalldir, out)
			else:
				target = objbuilddir + '/' + p.basename + '.elf'
				out = localenv.Program(target, source=srclst)
				out = localenv.Install(bininstalldir, out)

				src = target
				target = objbuilddir + '/' + p.basename + '.hex'
				tmp = localenv.Command(target, out, 'avr-objcopy -j .text -j .data -O ihex $SOURCE $TARGET')
				localenv.Install(bininstalldir, tmp)

			# show memory usage
			if localenv['memusage']:
				target = objbuilddir + '/' + p.basename + '.size'
				localenv.Command( target, out, 'avr-size ${SOURCE} | tee ${TARGET}')
