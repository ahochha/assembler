/* used to store symbols read in from SYMS.DAT */

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <map>
#include <fstream>
#include "Symbol.h"
#include "FileHandler.h"
#include "Validator.h"
#include "IntermediateTable.h"
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
        bool ProcessSymbol(int, string);
        bool ParseFirstOperation(string, int&, string, Symbol&);
        void InsertSymbol(int, Symbol);
};

#endif