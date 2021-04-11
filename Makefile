RESULT = lib/
BIN = bin/
TARGET = lexangen
SRC = src/


all:$(TARGET)

$(TARGET): $(BIN)FIleReader.o 
	g++ -std=c++11  $(BIN)FIleReader.o main.cpp -o $(TARGET)

$(BIN)FIleReader.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)FIleReader.o $(SRC)FIleReader.cpp

bin:
	mkdir bin

clean:
	rm -rf $(BIN)*.o