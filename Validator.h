/* used to validate data read in from files */

#ifndef Validator_h
#define Validator_h

#include <string>
#include <vector>
#include <map>
#include "SymbolTable\Symbol.h"
using namespace std;

class Validator
{
    public:
        /* constructor */
        Validator();

        /* getters */
        vector<string> GetErrors();

        /* public functions */
        bool ValidateSymbolLabel(string);
        bool ValidateOperation(string);
        bool IsValid(vector<bool>);
        void LogError(string);
        void PrintErrors();

        /*destructor */
        ~Validator();

    private:
        vector<string> errors;
        bool ValidateSymbolLabelFirstChar(string);
        bool ValidateSymbolLabelAlphaNumericChars(string);
        bool ValidateSymbolLabelLength(string);
};

#endif