#include <iostream>
#include <cmath>
using namespace std;

class TreeNode
  {
   public:
   int X;
   int Y;
   TreeNode *left;
   TreeNode *right;
   int times=0;//中序遍历时进栈的次数
   TreeNode (const int &x,const int &y,TreeNode *a=NULL,TreeNode *b=NULL)
   {X=x;Y=y;left=a;right=b;}
   TreeNode () {left=NULL;right=NULL;} 
   int getX() {return X;}
   int getY() {return Y;}
   bool isLeft () {return left!=NULL;}
   bool isRight () {return right!=NULL;}
   ~TreeNode () {};
  };

class BinaryDimonTree
{
 private:
  
  TreeNode *root;
 
 public:
  TreeNode *search (int x,int y,TreeNode* m,float d);
  friend void run_testcase(string testcasename);
  BinaryDimonTree ():root(NULL) {};
  BinaryDimonTree (int x,int y) {root=new TreeNode(x,y);}
  void insert(int x, int y);
  TreeNode* find_nearest_node(int x, int y);
  void clear (TreeNode *&t);
  ~BinaryDimonTree();
};

class Stack
{
 private:
 struct node
 {
  TreeNode *x;
  node *next;
  node (TreeNode *&x,node *y=NULL)
  {this->x=x;next=y;}
  node():next(NULL) {};
  ~node (){}; 
 } ;
 node *head;
 
 public:
  void push(TreeNode *&x) {node *temp=new node(x,head->next); head->next=temp;}
  TreeNode* pop() {node *temp=head->next; TreeNode *a=temp->x; head->next=temp->next; delete temp; return a;}
  bool isEmpty () {return head->next==NULL;}
  Stack () {head=new node;}
  ~Stack() {};
};

Stack s;