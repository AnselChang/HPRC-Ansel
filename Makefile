CXX = g++
CXXFLAGS = -Wall -std=c++17
SRC_DIR = src
OBJ_DIR = obj

# Use find to get all .cpp files recursively
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Generate object file names based on the source files found
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean
