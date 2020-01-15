/* used to store process and store instructions from a program file */

#ifndef IntermediateTable_h
#define IntermediateTable_h

#include <string>
#include <map>
#include <fstream>
#include "Symbol.h"
#include "FileHandler.h"
#include "Validator.h"
#include "Instruction.h"
using namespace std;

class IntermediateTable : public FileHandler, public Validator
{
    public:
        /* constructor */
        IntermediateTable();

        /* functions */
        void ProcessFile(ifstream&);
        void PrintTable();

        /* destructor */
        ~IntermediateTable();

    private:
        map<int, Instruction> intermediate_table;
        void ProcessInstruction(int, string);
        void InsertInstruction(int, Instruction);   
};

#endif