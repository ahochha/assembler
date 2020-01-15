#include <iostream>
#include <iomanip>
#include <regex>
#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable()
{
    /* not currently implemented */
}

void SymbolTable::LoadData(ifstream &SYMS_file, OpcodeTable &opcode_table)
{
    string file_line = "";
    int line_num = 1;
    bool critical_error = false;

    while (getline(SYMS_file, file_line) && critical_error == false) {
        if(!IsCommentLine(file_line)) {
            critical_error = ProcessSymbol(line_num, file_line, opcode_table);
            line_num++;
        }
    }
}

bool SymbolTable::ProcessSymbol(int line_num, string file_line, OpcodeTable &opcode_table)
{
    Symbol temp_symbol;
    string label = "";
    string operation = "";
    int current_char = 0;
    bool valid_symbol = true;
    bool critical_error = false;

    /* read and validate label */
    label = ReadAttribute(file_line, current_char);
    valid_symbol = ValidateSymbolLabel(line_num, label, temp_symbol);

    /* read operation (delete [+] if present) */
    operation = ReadAttribute(file_line, current_char);
    
    if (operation[0] == '+') {
        operation.erase(0, 1);
    }

    /* validate program instruction */
    if (line_num == 1) {
        critical_error = ParseFirstOperation(file_line, current_char, operation, temp_symbol);
    }
    else {
        critical_error = ParseOperation(file_line, current_char, operation, temp_symbol, opcode_table);
    }
    
    /* set attributes and add valid symbol to table */
    // if(valid_symbol) {
    //     label.resize(4, ' ');
    //     temp_symbol.SetLabel(label);

    //     InsertSymbol(line_num, temp_symbol);
    // }

    return critical_error;
}

bool SymbolTable::ParseFirstOperation(string file_line, int &current_char, string operation, Symbol &symbol)
{
    bool critical_error = ValidateFirstOperation(operation);

    if(!critical_error) {
        symbol.SetValue(ReadAttribute(file_line, current_char));
        symbol.SetRFLAG(true);
    }
    
    return critical_error;
}

bool SymbolTable::ParseOperation(string file_line, int &current_char, string operation, Symbol &symbol, OpcodeTable &opcode_table)
{
    bool critical_error = false;
    regex skip_op_regex("EQU|END|BASE|EXTREF|EXTDEF");
    regex op_regex("RESW|WORD|RESB|BYTE");

    /* DO SOMETHING FOR LINES THAT DONT HAVE A SYMBOL LABEL */

    if (regex_match(operation, skip_op_regex)) {
        cout << "skip op" << endl;
    }
    else if (regex_match(operation, op_regex)) {
        cout << "op" << endl;
    }
    else {
        critical_error = opcode_table.Search(operation);
        cout << critical_error << " " << operation << endl;
    }

    if (!critical_error) {
        //do stuff here...
    }

    return critical_error;
}

void SymbolTable::InsertSymbol(int line_num, Symbol symbol)
{
    symbol_table.insert(pair<int, Symbol>(line_num, symbol));

    return;
}

void SymbolTable::PrintTable()
{
	cout << endl << "Label" << setw(12) << "Value" << setw(12) << "RFlag"
		<< setw(12) << "IFlag" << setw(12) << "MFlag" << endl;

    cout << "------------------------------------------------------" << endl;

    for (auto symbol: symbol_table) {
        cout << setw(4) << symbol.second.GetLabel() << setw(12) << symbol.second.GetValue() 
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