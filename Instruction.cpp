#include <iostream>
#include <iomanip>
#include "Instruction.h"
using namespace std;

Instruction::Instruction()
{
    label = "";
    operation = "";
    operand = "";
    location_counter = 0;
}

void Instruction::SetLabel(string _label)
{
    label = _label;
}

void Instruction::SetOperation(string _operation)
{
    operation = _operation;
}

void Instruction::SetOperand(string _operand)
{
    operand = _operand;
}

void Instruction::SetLocationCounter(string _lc)
{
    location_counter = stoi(_lc);
}

string Instruction::GetLabel()
{
    return label;
}

string Instruction::GetOperation()
{
    return operation;
}

string Instruction::GetOperand()
{
    return operand;
}

int Instruction::GetLocationCounter()
{
    return location_counter;
}

Instruction::~Instruction()
{
    /* not currently implemented */
}