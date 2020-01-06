#include <iostream>
#include <iomanip>
#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable()
{
    /* not currently implemented */
}

void SymbolTable::LoadData(ifstream &SYMS_file)
{
    string file_line = "";
    int line_num = 1;

    while (getline(SYMS_file, file_line)) {
        AddLine(file_line);
        ProcessSymbol(line_num, file_line);
        line_num++;
    }
}

void SymbolTable::ProcessSymbol(int line_num, string file_line)
{
    vector<SymbolError> errors;
    Symbol temp_symbol;
    string name = "";
    string value = "";
    string rflag = "";
    int current_char = 0;
    bool valid_symbol = true;

    /* get symbol attributes */
    name = ReadAttribute(file_line, current_char);
    value = ReadAttribute(file_line, current_char);
    rflag = ReadAttribute(file_line, current_char);

    /* validate symbol attributes before adding symbol to table */
    valid_symbol = ValidateSymbolEntry(line_num, name, value, rflag, temp_symbol);
    
    /* set attributes and add valid symbol to table */
    if(valid_symbol) {
        name.resize(4, ' ');
        temp_symbol.SetName(name);
        temp_symbol.SetValue(value);
        temp_symbol.SetIFLAG(false);
        temp_symbol.SetMFLAG(false);

        InsertSymbol(line_num, temp_symbol);
    }

    return;
}

void SymbolTable::InsertSymbol(int line_num, Symbol symbol)
{
    symbol_table.insert(pair<int, Symbol>(line_num, symbol));

    return;
}

void SymbolTable::PrintTable()
{
	cout << endl << "Symbol" << setw(12) << "Value" << setw(12) << "RFlag"
		<< setw(12) << "IFlag" << setw(12) << "MFlag" << endl;

    cout << "------------------------------------------------------" << endl;

    for (auto symbol: symbol_table) {
        cout << setw(4) << symbol.second.GetName() << setw(12) << symbol.second.GetValue() 
            << setw(12) << symbol.second.GetRFLAG() << setw(12) << symbol.second.GetIFLAG() 
            << setw(12) << symbol.second.GetMFLAG() << endl;
    }

    cout << endl;

    return;
}

SymbolTable::~SymbolTable()
{
    /* not currently implemented */
}