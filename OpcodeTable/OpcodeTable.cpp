#include <iostream>
#include <iomanip>
#include <algorithm>
#include "..\Resources.h"
#include "OpcodeTable.h"
using namespace std;

OpcodeTable::OpcodeTable()
{
    /* not currently implemented */
}

void OpcodeTable::LoadData(ifstream &OPCODES_file)
{
    string file_line = "";

    while (getline(OPCODES_file, resources::current_line)) 
    {
        ProcessOpcode();
        resources::current_char = 0;
    }
}

void OpcodeTable::ProcessOpcode()
{
    Opcode temp_opcode;
    int current_char = 0;

    /* get opcode attributes */
    temp_opcode.SetOperation(ReadAttribute());
    temp_opcode.SetCode(ReadAttribute());
    temp_opcode.SetFormat(stoi(ReadAttribute()));

    /* add opcode to table */
    InsertOpcode(temp_opcode);

    return;
}

void OpcodeTable::InsertOpcode(Opcode opcode)
{
    opcodes.push_back(opcode);
}

SearchOp OpcodeTable::Search(string operation)
{
    SearchOp search_op = { false, Opcode() };

    auto match_opcode = find_if(opcodes.begin(), opcodes.end(), [operation](Opcode &opcode) {
        return operation == opcode.GetOperation();
    });

    search_op.found = (match_opcode != opcodes.end());

    if (search_op.found) 
    {
        int matched_num = distance(opcodes.begin(), match_opcode);
        search_op.opcode = opcodes[matched_num];
    }

    return search_op;
}

void OpcodeTable::PrintTable()
{
	cout << endl << setw(6) << "Name" << setw(14) << "Opcode" << setw(12) << "Format" << endl;

    cout << "--------------------------------" << endl;

    for (auto opcode: opcodes) 
    {
        cout << setw(6) << opcode.GetOperation() << setw(12) << opcode.GetCode() << setw(12) 
            << opcode.GetFormat() << endl;
    }

    cout << endl;

    return;
}

OpcodeTable::~OpcodeTable()
{
    /* not currently implemented */
}