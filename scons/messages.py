################################################################################
#
# Define functions for printing non verbose colored build messages
#
################################################################################

import sys

# define colors
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

# If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
	for key, value in colors.iteritems():
		colors[key] = ''

compile_source = '%sCompiling    %s==> %s$TARGET%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program   = '%sLinking      %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library   = '%sLinking      %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library = '%sRanlib       %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

def PrintCmdLine(s, target, source, env):
	if s.startswith('avr-objcopy') :
		print '%sGenerate hex %s==> %s%s%s' % \
		(colors['green'], colors['purple'], colors['yellow'], target[0], colors['end'])
	elif s.startswith('avr-size') :
		print '%sMemory Usage %s==> %s%s%s' % \
		(colors['cyan'], colors['purple'], colors['yellow'], source[0], colors['end'])
	elif s.startswith('Install') :
		print '%sInstalling   %s==> %s%s%s' % \
		(colors['green'], colors['purple'], colors['yellow'], target[0], colors['end'])
	else:
		print s

def SetupMessages(env):
	env['CCCOMSTR']     = compile_source
	env['CXXCOMSTR']    = compile_source
	env['ARCOMSTR']     = link_library
	env['LINKCOMSTR']   = link_program
	env['RANLIBCOMSTR'] = ranlib_library
	env['PRINT_CMD_LINE_FUNC'] = PrintCmdLine
