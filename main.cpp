#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Symbol.h"
#include "Validator.h"
#include "SymbolTable.h"
using namespace std;

/* prototypes */
void GetFilename(const int, const char*[], string&);
vector<char> ConvertLineToVector(string);

int main(const int argc, const char* argv[])
{
    ifstream SYMS_file;
	ifstream ASM_file;
    string filename;
    SymbolTable symbol_table;

    SYMS_file.open("SYMS.DAT");

    GetFilename(argc, argv, filename);
    ASM_file.open(filename);

    if (!SYMS_file) {
        cerr << "SYMS.DAT was not found." << endl;
    }
    else {
        symbol_table.LoadData(SYMS_file);
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