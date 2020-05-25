#include <string>
#include <vector>
#include <math.h>
#include "NumericConverter.h"
using namespace std;

NumericConverter::NumericConverter()
{
    /* not currently implemented */
}

/* hex to decimal */
int NumericConverter::htod(string hex)
{
    vector<int> number;
    int decimal = 0;
    
    for (char &c: hex) {
        switch (c) {
            case '0': number.push_back(0); break;
            case '1': number.push_back(1); break;
            case '2': number.push_back(2); break;
            case '3': number.push_back(3); break;            
            case '4': number.push_back(4); break;
            case '5': number.push_back(5); break;
            case '6': number.push_back(6); break;
            case '7': number.push_back(7); break;
            case '8': number.push_back(8); break;
            case '9': number.push_back(9); break;
            case 'A': number.push_back(10); break;
            case 'B': number.push_back(11); break;
            case 'C': number.push_back(12); break;
            case 'D': number.push_back(13); break;
            case 'E': number.push_back(14); break;
            case 'F': number.push_back(15); break;
        }
    }

    for (int i = 0, j = hex.length(); i < hex.length(); i++, j--) {
        decimal += number[i] * pow(16, static_cast<double>(j) - 1);
    }

    return decimal;
}

/* decimal to hex */
string NumericConverter::dtoh(int number)
{
    int remainder = 0;
    int quotient = 0;
    string hex = "";
    string hex_values[] = {"0", "1", "2", "3", "4", "5", "6", "7", 
        "8", "9", "A", "B", "C", "D", "E", "F"};

    if (number == 0) {
        hex = "0";
    }
    else {
        while (number != 0) {
            remainder = number % 16;
            number = number / 16;
            hex = hex_values[remainder] + hex;
        }
    }

    return hex;
}

NumericConverter::~NumericConverter()
{
    /* not currently implemented */ 
}