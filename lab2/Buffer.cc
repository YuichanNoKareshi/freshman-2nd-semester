#include <fstream>
#include <iostream>
#include "Buffer.h"

Buffer::Buffer()
{
    currentLine = maxLine = 0;
}
Buffer::~Buffer()
{
}
void Buffer::moveToPrevLine()
{
    if (currentLine <= 1)
        throw out_of_range("Line number out of range");
    currentLine--;
}
string Buffer::moveToLine(int lineNum)
{
    if (lineNum <= 0 || lineNum > maxLine)
        throw out_of_range("Line number out of range");
    currentLine = lineNum;
    return lines[lineNum];
}

void Buffer::writeToFile(const string &filename) const
{
    // TODO: write lines to the file and output the number of bytes written.
    ofstream file1;
    file1.open(filename);
    int num=0;
    for (int i=0;i<maxLine;i++) 
    {
    
        file1<<lines[i]<<'\n';
        num+=lines[i].length();
         
    }
    
    if (lines[maxLine]!="\0") 
    {file1<<lines[maxLine];
    num+=lines[maxLine].length();}
    cout<<"the number of bytes is "<<num<<endl;
}

void Buffer::showLines(int start, int end) const
{
    // TODO: print lines according to the requirement.
    if (start<0 || end>maxLine) 
      throw out_of_range("Number range error");
    for (int i=start;i<=end;i++) cout<<i<<'\t'<<lines[i]<<'\n';
}
void Buffer::deleteLines(int start, int end)
{
    if (start <= 0 || end > maxLine || start > end)
        throw range_error("Delete range error");
    for (int i = end + 1; i <= maxLine; ++i) {
        lines[i - end - 1 + start] = lines[i];
    }
    maxLine -= end - start + 1;
}

void Buffer::insertLine(const string &text)
{
    // TODO: insert a line to current line.
        for (int i=maxLine;i>=currentLine;i--) lines[i+1]=lines[i];
        lines[currentLine]=text;
        maxLine++;
        currentLine++;
}

void Buffer::appendLine(const string &text)
{
    if (maxLine >= MAX_LINE)
        throw out_of_range("move beyond the file line limit");
    for (int i = maxLine; i > currentLine; i--) {
        lines[i + 1] = lines[i];
    }
    lines[currentLine + 1] = text;
    currentLine++;
    maxLine++;
}