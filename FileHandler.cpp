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

string FileHandler::GetLine(int line_num)
{
    return lines[line_num - 1];
}

void FileHandler::AddLine(string line)
{
    lines.push_back(CleanLine(line));
}

string FileHandler::CleanLine(string line)
{
    int current_char = 0;
    string cleaned_line = "";

    current_char = SkipBeginningSpaces(line, current_char);

    while (line[current_char] != '$' && current_char < line.size()) {
        cleaned_line.push_back(line[current_char]);
        current_char++;
    }

    return cleaned_line;
}

string FileHandler::ReadAttribute(string line, int& current_char)
{
    int attr_char = 0;
    string attribute = "";
    bool is_literal = false;

    current_char = SkipBeginningSpaces(line, current_char);

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

int FileHandler::SkipBeginningSpaces(string line, int current_char) 
{
    /* skip spaces at begining of attribute */
    while (line[current_char] == ' ') {
        current_char++;
    }

    return current_char;
}

bool FileHandler::IsCommentLine(string line)
{
    bool isComment = false;

    /* $ is the comment character */
    for(char &c: line) {
        if(c != ' ' && c != '$') {
            break;
        }
        else if (c == '$') {
            isComment = true;
        }
    }

    if (line.size() == 0) {
        isComment = true;
    }

    return isComment;
}

FileHandler::~FileHandler()
{

}