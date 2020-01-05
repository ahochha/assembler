#include <string>
#include "Symbol.h"
using namespace std;

Symbol::Symbol()
{
    name = "";
    value = -99;
    RFLAG = false;
    IFLAG = false;
    MFLAG = false;
}

void Symbol::SetName(string _name)
{
    name = _name;
}

void Symbol::SetValue(string _value)
{
    value = stoi(_value);
}

void Symbol::SetRFLAG(bool _rflag)
{
    RFLAG = _rflag;
}

void Symbol::SetIFLAG(bool _iflag)
{
    IFLAG = _iflag;
}

void Symbol::SetMFLAG(bool _mflag)
{
    MFLAG = _mflag;
}

string Symbol::GetName()
{
    return name;
}

int Symbol::GetValue()
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