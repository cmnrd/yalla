################################################################################
#
# Configure scons build flags
#
################################################################################

ccflags   = ''
cxxflags  = ''
linkflags = ''

# set some avr specific flags
ccflags += ' -funsigned-char'
ccflags += ' -funsigned-bitfields'
ccflags += ' -fpack-struct'
ccflags += ' -fshort-enums'

# warnings
ccflags += ' -Wall'
ccflags += ' -Wextra'

# compile c++ files using the c++11 standard
cxxflags += ' -std=c++11'

# debugging options
dbg_ccflags = ccflags
dbg_ccflags += ' -O1 -g2'

dbg_cxxflags = cxxflags
dbg_linkflags = ''

# optimization
ccflags += ' -Os'

# enable link time optimization
ccflags += ' -flto'

# strip unused functions
ccflags   += ' -ffunction-sections -fdata-sections'
linkflags += ' -Wl,--gc-sections'

# link relaxiation
linkflags += ' -Wl,--relax'
