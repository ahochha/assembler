#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Validator.h"
using namespace std;

Validator::Validator()
{
    /* not currently implemented */
}

bool Validator::ValidateSymbolLabel(int line_num, string name, Symbol &symbol)
{
    vector<Error> line_errors;
    bool valid_symbol = true;
    bool search_val = true;

    /* validate symbol label */
    line_errors.push_back(ValidateSymbolLabelFirstChar(line_num, name));
    line_errors.push_back(ValidateSymbolLabelAlphaNumericChars(line_num, name));
    line_errors.push_back(ValidateSymbolLabelLength(line_num, name));

    /* search vector for errors (is_error == true) */
    valid_symbol = find_if(line_errors.begin(), line_errors.end(), [](const Error &error){
        return error.is_error == true;
    }) == line_errors.end();

    for (Error error: line_errors) {
        if (error.is_error == true) {
            LogError(error);
        }
    }

    return valid_symbol;
}

void Validator::LogError(Error error)
{
    errors.push_back(error);

    return;
}

Error Validator::ValidateSymbolLabelFirstChar(int line_num, string name)
{
    Error error = { false, line_num, "symbol", "Valid Symbol!" };

    if (!isalpha(name[0])) {
        error.is_error = true;
        error.message = "ERROR -- The symbol name must start with a letter.  Symbol: " + name;
    }

    return error;
}

Error Validator::ValidateSymbolLabelAlphaNumericChars(int line_num, string name)
{
    Error error = { false, line_num, "symbol", "Valid Symbol!" };

    for (char &c: name) {
        if(!(isalnum(c) || c == '_')) {
            error.is_error = true;
            error.message = "ERROR -- Symbol can only contain a number, letter, or underscore.  Symbol: " + name;
            break;
        }
    }

    return error;
}

Error Validator::ValidateSymbolLabelLength(int line_num, string name)
{
    Error error = { false, line_num, "symbol", "Valid Symbol!" };

    if (name.size() > 10) {
        error.is_error = true;
        error.message = "ERROR -- Symbol must have 10 or less characters.  Symbol: " + name;
    }

    return error;
}

bool Validator::ValidateFirstOperation(string operation)
{
    return (operation != "START");
}

vector<Error> Validator::GetErrors()
{
    return errors;
}

void Validator::PrintErrors()
{
    for (Error error: errors) {
        cout << "Line #" << error.line_num << ": " << error.message << endl;
    }

    cout << endl;

    return;
}

Validator::~Validator()
{
    /* not currently implemented */
}