/* used to validate data read in from files */

#ifndef Validator_h
#define Validator_h

#include <string>
#include <vector>
#include "Symbol.h"
using namespace std;

struct Error 
{
    bool is_error;
    int line_num;
    string error_type;
    string message;
};

class Validator
{
    public:
        /* constructor */
        Validator();

        /* getters */
        vector<Error> GetErrors();

        /* functions */
        bool ValidateSymbolLabel(int, string, Symbol&);
        bool ValidateFirstOperation(string);
        void PrintErrors();

        /*destructor */
        ~Validator();

    private:
        vector<Error> errors;
        Error ValidateSymbolLabelFirstChar(int, string);
        Error ValidateSymbolLabelAlphaNumericChars(int, string);
        Error ValidateSymbolLabelLength(int, string);
        void LogError(Error);
};

#endif