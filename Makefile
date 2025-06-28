DIST := wthr

BUILD_DIR := build
SRC_DIR := src

EXEC := $(BUILD_DIR)/$(DIST)

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SOURCES))

CXX := g++
CXXFLAGS := -MMD -MP -std=c++20 -Wall -O3
LDFLAGS := $(shell pkg-config --libs ncurses)

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -rf $(BUILD_DIR)

run:
	./$(EXEC)
