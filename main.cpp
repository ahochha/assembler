#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Symbol.h"
#include "Validator.h"
#include "SymbolTable.h"
#include "OpcodeTable.h"
#include "IntermediateTable.h"
using namespace std;

/* prototypes */
void GetFilename(const int, const char*[], string&);

int main(const int argc, const char* argv[])
{
    ifstream OPCODE_file;
	ifstream ASM_file;
    string filename;
    SymbolTable symbol_table;
    OpcodeTable opcode_table;
    IntermediateTable intermediate_table;

    OPCODE_file.open("OPCODES.DAT");

    GetFilename(argc, argv, filename);
    ASM_file.open(filename);

    /* load opcode table */
    if (!OPCODE_file) {
        cerr << "ERROR -- OPCODES.DAT was not found." << endl;
    }
    else {
        opcode_table.LoadData(OPCODE_file);
    }

    /* process inputed program file */
    if (!ASM_file) {
        cerr << "ERROR -- " << filename << " was not found." << endl;
    }
    else {
        symbol_table.LoadData(ASM_file, opcode_table);
        symbol_table.PrintTable();
        symbol_table.PrintErrors();
    }

    return 0;
}

void GetFilename(const int argc, const char* argv[], string &filename)
{
    if (argc == 1) {
        cout << endl << "Enter source file name: ";      
        getline(cin, filename);
    }
    else {
        filename = string(argv[1]);
    }

    return;
}