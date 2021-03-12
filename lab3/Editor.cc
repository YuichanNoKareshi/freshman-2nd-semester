#include <iostream>
#include <sstream>
#include "Editor.h"
#include <cmath>

using namespace std;

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

void Editor::dispatchCmd(const string &cmd)
{
    /*
    TODO: your code here.
          cmd-1: non-negative integer + statement (e.g., 100 let a = b + c)
          cmd-2: delete (e.g., d 100)
          cmd-3: list   (e.g., lisT) 
          cmd-4: save as a file (e.g., save code.sh)
    */
   if (cmd[0]>='0'&&cmd[0]<='9')
   {
    int i=0;//i为数字的位数
    while (cmd[i]>='0'&&cmd[i]<='9') i++;
    if (cmd[i]!=' ') {throw "Bad/Unknown command";return;}
    if (i>10) {cout<<"range error!"<<endl;return;}
    int index=0;
    for (int j=0;j<i;j++) 
    {
        index+=cmd[j]-'0';
        if (j!=i-1) index*=10;else break;
        if (index*10-'0'+cmd[j+1]-2000000000>=147483647&&j+1!=i) {cout<<"range error!"<<endl;return;} 
        
    }
    string arr;
    arr=cmd.substr(i+1);
    buffer->insertLine(index,arr);
    return;
   }
   
   if (cmd[0]=='d'&&cmd[1]==' ')
   {
    if (cmd[1]!=' ') {throw "Bad/Unknown command";return;}
    int i=2;//i为数字的位数+2
    while (cmd[i]>='0'&&cmd[i]<='9') i++;
    int index=0;
    for (int j=2;j<i;j++) 
    {
        index+=cmd[j]-'0';
        if (j!=i-1) index*=10;else break;
        if (index*10-'0'+cmd[j+1]-2000000000>=147483647&&j+1!=i) {cout<<"range error!"<<endl;return;}
        
    }
    buffer->deleteLine(index);
    return;
   }

   if ((cmd[0]=='L'||cmd[0]=='l')&&(cmd[1]=='i'||cmd[1]=='I')&&(cmd[2]=='s'||cmd[2]=='S')&&(cmd[3]=='T'||cmd[3]=='t')) 
   {
    if (cmd[4]!='\0') {throw "Bad/Unknown command";return;}
    buffer->showLines();
    return;
   }

   if (cmd[0]=='s'&&cmd[1]=='a'&&cmd[2]=='v'&&cmd[3]=='e')
   {
    if (cmd[4]!=' ') {throw "Bad/Unknown command";return;}
    string arr;
    arr=cmd.substr(5);
    buffer->writeToFile(arr);  
    return; 
   }

   //异常抛出
    throw "Bad/Unknown command";
}

//TODO: add other code you want
Editor::Editor()
{
    buffer=new ListBuffer;
}

Editor::~Editor()
{   
};