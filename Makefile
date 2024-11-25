# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Targets
TARGET = Lab07Test
OBJS = WordCount.o tddFuncs.o Lab07Test.o

# Default target
all: $(TARGET)

# Build the test application
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile WordCount
WordCount.o: WordCount.cpp WordCount.h
	$(CXX) $(CXXFLAGS) -c WordCount.cpp

# Compile tddFuncs
tddFuncs.o: tddFuncs.cpp tddFuncs.h
	$(CXX) $(CXXFLAGS) -c tddFuncs.cpp

# Compile Lab07Test
Lab07Test.o: Lab07Test.cpp WordCount.h tddFuncs.h
	$(CXX) $(CXXFLAGS) -c Lab07Test.cpp

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the tests
tests: $(TARGET)
	./$(TARGET)
