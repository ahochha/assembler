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
    bool is_literal = false;

    /* skip spaces at begining of attribute */
    while (line[current_char] == ' ') {
        current_char++;
    }

    if (line[current_char] == '=') {
        is_literal = true;
    }

    /* copy filtered file_line substring over to attribute */
    while (line[current_char] != ' ' && current_char < line.size()) {      
        if (is_literal) {
            attribute.push_back(line[current_char]);
        }
        else {
            attribute.push_back(toupper(line[current_char]));
        }

        attr_char++;
        current_char++;
    }

    return attribute;
}

bool FileHandler::IsCommentLine(string file_line)
{
    bool isComment = false;

    /* $ is the comment character */
    for(char &c: file_line) {
        if(c != ' ' && c != '$') {
            break;
        }
        else if (c == '$') {
            isComment = true;
        }
    }

    if (file_line.size() == 0) {
        isComment = true;
    }

    return isComment;
}

FileHandler::~FileHandler()
{

}