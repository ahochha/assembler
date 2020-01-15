/* used to represent symbols read in from SYMS.DAT */

#ifndef Instruction_h
#define Instruction_h

#include <string>
using namespace std;

class Instruction
{
    public:
        /* constructor */
        Instruction();

        /* getters */
        string GetLabel();
        string GetOperation();
        string GetOperand();
        int GetLocationCounter();

        /* setters */
        void SetLabel(string);
        void SetOperation(string);
        void SetOperand(string);
        void SetLocationCounter(string);

        /* destructor */
        ~Instruction();

    private:
        string label;
        string operation;
        string operand;
        int location_counter;
};

#endif