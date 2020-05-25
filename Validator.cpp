#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Resources.h"
#include "Validator.h"
using namespace std;

Validator::Validator()
{
    /* not currently implemented */
}

bool Validator::ValidateSymbolLabel(string label)
{
    vector<bool> validation_tests;
    bool valid_symbol = true;
    bool search_val = true;

    /* validate symbol label */
    validation_tests.push_back(ValidateSymbolLabelFirstChar(label));
    validation_tests.push_back(ValidateSymbolLabelAlphaNumericChars(label));
    validation_tests.push_back(ValidateSymbolLabelLength(label));

    return IsValid(validation_tests);
}

bool Validator::ValidateSymbolLabelFirstChar(string label)
{
    bool valid = true;

    if (!isalpha(label[0])) 
    {
        valid = false;
        LogError("the symbol \"" + label + "\" must start with a letter");
    }

    return valid;
}

bool Validator::ValidateSymbolLabelAlphaNumericChars(string label)
{
    bool valid = true;

    for (char &c: label) 
    {
        if (!(isalnum(c) || c == '_')) 
        {
            valid = false;
            LogError("the symbol \"" + label + "\" can only contain a number, letter, or underscore");
            break;
        }
    }

    return valid;
}

bool Validator::ValidateSymbolLabelLength(string label)
{
    bool valid = true;

    if (label.size() > 10) 
    {
        valid = false;
        LogError("the symbol \"" + label + "\" must have 10 or less characters");
    }

    return valid;
}

bool Validator::ValidateOperation(string operation)
{
    SearchOp search_op = resources::opcode_table.Search(operation);
    bool special_op = regex_match(operation, resources::special_op_regex);
    bool mem_space_op = regex_match(operation, resources::mem_space_regex);

    return search_op.found || special_op || mem_space_op || operation == "START";
}

void Validator::LogError(string error_message)
{
    errors.push_back("error - line " + to_string(resources::line_num) + " - " + error_message);

    return;
}

vector<string> Validator::GetErrors()
{
    return errors;
}

bool Validator::IsValid(vector<bool> validation_tests)
{
    bool is_valid = false;

    /* search vector for errors (is_error == true) */
    is_valid = find_if(validation_tests.begin(), validation_tests.end(), [](bool &is_error){
        return is_error == true;
    }) == validation_tests.end();

    return is_valid;
}

void Validator::PrintErrors()
{
    for (string error: errors) {
        cout << error << endl;
    }

    cout << endl;

    return;
}

Validator::~Validator()
{
    /* not currently implemented */
}