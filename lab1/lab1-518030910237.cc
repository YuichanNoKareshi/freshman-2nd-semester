#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;

template<class T>
class Class {
private:
    T **students;
    int count;
    int capacity;
public:
    Class(int number) {
        students = new T*[number];
        count = 0;
        capacity = number;
    }
    void addStudent(T *student) {
        if (count >= capacity)
            throw out_of_range("Too many students in the class");
        students[count++] = student;
    }
    void takeAttendance() {
        for (int i=0;i<count;i++) students[i]->signup();
    }
    ~Class() {
        delete[] students;
    }
};

class Student
{
protected:
    string id;
public:    
    virtual void signup() =0;
    Student () {};    
};

class Graduate:public Student
{
public:
    Graduate (string str){id=str;}
    virtual void signup () {cout<<"Graduate student "<<id<<endl;}   
};

class Undergraduate:public Student
{
public:
    Undergraduate(string str) {id=str;}
    virtual void signup () {cout<<"Undergraduate student "<<id<<endl;}   
};

int main()
{
    Class<Graduate> advanced_class(12);
    Class<Undergraduate> basic_class(81);
    Class<Student> common_class(108);
    Graduate *graduate_students[12];
    Undergraduate *undergraduate_students[81];

    for (int i = 0; i < 12; ++i) {
        stringstream ss;
        ss << "B18037" << std::setfill('0') << setw(2) << i;
        graduate_students[i] = new Graduate(ss.str());
    }
    for (int i = 0; i < 81; ++i) {
        stringstream ss;
        ss << "F18037" << std::setfill('0') << setw(2) << i;
        undergraduate_students[i] = new Undergraduate(ss.str());
    }

    // Add graduate students to advanced_class
    for (int i = 0; i < 12; ++i) {
        advanced_class.addStudent(graduate_students[i]);
    }
    // TODO: Add undergraduate students for basic_class
    for (int i=0;i<81;i++)
    {
      basic_class.addStudent(undergraduate_students[i]);  
    }
    // TODO: Add all graduate students and undergrudate students to common_class
    for (int i=0;i<12;i++)
    {
      common_class.addStudent(graduate_students[i]);  
    }

    for (int i=0;i<81;i++)
    {
      common_class.addStudent(undergraduate_students[i]);  
    }
    // TOOD: call takeAttendance on all three classes
    cout<<"common class's signup starts"<<endl;
    common_class.takeAttendance();
    cout<<"\nadvanced class's signup starts"<<endl;
    advanced_class.takeAttendance();
    cout<<"\nbasic class's signup starts"<<endl;
    basic_class.takeAttendance();
    return 0;
}