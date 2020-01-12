#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Symbol.h"
#include "Validator.h"
#include "SymbolTable.h"
#include "OpcodeTable.h"
using namespace std;

/* prototypes */
void GetFilename(const int, const char*[], string&);

int main(const int argc, const char* argv[])
{
    ifstream SYMS_file;
    ifstream OPCODE_file;
	ifstream ASM_file;
    string filename;
    SymbolTable symbol_table;
    OpcodeTable opcode_table;

    SYMS_file.open("SYMS.DAT");
    OPCODE_file.open("OPCODES.DAT");

    GetFilename(argc, argv, filename);
    ASM_file.open(filename);

    /* load and display symbol table */
    if (!SYMS_file) {
        cerr << "ERROR -- SYMS.DAT was not found." << endl;
    }
    else {
        symbol_table.LoadData(SYMS_file);
        symbol_table.PrintTable();
        symbol_table.PrintErrors();
    }

    /* load opcode table */
    if (!OPCODE_file) {
        cerr << "ERROR -- OPCODES.DAT was not found." << endl;
    }
    else {
        opcode_table.LoadData(OPCODE_file);
        opcode_table.PrintTable();
    }

    /* process inputed program file 
    if (!ASM_file) {
        cerr << "ERROR -- " << filename << " was not found." << endl;
    }
    else {
        cout << "--- PASS ONE ---" << endl << endl << endl << "SIC/XE Source Program" << endl << endl;

    } */

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