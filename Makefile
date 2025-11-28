CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC = $(wildcard src/core/*.cpp)
BIN = bin/ModelBoids

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
