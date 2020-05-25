#include "Symbol.h"
using namespace std;

Symbol::Symbol()
{
    label = "";
    value = "";
    RFLAG = false;
    IFLAG = false;
    MFLAG = false;
}

void Symbol::SetLabel(string label)
{
    this->label = label;
}

void Symbol::SetValue(string value)
{
    this->value = value;
}

void Symbol::SetRFLAG(bool RFLAG)
{
    this->RFLAG = RFLAG;
}

void Symbol::SetIFLAG(bool IFLAG)
{
    this->IFLAG = IFLAG;
}

void Symbol::SetMFLAG(bool MFLAG)
{
    this->MFLAG = MFLAG;
}

string Symbol::GetLabel()
{
    return label;
}

string Symbol::GetValue()
{
    return value;
}

bool Symbol::GetRFLAG()
{
    return RFLAG;
}

bool Symbol::GetIFLAG()
{
    return IFLAG;
}

bool Symbol::GetMFLAG()
{
    return MFLAG;
}

Symbol::~Symbol()
{
    /* not currently implemented */
}