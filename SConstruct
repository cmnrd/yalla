################################################################################
#
# SConstruct
#
################################################################################

# avoid creation of *.pyc files in the source tree
import sys
sys.dont_write_bytecode = True

from SCons.Script.SConscript import SConsEnvironment

from scons import config
from scons import message
from scons import devices
from scons import projects
from scons.projectmanager import ProjectManager

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
                       devices.list))

vars.Add(BoolVariable('verbose', 'print full gcc comands', 0))

vars.Add(BoolVariable('memusage', 'print memory usage for every project', 1))

vars.Add(BoolVariable('debug', 'build target for debugging', 0))
vars.Add(BoolVariable('simavr', 'build target for simavr (includes debug)', 0))

vars.Add('gcc',    'path to gcc',    'avr-gcc')
vars.Add('ar',     'path to ar',     'avr-gcc-ar')
vars.Add('ranlib', 'path to ranlib', 'avr-gcc-ranlib')

vars.Add('frequency', 'the target cpu frequency', 8000000)

################################################################################
#
# Create the environment
#
################################################################################

env = Environment(variables = vars)

# Generate help text for variables
Help(vars.GenerateHelpText(env))

# put all .sconsign files in one place
env.SConsignFile()

# override the default build tools
env['CC']     = env['gcc']
env['CXX']    = env['gcc']
env['AR']     = env['ar']
env['RANLIB'] = env['ranlib']

# set build flags
if env['debug'] or env['simavr']:
	env['CCFLAGS']   = config.dbg_ccflags
	env['CXXFLAGS']  = config.dbg_cxxflags
	env['LINKFLAGS'] = config.dbg_linkflags
else:
	env['CCFLAGS']   = config.ccflags
	env['CXXFLAGS']  = config.cxxflags
	env['LINKFLAGS'] = config.linkflags

# set messages
if env['verbose'] == 0:
	env['CCCOMSTR']     = message.compile_source
	env['CXXCOMSTR']    = message.compile_source
	env['ARCOMSTR']     = message.link_library
	env['LINKCOMSTR']   = message.link_program
	env['RANLIBCOMSTR'] = message.ranlib_library
	env['PRINT_CMD_LINE_FUNC'] = message.printCmdLine

# set cpu frequency
env.Append(CPPDEFINES = ['F_CPU=' + str(env['frequency'])])

# construct the project manager and add it to the environment
SConsEnvironment.pm = ProjectManager(env, env['devices'])

# export the environment so SConscripts can access it
Export('env')

################################################################################
#
# Build it!
#
################################################################################

# tell the project manager about every project in the list
# the rest is handled by the SConscripts
for project in projects.list:
	env.pm.AddProject(project)
