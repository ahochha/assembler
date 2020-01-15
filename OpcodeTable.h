/* used to store opcodes read in from OPCODES.DAT */

#ifndef OpcodeTable_h
#define OpcodeTable_h

#include <string>
#include <vector>
#include <fstream>
#include "Opcode.h"
#include "FileHandler.h"
#include "Validator.h"
using namespace std;

class OpcodeTable : public FileHandler
{
    public:
        /* constructor */
        OpcodeTable();

        /* functions */
        void LoadData(ifstream&);
        bool Search(string);
        void PrintTable();

        /* destructor */
        ~OpcodeTable();

    private:
        vector<Opcode> opcode_table;
        void ProcessOpcode(string);
        void InsertOpcode(Opcode);
};

#endif