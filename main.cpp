#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//global variables
const int LINE_SIZE = 80;

//prototypes
void GetFilename(const int, const char*[], string&);
vector<char> ConvertStringToVector(string);
void ProcessFileLine();

//used to represent symbols read in from SYMS.DAT
struct OneSymbol {
    vector<char> symbol;
    int value;
    bool RFLAG;
    bool IFLAG;
    bool MFLAG;
};

int main(const int argc, const char* argv[])
{
    ifstream SYMS_file;
	ifstream in_file;
    string filename;
    string file_line_str;
    vector<char> file_line;
    vector<vector<char>> lines;
    map<int, OneSymbol> symbol_table;

    SYMS_file.open("SYMS.DAT");

    GetFilename(argc, argv, filename);
    in_file.open(filename);

    if (!SYMS_file) {
        cerr << "SYMS.DAT was not found." << endl;
    }
    else {
        while (!getline(SYMS_file, file_line_str).eof()) {
            file_line = ConvertStringToVector(file_line_str);
            lines.push_back(file_line);
            ProcessFileLine();
        }
    }

    return 0;
}

void GetFilename(const int argc, const char* argv[], string &filename)
{
    if (argc == 1) {
        cout << "Enter source file name: ";      
        getline(cin, filename);
    }
    else {
        filename = string(argv[1]);
    }

    return;
}

vector<char> ConvertStringToVector(string line_str)
{
    vector<char> line(line_str.begin(), line_str.end());
    return line;
}

void ProcessFileLine()
{
    return;
}