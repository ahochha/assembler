/* used to handle operations pertaining to files */

#ifndef FileHandler_h
#define FileHandler_h

#include <string>
#include <vector>
using namespace std;

class FileHandler
{
    public:
        /* constructor */
        FileHandler();

        /* functions */
        string ReadAttribute();
        bool IsCommentLine();

        /* destructor */
        ~FileHandler();

    private:
        void SkipBeginningSpaces();
};

#endif