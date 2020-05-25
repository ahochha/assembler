#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Resources.h"
using namespace std;

/* prototypes */
void GetFilename(const int, const char*[], string&);

int main(const int argc, const char* argv[])
{
    ifstream OPCODE_file;
	ifstream ASM_file;
    string filename;

    /* prepare input files */
    OPCODE_file.open("OPCODES.DAT");
    GetFilename(argc, argv, filename);
    ASM_file.open(filename);

    /* load opcode table */
    if (!OPCODE_file) 
    {
        cerr << "ERROR -- OPCODES.DAT was not found." << endl;
    }
    else 
    {
        resources::opcode_table.LoadData(OPCODE_file);
    }

    /* process Assembly program file */
    if (!ASM_file) 
    {
        cerr << "ERROR -- " << filename << " was not found." << endl;
    }
    else 
    {
        resources::symbol_table.LoadData(ASM_file);
        resources::symbol_table.PrintTable();
        resources::symbol_table.PrintErrors();
    }

    OPCODE_file.close();
    ASM_file.close();

    return 0;
}

void GetFilename(const int argc, const char* argv[], string &filename)
{
    if (argc == 1) 
    {
        cout << endl << "Enter source file name: ";   
        getline(cin, filename);
    }
    else 
    {
        filename = string(argv[1]);
    }

    return;
}