#include "termio.h"

// Do not delete the following 3 lines
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
int Termio::MAX_WIDTH;
int Termio::MAX_HEIGHT;

void write_hi() {
    for (int i = 0; i < 5; i++) {
        Termio::buffer[i][0] = '|';
        Termio::buffer[i][5] = '|';
        Termio::buffer[i][9] = '|';
        Termio::buffer[i][13] = '*';
    }
    Termio::buffer[3][13] = ' ';
    Termio::buffer[1][9] = ' ';
    for (int i = 1; i < 5; i++) {
        Termio::buffer[2][i] = '-';
    }
}

class Stack
//记录用户操作的栈
{
 private:
  struct node
  {
   int from;
   int to;
   
   node *next;
   node (const int &a,const int &b,node *c=NULL)
   {from=a;to=b;next=c;}
   node ():next(NULL) {};
   ~node () {};
  };
  
 
 public:
   int length=0;
   node *top_p;
   void push(const int &a,const int &b);
   void pop(int &x,int &y);
   Stack () {top_p=NULL;}
   ~Stack () {};
};
//定义栈的函数
void Stack::push(const int &a,const int &b)
{
 top_p=new node (a,b,top_p);
 length++;
}
void Stack::pop(int &x,int &y)
{
 node *temp=top_p;
 top_p=top_p->next;
 x=temp->to;
 y=temp->from;
 delete temp;
 length--;
}

class Tower
//记录汉诺塔的形状
{
 private:
  int *disk;//记录各个盘位置的数组,第五个盘为最大的盘
  int num;//记录盘的个数
 public:
  Tower(){num=0;disk=NULL;}
  Tower (const int &x)
  {num=x;disk=new int [num];for (int i=0;i<num;i++) disk[i]=1;}  
  ~Tower () {} ;
  void setbuffer();
  bool isWin ();
  bool move(int x,int y);
  void solve(int n,int a,int b,int c);
};

bool Tower::isWin ()
{
 bool flag=true;
 for (int i=0;i<num;i++) if (disk[i]!=3) flag=false;
 return flag;  
}
void Tower::setbuffer()
{
 for (int i=0;i<Termio::MAX_WIDTH;i++) Termio::buffer[Termio::MAX_HEIGHT-1][i]='-';
 for (int i=0;i<Termio::MAX_HEIGHT;i++)
 {
  Termio::buffer[i][5]='|';
  Termio::buffer[i][17]='|';
  Termio::buffer[i][29]='|';
 }
 
 for (int i=num-1;i>=0;i--)
 {
  int high=0;//记录这个盘是这个柱子的第几个盘（1~5）   
  for (int j=num-1;j>=i;j--) if (disk[j]==disk[i]) high++;
  switch (disk[i])
  {
   case 1:{for (int h=4-i;h<=6+i;h++) Termio::buffer[5-high][h]='*';break;}
   case 2:{for (int h=16-i;h<=18+i;h++) Termio::buffer[5-high][h]='*';break;}
   case 3:{for (int h=28-i;h<=30+i;h++) Termio::buffer[5-high][h]='*';break;}
  } 
 }
}
bool Tower::move(int x,int y)
{
 if (x<1||y<1||x>3||y>3) return false;
 int i=0;    
 while (disk[i]!=x) 
 {
  i++;
  if (i==num) return false;
 }
 
 int j=0;
 while (j<i)
 {
  if (disk[j]==y) return false;
  j++;
 }
 
 disk[i]=y;
 return true;
}
void Tower::solve(int n,int a,int b,int c)
{
 if (n==1) 
 {
  cout<<a<<' '<<c<<endl;
  move(a,c);   
  Termio::Clear();
  Termio::ResetBuffer(); 
  setbuffer();
  Termio::Draw();
 }
 else 
 {
  solve(n-1,a,c,b);
  
  cout<<a<<' '<<c<<endl;
  move(a,c);   
  Termio::Clear();
  Termio::ResetBuffer();
  setbuffer();
  Termio::Draw();
  
  solve(n-1,b,a,c);
 }
}

int main() {

    // ---- Example: how to use termio.h ----
    // clear screen
    //Termio::Clear();
    // reset buffer
    //Termio::ResetBuffer();
    //write_hi();
    //Termio::Draw();
    // ----------- End of example -----------
    // Your code here
int disks_num;
cout<<"How many disks do you want? (1~5)"<<endl;
cin>>disks_num;
while (disks_num>5||disks_num<1) 
 {
  cout<<"Range error! How many disks do you want? (1~5)"<<endl;
  cin>>disks_num;
 }
Termio::MAX_WIDTH=35;
Termio::MAX_HEIGHT=6;

int x,y;//记录用户的操作
Tower tower(disks_num);
Termio::Clear();
Termio::ResetBuffer();
tower.setbuffer();
Termio::Draw();
Stack stack;
while (!tower.isWin()) 
{
 cout<<"Move a disk.Format:x y"<<endl;
 cin>>x>>y;
 if (x==0&&y==0) //直接解决
 {
  while(stack.top_p!=NULL) 
  {
   stack.pop(x,y);
   cout<<x<<' '<<y<<endl;
   tower.move(x,y);   
   Termio::Clear();
   Termio::ResetBuffer();
   tower.setbuffer();
   Termio::Draw();
  }
  
  int q=1,p=2,w=3;
  tower.solve(disks_num,q,p,w);
  cout<<"Vectory!"<<endl;
  break;
 }//直接解决结束

 if (tower.move(x,y))
 {
  Termio::Clear();
  Termio::ResetBuffer();
  tower.setbuffer();
  Termio::Draw();
  stack.push(x,y);
  if (tower.isWin()) cout<<"Vectory!\nYou used "<<stack.length<<" steps to win."<<endl;
 }
 else {cout<<"You can't do this"<<endl;continue;}
 
}


return 0;
}
