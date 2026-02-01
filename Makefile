# 1. Variables - Makes it easy to change compilers or flags later
CXX = g++-13
CXXFLAGS = -I include -Wall -Wextra -std=c++17
TARGET = monitor

# 2. Wildcards - Automatically finds all .cpp files in the src/ directory
SRCS = $(wildcard src/*.cpp)

# 3. The Build Rule
# The $(SRCS) part ensures that if ANY .cpp or .h file changes, it rebuilds.
$(TARGET): $(SRCS) $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# 4. Clean Rule
clean:
	rm -f $(TARGET)