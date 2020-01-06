#include <string>
#include <vector>
#include "FileHandler.h"
using namespace std;

FileHandler::FileHandler()
{

}

vector<string> FileHandler::GetLines()
{
    return lines;
}

void FileHandler::AddLine(string line)
{
    lines.push_back(line);
}

string FileHandler::ReadAttribute(string line, int& current_char)
{
    int attr_char = 0;
    string attribute = "";

    /* skip spaces at begining of attribute */
    while (line[current_char] == ' ') {
        current_char++;
    }

    /* copy filtered file_line substring over to attribute */
    while (line[current_char] != ' ' && current_char < line.size()) {
        attribute.push_back(toupper(line[current_char]));
        attr_char++;
        current_char++;
    }

    return attribute;
}

FileHandler::~FileHandler()
{

}