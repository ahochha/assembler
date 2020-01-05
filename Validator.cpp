#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Validator.h"
using namespace std;

Validator::Validator()
{
    /* not currently implemented */
}

bool Validator::ValidateSymbolEntry(int line_num, string name, string value, string rflag, Symbol &symbol)
{
    vector<SymbolError> line_errors;
    bool valid_symbol = true;
    bool search_val = true;

    /* validate symbol attributes */
    line_errors.push_back(ValidateSymbolNameFirstChar(line_num, name));
    line_errors.push_back(ValidateSymbolNameAlphaNumericChars(line_num, name));
    line_errors.push_back(ValidateSymbolNameLength(line_num, name));
    line_errors.push_back(ValidateSymbolValue(line_num, value));
    line_errors.push_back(ValidateAndSetSymbolRFLAG(line_num, rflag, symbol));

    /* search vector for errors (is_error == true) */
    valid_symbol = find_if(line_errors.begin(), line_errors.end(), [](const SymbolError &error){
        return error.is_error == true;
    }) == line_errors.end();

    LogErrors(line_errors);

    return valid_symbol;
}

void Validator::LogErrors(vector<SymbolError> line_errors)
{
    for (SymbolError error: line_errors) {
        if (error.is_error == true) {
            errors.push_back(error);
        }
    }

    return;
}

SymbolError Validator::ValidateSymbolNameFirstChar(int line_num, string name)
{
    SymbolError error = { false, line_num, "Valid Symbol!" };

    if (!isalpha(name[0])) {
        error.is_error = true;
        error.message = "ERROR -- The symbol name must start with a letter.  Symbol: " + name;
    }

    return error;
}

SymbolError Validator::ValidateSymbolNameAlphaNumericChars(int line_num, string name)
{
    SymbolError error = { false, line_num, "Valid Symbol!" };

    for (char &c: name) {
        if(!(isalnum(c) || c == '_')) {
            error.is_error = true;
            error.message = "ERROR -- Symbol can only contain a number, letter, or underscore.  Symbol: " + name;
            break;
        }
    }

    return error;
}

SymbolError Validator::ValidateSymbolNameLength(int line_num, string name)
{
    SymbolError error = { false, line_num, "Valid Symbol!" };

    if (name.size() > 10) {
        error.is_error = true;
        error.message = "ERROR -- Symbol must have 10 or less characters.  Symbol: " + name;
    }

    return error;
}

SymbolError Validator::ValidateSymbolValue(int line_num, string value)
{
    SymbolError error = { false, line_num, "Valid Symbol!" };
    bool is_digit;

    for (char &c: value) {
        is_digit = isdigit(c);

        if (c == '-' || c == '+') {
            is_digit = true;
        }

        if (is_digit == false) {
            error.is_error = true;
            error.message = "ERROR -- The value for the symbol must be an int.  Value: " + value;
            break;
        }
    }

    return error;
}

SymbolError Validator::ValidateAndSetSymbolRFLAG(int line_num, string rflag, Symbol &symbol)
{
    SymbolError error = { false, line_num, "Valid Symbol!" };
    const char* c_rflag = rflag.c_str();

    /* tests a true RFLAG */
    if (strcmp(c_rflag, "TRUE") == 0 || strcmp(c_rflag, "T") == 0 || strcmp(c_rflag, "1") == 0) {
        symbol.SetRFLAG(true);
    }
    /* tests a false RFLAG */
    else if (strcmp(c_rflag, "FALSE") == 0 || strcmp(c_rflag, "F") == 0 || strcmp(c_rflag, "0") == 0) {
        symbol.SetRFLAG(false);
    }
    /* anything else */
    else {
        error.is_error = true;
        error.message = "ERROR -- Invalid RFLAG.  RFLAG must be true or false.  RFlag: " + rflag;
    }

    return error;
}

vector<SymbolError> Validator::GetErrors()
{
    return errors;
}

void Validator::PrintErrors()
{
    for (SymbolError error: errors) {
        cout << "Line #" << error.line_num << ": " << error.message << endl;
    }

    cout << endl;

    return;
}

Validator::~Validator()
{
    /* not currently implemented */
}