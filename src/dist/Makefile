RESULT = lib/
BIN = bin/
TARGET = $(BIN)libtranslator.so
SRC = src/
TEST = test/

all:$(TARGET)

$(TARGET):$(BIN)Scanner.o $(BIN)Mark.o $(BIN)Graph.o $(BIN)State.o $(BIN)Transition.o $(BIN)Parser.o 
	g++ -std=c++11 -shared -o $(TARGET) $(BIN)Scanner.o $(BIN)Mark.o $(BIN)Graph.o $(BIN)State.o $(BIN)Transition.o $(BIN)Parser.o 


$(BIN)Mark.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Mark.o $(SRC)Mark.cpp
$(BIN)Transition.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Transition.o $(SRC)Transition.cpp
$(BIN)State.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)State.o $(SRC)State.cpp
$(BIN)Graph.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Graph.o $(SRC)Graph.cpp
$(BIN)Scanner.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Scanner.o $(SRC)Scanner.cpp
$(BIN)Parser.o: 
	g++ -fPIC -c -std=c++11 -o $(BIN)Parser.o $(SRC)Parser.cpp

install:
	install $(TARGET) $(RESULT)
bin:
	mkdir bin

clean:
	rm -rf $(BIN)*.o