#include <iostream>
#include <iomanip>
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