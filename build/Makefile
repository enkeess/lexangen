RESULT = lib/
BIN = bin/
TARGET = syn-analyzer
SRC = src/
TEST = test/

all: bin clean $(TARGET)

$(TARGET): $(BIN)STATE_NAME.o $(BIN)Mark.o $(BIN)Transition.o $(BIN)State.o $(BIN)Graph.o $(BIN)Dependencies.o $(BIN)Scanner.o $(BIN)Parser.o 
	g++ -std=c++11 $(BIN)STATE_NAME.o $(BIN)Mark.o $(BIN)Transition.o $(BIN)State.o $(BIN)Graph.o $(BIN)Dependencies.o $(BIN)Scanner.o $(BIN)Parser.o main.cpp -o $(TARGET)

$(BIN)STATE_NAME.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)STATE_NAME.o $(SRC)STATE_NAME.cpp
$(BIN)Mark.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Mark.o $(SRC)Mark.cpp
$(BIN)Transition.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Transition.o $(SRC)Transition.cpp
$(BIN)State.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)State.o $(SRC)State.cpp
$(BIN)Graph.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Graph.o $(SRC)Graph.cpp
$(BIN)Dependencies.o: 
	g++ -fPIC -c -std=c++11 -o $(BIN)Dependencies.o $(SRC)Dependencies.cpp
$(BIN)Scanner.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Scanner.o $(SRC)Scanner.cpp
$(BIN)Parser.o: 
	g++ -fPIC -c -std=c++11 -o $(BIN)Parser.o $(SRC)Parser.cpp

bin:
	mkdir bin

clean:
	rm -rf $(BIN)Dependencies.o $(BIN)STATE_NAME.o
	rm -f $(TARGET)