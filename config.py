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

# optimization
ccflags += ' -Os'

# enable link time optimization
ccflags += ' -flto'

# strip unused functions
ccflags   += ' -ffunction-sections -fdata-sections'
linkflags +=  ' -Wl,--gc-sections'

# link relaxiation
linkflags += ' -Wl,--relax'

# compile c++ files using the c++11 standard
cxxflags += ' -std=c++11'
