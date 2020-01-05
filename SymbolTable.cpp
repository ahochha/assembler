#include <iostream>
#include <iomanip>
#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable()
{
    /* not currently implemented */
}

void SymbolTable::InsertSymbol(int line_num, Symbol symbol)
{
    symbol_table.insert(pair<int, Symbol>(line_num, symbol));

    return;
}

void SymbolTable::Print()
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