#include <string>
#include "Opcode.h"
using namespace std;

Opcode::Opcode()
{
    operation = "";
    code = "";
    format = -99;
}

void Opcode::SetOperation(string operation)
{
    this->operation = operation;
}

void Opcode::SetCode(string code)
{
    this->code = code;
}

void Opcode::SetFormat(int format)
{
    this->format = format;
}

string Opcode::GetOperation()
{
    return operation;
}

string Opcode::GetCode()
{
    return code;
}

int Opcode::GetFormat()
{
    return format;
}

Opcode::~Opcode()
{
    /* not currently implemented */
}