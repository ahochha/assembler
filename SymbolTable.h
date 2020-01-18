/* used to store symbols read in from SYMS.DAT */

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <map>
#include <fstream>
#include "Symbol.h"
#include "FileHandler.h"
#include "Validator.h"
#include "OpcodeTable.h"
#include "NumericConverter.h"
using namespace std;

struct Address
{
    bool is_error;
    bool is_equ;
    bool RFLAG;
    int location_counter;
};

struct FoundSymbol
{
    bool found;
    Symbol symbol;
};

class SymbolTable : public FileHandler, public Validator, public NumericConverter
{
    public:
        /* constructor */
        SymbolTable();

        /* functions */
        void LoadData(ifstream&, OpcodeTable&);
        void PrintTable();

        /* destructor */
        ~SymbolTable();

    private:
        map<int, Symbol> symbol_table;
        Address ProcessSymbol(int, int, string, OpcodeTable&);
        Address ParseFirstOperation(string, int&, string, Symbol&);
        Address ParseOperation(string, int&, int, string, Symbol&, OpcodeTable&);
        Address ParseSpecialOperation(string, string, int);
        FoundSymbol GetExpressionValue(string, int&);
        FoundSymbol Search(string);
        int EvaluateExpression(string, int);
        int AllocateNeededMemory(string, string, int);
        int DetermineFormatType(int, int);
        void InsertSymbol(int, Symbol);
};

#endif