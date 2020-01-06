/* used to store symbols read in from SYMS.DAT */

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Symbol.h"
#include "FileHandler.h"
#include "Validator.h"
using namespace std;

class SymbolTable : public FileHandler, public Validator
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
        map<int, Symbol> symbol_table;
        void ProcessSymbol(int, string);
        void InsertSymbol(int, Symbol);
};

#endif