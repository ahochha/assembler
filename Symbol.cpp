#include <string>
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

void Symbol::SetLabel(string _label)
{
    label = _label;
}

void Symbol::SetValue(string _value)
{
    value = _value;
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