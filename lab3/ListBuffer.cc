#include <fstream>
#include <iostream>
#include "ListBuffer.h"

//TODO: your code here
//implement the functions in ListBuffer
ListBuffer::ListBuffer()
{
    head=new listnode();
}
ListBuffer::~ListBuffer()
{
}


void ListBuffer::writeToFile(const string &filename) const
{
    ofstream file1;
    file1.open(filename);
    listnode *temp=head->next;
    while (true) 
    {
        file1<<temp->num<<" "<<temp->x<<'\n';
        if (temp->next==NULL) break;
        temp=temp->next;
    }
}

void ListBuffer::showLines() const
{
  if (head->next==NULL) {cout<<"?There is no sentence.\n";return;}
  listnode *temp=head->next;
    while (true) 
    {
        cout<<temp->num<<" "<<temp->x<<'\n';
        if (temp->next==NULL) break;
        temp=temp->next;
    }
}

void ListBuffer::deleteLine(int line_idx)
{
 listnode *temp=head;
 while (true)
 {
  temp=temp->next;   
  if (line_idx==temp->num) 
  {
   listnode *p=head;
   while (p->next!=temp) p=p->next; 
   p->next=temp->next;
   delete temp;
   break;
  } 
  if (temp->next==NULL) 
  {
   throw range_error("delete range error"); 
   break;
  }
 }
}

void ListBuffer::insertLine(int line_idx, const string &text)
{
 listnode *temp=head;
 if (temp->next==NULL) 
 {
  temp->next=new listnode;
  temp->next->x=text;
  temp->next->num=line_idx;
  return;
 }
 
 if ((temp->next->num)==line_idx) {temp->next->x=text;return;}
 
 if ((temp->next->num)>line_idx) 
 {
  listnode *p=new listnode;   
  p->x=text;
  p->num=line_idx;
  p->next=head->next;
  head->next=p;
  return;
 }

 while (true) 
 {
  temp=temp->next; 

  if (temp->next==NULL) 
  {
   temp->next=new listnode;
   temp->next->num=line_idx;
   temp->next->x=text;
   break;   
  } 
  
  if ((temp->next->num)==line_idx) {temp->next->x=text;break;}
  
  if ((temp->next->num)<line_idx) continue;

  if ((temp->next->num)>line_idx) 
  {listnode *p=new listnode; 
   p->x=text;
   p->num=line_idx;
   p->next=temp->next;
   temp->next=p;
   break;
  }
 }
}


