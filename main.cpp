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
void ProcessSYMSFileLine(int, vector<char>, SymbolTable&, Validator&);
string ReadSymbolAttribute(vector<char>, int&);
vector<char> ConvertLineToVector(string);

int main(const int argc, const char* argv[])
{
    ifstream SYMS_file;
	ifstream ASM_file;
    string filename;
    string file_line_str;
    vector<char> file_line;
    vector<vector<char>> lines;
    SymbolTable symbol_table;
    Validator validator;
    int line_num = 1;

    SYMS_file.open("SYMS.DAT");

    GetFilename(argc, argv, filename);
    ASM_file.open(filename);

    if (!SYMS_file) {
        cerr << "SYMS.DAT was not found." << endl;
    }
    else {
        while (getline(SYMS_file, file_line_str)) {
            file_line = ConvertLineToVector(file_line_str);
            lines.push_back(file_line);
            ProcessSYMSFileLine(line_num, file_line, symbol_table, validator);
            line_num++;
        }

        symbol_table.Print();
        validator.PrintErrors();
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

void ProcessSYMSFileLine(int line_num, vector<char> file_line, SymbolTable &symbol_table, Validator &validator)
{
    vector<SymbolError> errors;
    Symbol temp_symbol;
    string name = "";
    string value = "";
    string rflag = "";
    int current_char = 0;
    bool valid_symbol = true;

    /* get symbol attributes */
    name = ReadSymbolAttribute(file_line, current_char);
    value = ReadSymbolAttribute(file_line, current_char);
    rflag = ReadSymbolAttribute(file_line, current_char);

    /* validate symbol attributes before adding symbol to table */
    valid_symbol = validator.ValidateSymbolEntry(line_num, name, value, rflag, temp_symbol);
    
    /* set attributes and add valid symbol to table */
    if(valid_symbol) {
        name.resize(4, ' ');
        temp_symbol.SetName(name);
        temp_symbol.SetValue(value);
        temp_symbol.SetIFLAG(false);
        temp_symbol.SetMFLAG(false);

        symbol_table.InsertSymbol(line_num, temp_symbol);
    }

    return;
}

string ReadSymbolAttribute(vector<char> file_line, int& current_char)
{
    int attr_char = 0;
    string attribute = "";

    /* skip spaces at begining of attribute */
    while (file_line[current_char] == ' ') {
        current_char++;
    }

    /* copy filtered file_line substring over to attribute */
    while (file_line[current_char] != ' ' && current_char < file_line.size()) {
        attribute.push_back(toupper(file_line[current_char]));
        attr_char++;
        current_char++;
    }

    return attribute;
}

vector<char> ConvertLineToVector(string line_str)
{
    vector<char> line(line_str.begin(), line_str.end());
    return line;
}

