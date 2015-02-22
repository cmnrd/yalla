################################################################################
#
# Class for simple handling of build configurations
#
################################################################################

class BuildConfig:

	def __init__(self):
		self.ccflags    = list()
		self.cxxflags   = list()
		self.linkflags  = list()
		self.cppdefines = list()
		self.cpppath    = list()
		self.parse      = list()

	def AppendToEnvironment(self, env):
		env.Append( CCFLAGS    = self.ccflags)
		env.Append( CXXFLAGS   = self.cxxflags)
		env.Append( LINKFLAGS  = self.linkflags)
		env.Append( CPPDEFINES = self.cppdefines)
		env.Append( CPPPATH    = self.cpppath)

		for p in self.parse:
			env.ParseConfig(p)
