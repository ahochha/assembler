/* To store structs, methods, and variables used globally throughout the Assembler. */

#ifndef Resources_h
#define Resources_h

#include <regex>
#include <string>
#include "OpcodeTable\OpcodeTable.h"
#include "SymbolTable\SymbolTable.h"
using namespace std;

/* struct used as return value for OpcodeTable Search function */
struct SearchOp
{
    bool found;
    Opcode opcode;
};

/* struct used as return value for SymbolTable Search function */
struct SearchSym
{
    bool found;
    Symbol symbol;
};

namespace resources
{
    /* General Use */
    string current_line = "";
    int current_char = 0;

    /* Tables */
    OpcodeTable opcode_table;
    SymbolTable symbol_table;

    /* Variables used when processing symbols */
    int line_num = 1;

    /* Regular expressions used when loading symbol table */
    regex has_label_regex("[^\\s]+\\s+[^\\s]+\\s+[^\\s]+\\s*");
    regex special_op_regex("EQU|END|BASE|EXTREF|EXTDEF");
    regex mem_space_regex("RESW|WORD|RESB|BYTE");
    regex word_expression_regex("\\w+");
    regex number_expression_regex("\\d+");
    regex byte_regex("'[^\\s]+'");
};

#endif