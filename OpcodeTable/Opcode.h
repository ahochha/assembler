/* used to represent opcodes read in from OPCODES.DAT */

#ifndef Opcode_h
#define Opcode_h

#include <string>
using namespace std;

class Opcode
{
    public:
        /* constructor */
        Opcode();

        /* getters */
        string GetOperation();
        string GetCode();
        int GetFormat();

        /* setters */
        void SetOperation(string);
        void SetCode(string);
        void SetFormat(int);

        /* destructor */
        ~Opcode();

    private:
        string operation;
        string code;
        int format;
};

#endif