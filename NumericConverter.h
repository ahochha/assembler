/* used to convert between hex and decimal */

#ifndef NumericConverter_h
#define NumericConverter_h

#include <string>
using namespace std;

class NumericConverter
{
    public:
        /* constructor */
        NumericConverter();

        /* functions */
        int htod(string);
        string dtoh(int);

        /* destructor */
        ~NumericConverter();
};

#endif