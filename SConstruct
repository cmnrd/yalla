# based on the example at http://www.scons.org/wiki/SconstructMultipleRefactored

from SCons.Script.SConscript import SConsEnvironment
import glob
import sys
import os

#list of all supported devices
all_supported_devices = ['atmega8']

colors = {}
colors['white']  = '\033[97m'
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['bold']   = '\033[1m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

#this is our catch-all Dev class
#it keeps track of all the variables and common functions we need
class Dev:
  ccflags = ''
  cxxflags = ''
  linkflags = ''
  device = ''

  #---
  # sets up the sconscript file for a given sub-project
  def Subproject(self, project):
      SConscript(env.jDev.SPath('src/' + project), exports=['project'])

  #sets up the build for a given project
  def Buildit(self, localenv, project, islib = False):

     buildroot = '#' + 'build/' + self.device
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


     localenv.Append(LIBPATH = [libyallapath])
     localenv.Append(LIBS = ['yalla'])


     #specify the build directory
     localenv.VariantDir(builddir, ".", duplicate=0)

     srclst = map(lambda x: builddir + '/' + x, glob.glob('*.cpp'))
     srclst += map(lambda x: builddir + '/' + x, glob.glob('*.c'))

     pgm = localenv.Program(targetpath, source=srclst)
     env.Alias('all', pgm)  #note: not localenv

  #---- PRIVATE ----

  #---
  # return the sconscript path to use
  def SPath(self, project):
     return project + '/SConscript'

env = Environment()

#put all .sconsign files in one place
env.SConsignFile()

#we can put variables right into the environment, however
#we must watch out for name clashes.
SConsEnvironment.jDev = Dev()
SConsEnvironment.all_supported_devices = all_supported_devices

# read the mcu from command line or SConfig file
vars = Variables('SConfig')
vars.Add(ListVariable('devices',
                      'specify the target devices',
                      'all',
                       all_supported_devices))

vars.Add(BoolVariable('verbose', 'print full gcc comands', 0))
env = Environment(variables = vars)
Help(vars.GenerateHelpText(env))

ccflags = ''
cxxflags = ''
linkflags = ''

#avr specific flags
ccflags += ' -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums'

#warnings
ccflags += ' -Wall -Wextra'

#optimization
ccflags += ' -Os'

#link time optimization
ccflags += ' -flto'

#strip unused functions
ccflags += ' -ffunction-sections -fdata-sections'

#compile c++ files using the c++11 standard
cxxflags += ' -std=c++11'

#link relaxiation
linkflags += ' -Wl,--relax'

#strip unused functions
linkflags +=  ' -Wl,--gc-sections'

#override the default compiler
env['CC']  = 'avr-gcc'
env['CXX'] = 'avr-gcc'
env['AR']  = 'avr-gcc-ar'
env['RANLIB']  = 'avr-gcc-ranlib'

#set build flags
env['CCFLAGS']   = ccflags
env['CXXFLAGS']  = cxxflags
env['LINKFLAGS'] = linkflags

#look for simavr
env.ParseConfig( 'pkg-config --cflags simavr' )

#add include paths
env.Append(CPPPATH = ['#/include/yalla'])


if env['verbose'] == 0:
  env['CCCOMSTR']     = compile_source_message
  env['CXXCOMSTR']    = compile_source_message
  env['ARCOMSTR']     = link_library_message
  env['LINKCOMSTR']   = link_program_message
  env['RANLIBCOMSTR'] = ranlib_library_message

#make sure the sconscripts can get to the variables
#don't need to export anything but 'env'
Export('env')

for device in env['devices']:
  env.jDev.device = device

  #setup the yalla library seperately
  SConscript('src/yalla/SConscript')

  #specify all of the sub-projects in the section
  env.jDev.Subproject('test/avr/iomm')
  env.jDev.Subproject('test/avr/register')

