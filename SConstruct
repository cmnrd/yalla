################################################################################
#
# SConstruct
#
# based on the example at http://www.scons.org/wiki/SconstructMultipleRefactored
#
################################################################################

# avoid creation of *.pyc files in the source tree
import sys
sys.dont_write_bytecode = True

from SCons.Script.SConscript import SConsEnvironment
import glob
import os
import config
import message
import supported_devices

################################################################################
#
# Variable settings
#
################################################################################

# read variables from command line or SConfig file
vars = Variables('SConfig')

vars.Add(ListVariable('devices',
                      'specify the target devices',
                      'all',
                       supported_devices.list))

vars.Add(BoolVariable('verbose', 'print full gcc comands', 0))

################################################################################
#
# Build manager class
#
################################################################################

#this is our catch-all Dev class
#it keeps track of all the variables and common functions we need
class Dev:
	ccflags = ''
	cxxflags = ''
	linkflags = ''
	device = ''
	libpath = ''
	libs = ''

	#---
	# sets up the sconscript file for a given sub-project
	def Subproject(self, project):
		SConscript(env.jDev.SPath('src/' + project), exports=['project'])

	def AddLibrary(self, libraryProject):
		self.libpath += '#/build/' + self.device + '/yalla'
		self.libs += os.path.basename(libraryProject)

	#sets up the build for a given project
	def BuildProgram(self, localenv, project):

		buildroot = '#/build/' + self.device
		builddir = buildroot + '/' + project
		targetpath = builddir + '/' + os.path.basename(project) + '.elf'
		libyallapath = buildroot + '/yalla'

		#append device specific settings
		localenv.Append(CPPPATH = ['#/include/yalla/device/' + self.device])
		localenv.Append(CCFLAGS=' -mmcu=' + self.device)
		localenv.Append(LINKFLAGS=' -mmcu=' + self.device)

		#append the user's additional compile flags
		#assume ccflags and cxxflags are defined
		localenv.Append(CCFLAGS=self.ccflags)
		localenv.Append(CXXFLAGS=self.cxxflags)
		localenv.Append(LINKFLAGS=self.linkflags)
		localenv.Append(LIBPATH = self.libpath)
		localenv.Append(LIBS = self.libs)

		#specify the build directory
		localenv.VariantDir(builddir, ".", duplicate=0)

		srclst = map(lambda x: builddir + '/' + x, glob.glob('*.cpp'))
		srclst += map(lambda x: builddir + '/' + x, glob.glob('*.c'))

		pgm = localenv.Program(targetpath, source=srclst)
		env.Alias('all', pgm)  #note: not localenv

	def BuildLibrary(self, localenv, project):

		buildroot = '#' + 'build/' + self.device
		builddir = buildroot + '/' + project
		targetpath = builddir + '/lib' + os.path.basename(project) + '.a'

		#append device specific settings
		localenv.Append(CPPPATH = ['#/include/yalla/device/' + self.device])
		localenv.Append(CCFLAGS=' -mmcu=' + self.device)
		localenv.Append(LINKFLAGS=' -mmcu=' + self.device)

		#append the user's additional compile flags
		#assume ccflags and cxxflags are defined
		localenv.Append(CCFLAGS=self.ccflags)
		localenv.Append(CXXFLAGS=self.cxxflags)
		localenv.Append(LINKFLAGS=self.linkflags)

		#specify the build directory
		localenv.VariantDir(builddir, ".", duplicate=0)

		srclst = map(lambda x: builddir + '/' + x, glob.glob('*.cpp'))
		srclst += map(lambda x: builddir + '/' + x, glob.glob('*.c'))

		pgm = localenv.StaticLibrary(targetpath, source=srclst)
		env.Alias('all', pgm)  #note: not localenv

	#---- PRIVATE ----

	#---
	# return the sconscript path to use
	def SPath(self, project):
		return project + '/SConscript'

################################################################################
#
# Create the envrionment
#
################################################################################

env = Environment(variables = vars)

# Generate help text for variables
Help(vars.GenerateHelpText(env))

# put all .sconsign files in one place
env.SConsignFile()

# override the default build tools
env['CC']  = 'avr-gcc'
env['CXX'] = 'avr-gcc'
env['AR']  = 'avr-gcc-ar'
env['RANLIB']  = 'avr-gcc-ranlib'

# set build flags
env['CCFLAGS']   = config.ccflags
env['CXXFLAGS']  = config.cxxflags
env['LINKFLAGS'] = config.linkflags

# look for simavr
env.ParseConfig( 'pkg-config --cflags simavr' )

# add include path
env.Append(CPPPATH = ['#/include/yalla'])

# set messages
if env['verbose'] == 0:
	env['CCCOMSTR']     = message.compile_source
	env['CXXCOMSTR']    = message.compile_source
	env['ARCOMSTR']     = message.link_library
	env['LINKCOMSTR']   = message.link_program
	env['RANLIBCOMSTR'] = message.ranlib_library

#we can put variables right into the environment, however
#we must watch out for name clashes.
SConsEnvironment.jDev = Dev()

# make sure the sconscripts can get to the variables
# don't need to export anything but 'env'
Export('env')

################################################################################
#
# Build it!
#
################################################################################

# build for every device specified in the list
for device in env['devices']:
	env.jDev.device = device

	# setup the yalla library seperately
	env.jDev.Subproject('yalla')

	# specify all of the sub-projects in the section
	env.jDev.Subproject('test/avr/iomm')
	env.jDev.Subproject('test/avr/register')
