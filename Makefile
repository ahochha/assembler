prog: main.o Symbol.o SymbolTable.o Opcode.o OpcodeTable.o Instruction.o IntermediateTable.o Validator.o FileHandler.o
	g++ -std=c++11 main.o Symbol.o SymbolTable.o Opcode.o OpcodeTable.o Instruction.o IntermediateTable.o Validator.o FileHandler.o -o prog

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Symbol.o: Symbol.cpp Symbol.h
	g++ -std=c++11 -c Symbol.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -std=c++11 -c SymbolTable.cpp

Opcode.o: Opcode.cpp Opcode.h
	g++ -std=c++11 -c Opcode.cpp

OpcodeTable.o: OpcodeTable.cpp OpcodeTable.h
	g++ -std=c++11 -c OpcodeTable.cpp

Instruction.o: Instruction.cpp Instruction.h
	g++ -std=c++11 -c Instruction.cpp

IntermediateTable.o: IntermediateTable.cpp IntermediateTable.h
	g++ -std=c++11 -c IntermediateTable.cpp

Validator.o: Validator.cpp Validator.h
	g++ -std=c++11 -c Validator.cpp

FileHandler.o: FileHandler.cpp FileHandler.h
	g++ -std=c++11 -c FileHandler.cpp

clean:
	rm *.o prog