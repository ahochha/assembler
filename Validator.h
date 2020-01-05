/* used to validate data read in from files */

#ifndef Validator_h
#define Validator_h

#include <string>
#include <vector>
#include "Symbol.h"
using namespace std;

struct SymbolError 
{
    bool is_error;
    int line_num;
    string message;
};

class Validator 
{
    public:
        /* constructor */
        Validator();

        /* getters */
        vector<SymbolError> GetErrors();

        /* functions */
        bool ValidateSymbolEntry(int, string, string, string, Symbol&);
        void PrintErrors();

        /*destructor */
        ~Validator();

    private:
        vector<SymbolError> errors;
        SymbolError ValidateSymbolNameFirstChar(int, string);
        SymbolError ValidateSymbolNameAlphaNumericChars(int, string);
        SymbolError ValidateSymbolNameLength(int, string);
        SymbolError ValidateSymbolValue(int, string);
        SymbolError ValidateAndSetSymbolRFLAG(int, string, Symbol&);
        void LogErrors(vector<SymbolError>);
};

#endif