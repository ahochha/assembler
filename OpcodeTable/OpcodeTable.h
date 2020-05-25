/* used to store opcodes read in from OPCODES.DAT */

#ifndef OpcodeTable_h
#define OpcodeTable_h

#include <string>
#include <vector>
#include <fstream>
#include "Opcode.h"
#include "..\FileHandler.h"
using namespace std;

class OpcodeTable : public FileHandler
{
    public:
        /* constructor */
        OpcodeTable();

        /* functions */
        void LoadData(ifstream&);
        SearchOp Search(string);
        void PrintTable();

        /* destructor */
        ~OpcodeTable();

    private:
        vector<Opcode> opcodes;
        void ProcessOpcode();
        void InsertOpcode(Opcode);
};

#endif