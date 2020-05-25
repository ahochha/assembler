#include <string>
#include <vector>
#include "Resources.h"
#include "FileHandler.h"
using namespace std;

FileHandler::FileHandler()
{

}

string FileHandler::ReadAttribute()
{
    string attribute = "";
    bool is_literal = false;

    SkipBeginningSpaces();

    if (resources::current_line[resources::current_char] == '=') 
    {
        is_literal = true;
    }

    /* copy filtered file_line substring over to attribute */
    while (resources::current_line[resources::current_char] != ' ' && resources::current_char < resources::current_line.size()) 
    {      
        if (is_literal) 
        {
            attribute.push_back(resources::current_line[resources::current_char]);
        }
        else 
        {
            attribute.push_back(toupper(resources::current_line[resources::current_char]));
        }

        resources::current_char++;
    }

    return attribute;
}

void FileHandler::SkipBeginningSpaces() 
{
    /* skip spaces at begining of attribute */
    while (resources::current_line[resources::current_char] == ' ') 
    {
        resources::current_char++;
    }
}

bool FileHandler::IsCommentLine()
{
    bool isComment = false;

    /* $ is the comment character */
    for (char &c: resources::current_line) 
    {
        if (c != ' ' && c != '$') 
        {
            break;
        }
        else if (c == '$') 
        {
            isComment = true;
        }
    }

    if (resources::current_line.size() == 0) 
    {
        isComment = true;
    }

    return isComment;
}

FileHandler::~FileHandler()
{

}