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
        string GetName();
        string GetOpcode();
        int GetFormat();

        /* setters */
        void SetName(string);
        void SetOpcode(string);
        void SetFormat(int);

        /* destructor */
        ~Opcode();

    private:
        string name;
        string opcode;
        int format;
};

#endif