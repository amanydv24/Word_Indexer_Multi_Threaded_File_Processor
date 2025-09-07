# Define the C++ compiler
CXX = g++

# Define compiler flags (e.g., C++ standard, warnings, optimization)
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2 -Iinc

# Define the name of the executable
TARGET = exec

# List all source files
# SRCS = src/main.cpp src/SearchThread.cpp src/SyncQueue.cpp
SRCS =  src/main.cpp \
		src/SearchThread.cpp \
		src/WorkerThread.cpp \
		src/SyncQueue.cpp


# Generate object file names from source files
OBJS = $(SRCS:.cpp=.o)

# Default target: builds the executable
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pattern rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target: removes generated files
clean:
	rm -f $(TARGET) $(OBJS)