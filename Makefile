CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(shell find src -name '*.cpp')
OBJ = $(SRC:.cpp=.o)

BIN_DIR = bin
BIN = $(BIN_DIR)/ModelBoids

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN) $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all run clean
