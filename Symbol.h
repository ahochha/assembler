/* used to represent symbols read in from SYMS.DAT */

#ifndef Symbol_h
#define Symbol_h

#include <string>
using namespace std;

class Symbol 
{
    public:
        /* constructor */
        Symbol();

        /* getters */
        string GetName();
        int GetValue();
        bool GetRFLAG();
        bool GetIFLAG();
        bool GetMFLAG();

        /* setters */
        void SetName(string);
        void SetValue(string);
        void SetRFLAG(bool);
        void SetIFLAG(bool);
        void SetMFLAG(bool);

        /* destructor */
        ~Symbol();

    private:
        string name;
        int value;
        bool RFLAG;
        bool IFLAG;
        bool MFLAG;
};

#endif