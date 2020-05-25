/* used to store symbols read in from SYMS.DAT */

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <map>
#include <fstream>
#include "Resources.h"
#include "Symbol.h"
#include "OpcodeTable\Opcode.h"
#include "FileHandler.h"
#include "Validator.h"
#include "NumericConverter.h"
using namespace std;

struct Address
{
    bool is_valid;
    bool is_equ;
    int location_counter;
};

class SymbolTable : public FileHandler, public Validator, public NumericConverter
{
    public:
        /* constructor */
        SymbolTable();

        /* functions */
        void LoadData(ifstream&);
        void PrintTable();

        /* destructor */
        ~SymbolTable();

    private:
        map<int, Symbol> symbols;
        bool ReadAndValidateAttributes(string&, string&);
        Address ProcessSymbol(int);
        void ParseOperation(int, string, Address&);
        void ParseSpecialOperation(string, string, int, Address&);
        int GetExpressionValue(string, int&);
        string ReadExpression(string, int&);
        SearchSym Search(string);
        int EvaluateExpression(string, int, int, int);
        int AllocateNeededMemory(string, string, int);
        int DetermineFormatType(int, int, bool);
        void InsertSymbol(Symbol);
};

#endif