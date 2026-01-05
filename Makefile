CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(shell find src -name '*.cpp')

BIN_DIR = bin
BIN = $(BIN_DIR)/ModelBoids

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean
