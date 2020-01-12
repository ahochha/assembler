#include <string>
#include "Opcode.h"
using namespace std;

Opcode::Opcode()
{
    name = "";
    opcode = "";
    format = -99;
}

void Opcode::SetName(string _name)
{
    name = _name;
}

void Opcode::SetOpcode(string _opcode)
{
    opcode = _opcode;
}

void Opcode::SetFormat(int _format)
{
    format = _format;
}

string Opcode::GetName()
{
    return name;
}

string Opcode::GetOpcode()
{
    return opcode;
}

int Opcode::GetFormat()
{
    return format;
}

Opcode::~Opcode()
{
    /* not currently implemented */
}