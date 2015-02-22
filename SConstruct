################################################################################
#
# SConstruct
#
################################################################################

# avoid creation of *.pyc files in the source tree
import sys
sys.dont_write_bytecode = True

import copy

from SCons.Script.SConscript import SConsEnvironment

from scons.buildconfig    import BuildConfig
from scons.messages       import SetupMessages
from scons.projectmanager import ProjectManager


################################################################################
#
# Variable settings
#
################################################################################

# read variables from command line or SConfig file
vars = Variables('SConfig')

vars.Add(BoolVariable('verbose', 'print full gcc comands', 0))

vars.Add(BoolVariable('memusage', 'print memory usage for every project', 1))

vars.Add('gcc',    'path to gcc',    'avr-gcc')
vars.Add('ar',     'path to ar',     'avr-gcc-ar')
vars.Add('ranlib', 'path to ranlib', 'avr-gcc-ranlib')

vars.Add('frequency', 'the target cpu frequency', 8000000)

################################################################################
#
# Projects
#
################################################################################

projects = []

projects += ['yalla']
projects += ['yalla/test/avr/iomm']
projects += ['yalla/test/avr/register']

################################################################################
#
# Devices
#
################################################################################

devices = []

devices += ['atmega8']

################################################################################
#
# Global build configuration
#
################################################################################

globalConfig = BuildConfig()

# These flags are AVR specific
globalConfig.ccflags += ['-funsigned-char']
globalConfig.ccflags += ['-funsigned-bitfields']
globalConfig.ccflags += ['-fpack-struct']
globalConfig.ccflags += ['-fshort-enums']

# Warnings
globalConfig.ccflags += ['-Wall']
globalConfig.ccflags += ['-Wextra']

# Use C++ 11 standard
globalConfig.cxxflags += ['-std=c++11']

################################################################################
#
# Variants
#
################################################################################

variants = dict()

###################
# Optimized Build #
###################

optConfig = BuildConfig()

# optimization
optConfig.ccflags += ['-Os', '-g1']

# enable link time optimization
optConfig.ccflags += ['-flto']

# strip unused functions
optConfig.ccflags   += ['-ffunction-sections', '-fdata-sections']
optConfig.linkflags += ['-Wl,--gc-sections']

# link relaxiation
optConfig.linkflags += ['-Wl,--relax']

variants['opt'] = optConfig

###############
# Debug Build #
###############

dbgConfig = BuildConfig()

# optimization
dbgConfig.ccflags += ['-O1', '-g3']

# define DEBUG macro
dbgConfig.cppdefines += ['DEBUG']

variants['dbg'] = dbgConfig

###############
# Simavr Build #
###############

# extend debug configuration
simConfig = copy.deepcopy(dbgConfig)

# define SIMAVR macro
simConfig.cppdefines += ['SIMAVR']

# add simavr to include path
# simConfig.ccflags += [' `pkg-config --cflags simavr` ']
simConfig.cpppath += ['/usr/include/simavr']

variants['sim'] = simConfig

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

# set messages
if env['verbose'] == 0:
	SetupMessages(env)

# set the CPU frequency
globalConfig.cppdefines += ['F_CPU=' + str(env['frequency'])]

# set global build configuration
globalConfig.AppendToEnvironment(env)

# construct the project manager and add it to the environment
SConsEnvironment.pm = ProjectManager(env, projects, devices, variants)

# export the environment so SConscripts can access it
Export('env')

################################################################################
#
# Build it!
#
################################################################################

# tell the project manager about every project in the list
# the rest is handled by the SConscripts
env.pm.BuildAll()
