# Name of the final executable
TARGET = build/toy-taco

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -MMD -MP

# Source files
SOURCES = $(wildcard *.cc)

# Object files
OBJECTS = $(SOURCES:%.cc=build/%.o)

# Dependency files
DEPS = $(OBJECTS:.o=.d)

# Rule to link everything into an executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
# The -MMD and -MP flags generate the dependency files
build/%.o: %.cc
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -rf build/*

# Include the generated dependency files
-include $(DEPS)
