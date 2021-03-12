#pragma once

#include <string>

using namespace std;

class ListBuffer {
private:
    //TODO: add a List here for storing the input lines
    class listnode
    { 
    public:  
      string x;
      int num;
      listnode *next; 
      listnode():next(NULL) {}; 
    };
    listnode *head;
    
public:
    ListBuffer();
    ~ListBuffer();

    void writeToFile(const string &filename) const;

    void showLines() const;
    void deleteLine(int line_idx);
    void insertLine(int line_idx, const string &text);
};
