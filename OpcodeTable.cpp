#include <iostream>
#include <iomanip>
#include <algorithm>
#include "OpcodeTable.h"
using namespace std;

OpcodeTable::OpcodeTable()
{
    /* not currently implemented */
}

void OpcodeTable::LoadData(ifstream &OPCODES_file)
{
    string file_line = "";

    while (getline(OPCODES_file, file_line)) {
        AddLine(file_line);
        ProcessOpcode(file_line);
    }
}

void OpcodeTable::ProcessOpcode(string file_line)
{
    Opcode temp_opcode;
    int current_char = 0;

    /* get opcode attributes */
    temp_opcode.SetName(ReadAttribute(file_line, current_char));
    temp_opcode.SetOpcode(ReadAttribute(file_line, current_char));
    temp_opcode.SetFormat(stoi(ReadAttribute(file_line, current_char)));

    /* add opcode to table */
    InsertOpcode(temp_opcode);

    return;
}

void OpcodeTable::InsertOpcode(Opcode opcode)
{
    opcode_table.push_back(opcode);
}

FoundOpcode OpcodeTable::Search(string operation)
{
    FoundOpcode search_op = { false, Opcode() };
    auto match_opcode = find_if(opcode_table.begin(), opcode_table.end(), [operation](Opcode &opcode){
        return operation == opcode.GetName();
    });
    search_op.not_found = (match_opcode == opcode_table.end());

    if (!search_op.not_found) {
        int matched_num = distance(opcode_table.begin(), match_opcode);
        search_op.opcode = opcode_table[matched_num];
    }

    return search_op;
}

void OpcodeTable::PrintTable()
{
	cout << endl << setw(6) << "Name" << setw(14) << "Opcode" << setw(12) << "Format" << endl;

    cout << "--------------------------------" << endl;

    for(auto opcode: opcode_table) {
        cout << setw(6) << opcode.GetName() << setw(12) << opcode.GetOpcode() << setw(12) 
            << opcode.GetFormat() << endl;
    }

    cout << endl;

    return;
}

OpcodeTable::~OpcodeTable()
{
    /* not currently implemented */
}