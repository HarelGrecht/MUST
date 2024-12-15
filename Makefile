# Compiler and flags
CXX = g++
CXXFLAGS = -IIncludes -std=c++17 -Wall -Wextra -lpthread -lpcap

# Source and output directories
SRC_DIR = Sources
OBJ_DIR = Objects
BIN = MUST

# Find all source files in the Sources directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Convert source file paths to object file paths
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: compile

# Compile the project normally (real mode)
compile: CXXFLAGS += 
compile: $(BIN)

# Compile the project in mock-up mode
compile_mock_up: CXXFLAGS += -DMOCK_UP
compile_mock_up: $(BIN)

# Link the binary
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: $(BIN)
	./$(BIN)

# Clean build files
clear:
	rm -rf $(OBJ_DIR) $(BIN)

# Debugging helper
print:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
