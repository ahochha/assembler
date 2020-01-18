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
    Address address = { false, false, true, 0 };

    while (getline(SYMS_file, file_line) && address.is_error == false) {
        if(!IsCommentLine(file_line)) {
            AddLine(file_line);
            address = ProcessSymbol(line_num, address.location_counter, GetLine(line_num), opcode_table);
            line_num++;
        }
    }
}

/* ADD ERROR HANDLING FOR LINES WITH ERRORS */
Address SymbolTable::ProcessSymbol(int line_num, int location_counter, string file_line, OpcodeTable &opcode_table)
{
    Address address = { false, false, true, location_counter };
    Symbol temp_symbol;
    string label = "";
    string operation = "";
    int current_char = 0;
    bool valid_symbol = false;
    regex has_label_regex("[^\\s]+\\s+[^\\s]+\\s+[^\\s]+\\s*");

    if (regex_match(file_line, has_label_regex)) {
        /* read and validate label */
        label = ReadAttribute(file_line, current_char);
        valid_symbol = ValidateSymbolLabel(line_num, label, temp_symbol);
    }

    /* read operation */
    operation = ReadAttribute(file_line, current_char);

    /* parse instruction to increment location counter */
    if (line_num == 1) {
        address = ParseFirstOperation(file_line, current_char, operation, temp_symbol);
    }
    else {
        address = ParseOperation(file_line, current_char, location_counter, operation, temp_symbol, opcode_table);
    }
    /* PROBLEM WITH SYMBOL TABLE INCREMENTING LINE_NUM WHEN ITS NOT SUPPOSE TO,
    CAUSING ISSUE WITH SYMBOL TABLE DISPLAY SHOWING BLANK LINES */
    /* set attributes and add valid symbol to table */
    if(valid_symbol && !address.is_error) {
        label.resize(4, ' ');
        temp_symbol.SetLabel(label);

        if (address.is_equ) {
            temp_symbol.SetValue(dtoh(address.location_counter));
            address.location_counter = location_counter;
        }
        else {
            temp_symbol.SetValue(dtoh(location_counter));
        }

        cout << temp_symbol.GetLabel() << ' ' << temp_symbol.GetValue() << endl;

        InsertSymbol(line_num, temp_symbol);
    }

    return address;
}

Address SymbolTable::ParseFirstOperation(string file_line, int &current_char, string operation, Symbol &symbol)
{
    Address address = { false, false, true, 0 };
    address.is_error = ValidateFirstOperation(operation);

    if(!address.is_error) {
        address.location_counter = stoi(ReadAttribute(file_line, current_char));
    }
    
    return address;
}

Address SymbolTable::ParseOperation(string file_line, int &current_char, int location_counter, string operation, Symbol &symbol, OpcodeTable &opcode_table)
{
    Address address = { false, false, true, location_counter };
    FoundOpcode search_op = { false, Opcode() };
    string operand = "";
    regex special_op_regex("EQU|END|BASE|EXTREF|EXTDEF");
    regex mem_space_regex("RESW|WORD|RESB|BYTE");
    bool special_op = regex_match(operation, special_op_regex);
    bool mem_space_op = regex_match(operation, mem_space_regex);

    if (mem_space_op) {
        operand = ReadAttribute(file_line, current_char);
        address.location_counter = AllocateNeededMemory(operation, operand, location_counter);
    }
    else if (special_op)
    {
        operand = ReadAttribute(file_line, current_char);
        address = ParseSpecialOperation(operation, operand, location_counter);
    }
    else {
        if (operation[0] == '+') {
            operation.erase(0, 1);
        }

        search_op = opcode_table.Search(operation);
        address.is_error = search_op.not_found;
        address.location_counter = DetermineFormatType(search_op.opcode.GetFormat(), location_counter);
    }

    return address;
}

Address SymbolTable::ParseSpecialOperation(string operation, string operand, int location_counter)
{
    Address address = { false, false, true, location_counter };

    if (operation == "EQU" && operand != "*")
    {
        address.location_counter = EvaluateExpression(operand, location_counter);
        address.is_equ = true;
    }
    /* ... */

    return address;
}

int SymbolTable::EvaluateExpression(string operand, int location_counter)
{
    int value  = 0;
    int expression_start = 0;
    FoundSymbol expression_1 = { false, Symbol() };
    FoundSymbol expression_2 = { false, Symbol() };
    regex op_type_regex("\\w+[\\+\\-]\\w+");
    bool equation = regex_match(operand, op_type_regex);
    
    if (equation) {
        expression_1 = GetExpressionValue(operand, expression_start);
        expression_start++;
        expression_2 = GetExpressionValue(operand, expression_start);

        if (operand.find('+') != string::npos && (expression_1.found && expression_2.found))
        {
            value = stoi(expression_1.symbol.GetValue()) + stoi(expression_2.symbol.GetValue());
        }
        else if (operand.find('-') != string::npos && (expression_1.found && expression_2.found))
        {
            value = stoi(expression_1.symbol.GetValue()) - stoi(expression_2.symbol.GetValue());
        }
    }
    else {
        expression_1 = GetExpressionValue(operand, expression_start);
        value = stoi(expression_1.symbol.GetValue());
    }

    return value;
}

FoundSymbol SymbolTable::GetExpressionValue(string operand, int &expression_start)
{
    FoundSymbol search_symbol = { false, Symbol() };
    string expression = "";
    string comparison_operand = operand.erase(0, expression_start);
    regex expression_regex("\\w+");
    smatch match;

    if (regex_search(operand, match, expression_regex)) {
        if (match.size() == 1) {
            expression = match[0];
            expression.resize(4, ' ');
            search_symbol = Search(expression);
            expression_start = match[0].length();
        }
    }

    /* CHECK FOR NUMBER */
    if (!search_symbol.found) {
        search_symbol.symbol.SetValue(operand);
    }

    return search_symbol;
}

FoundSymbol SymbolTable::Search(string label)
{
    FoundSymbol search_symbol = { false, Symbol() };

    for (int i = 0; i < symbol_table.size(); i++) {
        if (label == symbol_table[i].GetLabel()) {
            search_symbol.symbol = symbol_table[i];
            search_symbol.found = true;
        }
    }

    return search_symbol;
}

int SymbolTable::DetermineFormatType(int format, int location_counter)
{
    if (format == 1) {
        location_counter += 1;
    }
    else if (format == 2) {
        location_counter += 2;
    }
    else if (format == 3) {
        location_counter += 3;
    }
    else if (format == 4) {
        location_counter += 4;
    }

    return location_counter;
}

int SymbolTable::AllocateNeededMemory(string operation, string operand, int location_counter)
{
    if (operation == "WORD") {
        location_counter += 3;
    }
    else if (operation == "RESW") {
        location_counter += (3 * stoi(operand));
    }
    else if (operation == "RESB") {
        location_counter += stoi(operand);
    }
    else if (operation == "BYTE") {
        regex byte_regex("'[^\\s]+'");
        smatch match;

        if (regex_search(operand, match, byte_regex)) {
            if (match.size() == 1) {
                location_counter += (match[0].length() - 2);
            }
            else {
                /* log error */
            }
        }
    }

    return location_counter;
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