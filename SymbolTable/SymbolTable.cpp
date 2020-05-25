#include <iostream>
#include <iomanip>
#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable()
{
    /* not currently implemented */
}

void SymbolTable::LoadData(ifstream &ASM_file)
{
    Address current_address = { true, false, 0 };
    string label = "";
    string operation = "";

    while (getline(ASM_file, resources::current_line) && current_address.is_valid == true) 
    {
        if (!IsCommentLine()) 
        {
            current_address = ProcessSymbol(current_address.location_counter);
        }

        resources::line_num++;
        resources::current_char = 0;
    }
}

Address SymbolTable::ProcessSymbol(int location_counter)
{
    Address address = { true, false, location_counter };
    Symbol temp_symbol;
    string label = "";
    string operation = "";

    /* read and validate symbol attributes */
    address.is_valid = ReadAndValidateAttributes(label, operation);

    if (address.is_valid) 
    {
        /* parse operation to increment location counter */
        ParseOperation(location_counter, operation, address);

        /* MAP AND LINE_NUM CAUSING BLANK LINES IN SYMBOL TABLE DISPLAY */
        /* set attributes and add valid symbol to table */
        label.resize(4, ' ');
        temp_symbol.SetLabel(label);

        if (address.is_equ) 
        {
            temp_symbol.SetValue(dtoh(address.location_counter));
            address.location_counter = location_counter;
        }
        else 
        {
            temp_symbol.SetValue(dtoh(location_counter));
        }

        InsertSymbol(temp_symbol);
    }

    return address;
}

bool SymbolTable::ReadAndValidateAttributes(string &label, string &operation)
{
    vector<bool> validation_tests;

    /* if the line has a label, read and validate the label */
    if (regex_match(resources::current_line, resources::has_label_regex)) 
    {
        label = ReadAttribute();
        validation_tests.push_back(ValidateSymbolLabel(label));
    }

    /* read and validate the operation */
    operation = ReadAttribute();
    validation_tests.push_back(ValidateOperation(operation));

    return IsValid(validation_tests);
}

void SymbolTable::ParseOperation(int location_counter, string operation, Address &address)
{
    SearchOp search_op = { false, Opcode() };
    string operand = "";
    bool is_format4 = false;
    bool special_op = regex_match(operation, resources::special_op_regex);
    bool mem_space_op = regex_match(operation, resources::mem_space_regex);

    if (mem_space_op) 
    {
        operand = ReadAttribute();
        address.location_counter = AllocateNeededMemory(operation, operand, location_counter);
    }
    else if (special_op)
    {
        operand = ReadAttribute();
        ParseSpecialOperation(operation, operand, location_counter, address);
    }
    else if (operation == "START")
    {
        address.location_counter = stoi(ReadAttribute());
    }
    else 
    {
        if (operation[0] == '+') 
        {
            is_format4 = true;
            operation.erase(0, 1);
        }

        search_op = resources::opcode_table.Search(operation);
        address.location_counter = DetermineFormatType(search_op.opcode.GetFormat(), location_counter, is_format4);
    }
}

void SymbolTable::ParseSpecialOperation(string operation, string operand, int location_counter, Address &address)
{
    int expression_char = 0;
        int expression_value = 0;

    if (operation == "EQU" && operand != "*")
    {
        address.location_counter = EvaluateExpression(operand, location_counter, expression_char, expression_value);
        address.is_equ = true;
    }
    /* ... */
}

int SymbolTable::EvaluateExpression(string operand, int location_counter, int expression_char, int given_value)
{
    int result = 0;
    int value = 0;
    string expression_op = "";
    
    if (expression_char < operand.size()) 
    {
        if (operand[expression_char] == '+' || operand[expression_char] == '-')
        {
            expression_op = operand[expression_char];
            expression_char++;
        }

        value = GetExpressionValue(operand, expression_char);

        if (expression_op == "+")
        {
            result = given_value + value;
        }
        else if (expression_op == "-")
        {
            result = given_value - value;
        }
        else
        {
            result = EvaluateExpression(operand, location_counter, expression_char, value);
        }
    }

    return result;
}

int SymbolTable::GetExpressionValue(string operand, int &expression_char)
{
    SearchSym search_symbol = { false, Symbol() };
    string expression = "";
    int value = 0;

    if (isalpha(operand[expression_char]))
    {
        expression = ReadExpression(operand, expression_char);
        expression.resize(4, ' ');
        search_symbol = Search(expression);

        if (search_symbol.found == false)
        {
            LogError("found undefined symbol in \"" + operand + "\"");
        }
        else
        {
            value = stoi(search_symbol.symbol.GetValue());
        }
        
    }
    else if (regex_match(to_string(operand[expression_char]), resources::number_expression_regex))
    {
        expression = ReadExpression(operand, expression_char);

        try
        {
            value = stoi(expression);
        }
        catch (exception ex)
        {
            LogError("Expected a number, found \"" + operand + "\"");
        }
    }
    else
    {
        LogError("invalid expression provided");
    }

    return value;
}

string SymbolTable::ReadExpression(string operand, int &expression_char)
{
    string expression = "";

    while ((operand[expression_char] == '+' || operand[expression_char] == '-') && expression_char < operand.size())
    {
        expression += operand[expression_char];
        expression_char++;
    }

    return expression;
}

SearchSym SymbolTable::Search(string label)
{
    SearchSym search_symbol = { false, Symbol() };

    auto match_symbol = find_if(symbols.begin(), symbols.end(), [label](Symbol &symbol) {
        return label == symbol.GetLabel();
    });

    search_symbol.found = (match_symbol != symbols.end());

    if (search_symbol.found)
    {
        int matched_num = distance(symbols.begin(), match_symbol);
        search_symbol.symbol = symbols[matched_num];
    }

    return search_symbol;
}

int SymbolTable::DetermineFormatType(int format, int location_counter, bool is_format4)
{
    if (is_format4) 
    {
        location_counter += 4;
    }
    else if (format == 1) 
    {
        location_counter += 1;
    }
    else if (format == 2) 
    {
        location_counter += 2;
    }
    else if (format == 3) 
    {
        location_counter += 3;
    }

    return location_counter;
}

int SymbolTable::AllocateNeededMemory(string operation, string operand, int location_counter)
{
    if (operation == "WORD") 
    {
        location_counter += 3;
    }
    else if (operation == "RESW") 
    {
        location_counter += (3 * stoi(operand));
    }
    else if (operation == "RESB") 
    {
        location_counter += stoi(operand);
    }
    else if (operation == "BYTE") 
    {
        smatch match;

        if (regex_search(operand, match, resources::byte_regex)) 
        {
            location_counter += (match[0].length() - 2);
        }
        else
        {
            LogError("invalid byte value format (expected format is: 'EXAMPLE')");
        }
    }

    return location_counter;
}

void SymbolTable::InsertSymbol(Symbol symbol)
{
    symbols.insert(pair<int, Symbol>(resources::line_num, symbol));

    return;
}

void SymbolTable::PrintTable()
{
	cout << endl << "Label" << setw(12) << "Value" << setw(12) << "RFlag"
		<< setw(12) << "IFlag" << setw(12) << "MFlag" << endl;

    cout << "------------------------------------------------------" << endl;

    for (auto symbol: symbols) 
    {
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