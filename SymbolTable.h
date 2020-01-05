/* used to store symbols read in from SYMS.DAT */

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <vector>
#include <map>
#include "Symbol.h"
using namespace std;

class SymbolTable 
{
    public:
        /* constructor */
        SymbolTable();

        /* functions */
        void InsertSymbol(int, Symbol);
        void Print();

        /* destructor */
        ~SymbolTable();

    private:
        map<int, Symbol> symbol_table;
};

#endif