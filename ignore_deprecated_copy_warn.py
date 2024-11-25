Import("env")
for e in env, DefaultEnvironment():
    e.Append(CXXFLAGS=["-Wno-ignored-qualifiers"])
