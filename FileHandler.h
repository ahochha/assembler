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

        /* getters */
        vector<string> GetLines();

        /* setters */
        void AddLine(string);

        /* functions */
        string ReadAttribute(string, int&);
        bool IsCommentLine(string);

        /* destructor */
        ~FileHandler();

    private:
        vector<string> lines;
};

#endif