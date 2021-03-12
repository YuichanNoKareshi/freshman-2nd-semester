#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    delete buffer;
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.
    string text;
    while (true)
    {
        getline(cin,text);
        if (buffer->maxLine >= buffer->MAX_LINE)
          throw out_of_range("move beyond the file line limit");
        if (text==".") break;
        if (buffer->currentLine==buffer->maxLine && buffer->lines[0] != "\0" ) 
        {
            buffer->currentLine++;
            buffer->maxLine++;
            buffer->lines[buffer->currentLine]=text;
        }
        if (buffer->currentLine==0 && buffer->maxLine==0) buffer->lines[0]=text;
        if (buffer->maxLine!=buffer->currentLine)
        {
            for (int i=buffer->maxLine;i>=buffer->currentLine+1;i--) buffer->lines[i+1]=buffer->lines[i];
            buffer->lines[buffer->currentLine+1]=text;
            buffer->currentLine++;
            buffer->maxLine++;
        } 
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    int i=0;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".") break;
        buffer->insertLine(text);
        i++;
    }
    buffer->currentLine-=i;
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        char *arr;
        arr=new char [cmd.length()-1];
        for (int i=0;i<cmd.length()-1;i++) arr[i]=cmd[i+2];
        string filename;
        filename=arr;
        cmdWrite(filename);
        return;
    }
    // TODO: handle special case "show".
    if (cmd=="show") 
    {
        if (buffer->lines[buffer->maxLine]=="\0") buffer->showLines(0,buffer->maxLine-1);
        else    buffer->showLines(0,buffer->maxLine);
        return;
    }    
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
    }
    throw "Bad/Unknown command";
}
