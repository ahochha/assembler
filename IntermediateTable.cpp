#include <iostream>
#include <iomanip>
#include "IntermediateTable.h"
using namespace std;

IntermediateTable::IntermediateTable()
{
    /* not currently implemented */
}

void IntermediateTable::ProcessFile(ifstream &ASM_file)
{
    string file_line = "";
    int line_num = 1;

    while (getline(ASM_file, file_line)) {
        if (!IsCommentLine(file_line)) {
            AddLine(file_line);
            ProcessInstruction(line_num, file_line);
        }
        line_num++;
    }
}

void IntermediateTable::ProcessInstruction(int line_num, string file_line)
{
    vector<Error> errors;
    Instruction temp_inst;

}

IntermediateTable::~IntermediateTable()
{
    /* not currently implemented */
}