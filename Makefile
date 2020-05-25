prog: main.o FileHandler.o Opcode.o OpcodeTable.o
	g++ -std=c++11 main.o FileHandler.o Opcode.o OpcodeTable.o -o prog

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

FileHandler.o: FileHandler.cpp FileHandler.h
	g++ -std=c++11 -c FileHandler.cpp

NumericCoverter.o: NumericCoverter.cpp NumericCoverter.h
	g++ -std=c++11 -c NumericCoverter.cpp

Opcode.o: OpcodeTable\Opcode.cpp OpcodeTable\Opcode.h
	g++ -std=c++11 -c OpcodeTable\Opcode.cpp

OpcodeTable.o: OpcodeTable\OpcodeTable.cpp OpcodeTable\OpcodeTable.h
	g++ -std=c++11 -c OpcodeTable\OpcodeTable.cpp

Symbol.o: SymbolTable\Symbol.cpp SymbolTable\Symbol.h
	g++ -std=c++11 -c SymbolTable\Symbol.cpp

SymbolTable.o: SymbolTable\SymbolTable.cpp SymbolTable\SymbolTable.h
	g++ -std=c++11 -c SymbolTable\SymbolTable.cpp

clean:
	rm *.o prog