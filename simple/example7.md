# Simple example

## Using the copy constructor
```cpp
//  CopyConstructor - demonstrate a copy constructor
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    // conventional constructor
    Student(const char *pName = "no name", int ssId = 0)
      : name(pName), id(ssId)
    { cout << "Constructed "  << name << endl; }
    // copy constructor
    Student(const Student& s)
      : name("Copy of " + s.name), id(s.id)
    { cout << "Constructed "  << name << endl; }
    ~Student() { cout << "Destructing " << name << endl; }
  protected:
    string name;
    int  id;
};
// fn - receives its argument by value
void fn(Student copy)
{
  cout << "In function fn()" << endl;
}
int main(int nNumberofArgs, char* pszArgs[])
{
  Student scruffy("Scruffy", 1234);
  cout << "Calling fn()" << endl;
  fn(scruffy);
  cout << "Back in main()" << endl;
  // wait until user is ready before terminating program
  // to allow the user to see the program results
  cout << "Press Enter to continue..." << endl;
  cin.ignore(10, '\n');
  cin.get();
  return 0;
}

/*
Constructed Scruffy
Calling fn()
Constructed Copy of Scruffy
In function fn()
Destructing Copy of Scruffy
Back in main()
Press Enter to continue...
*/
```

## The Automatic Copy Constructor
```cpp
class Student
{
  public:
    // conventional constructor
    Student(const char *pName = "no name", int ssId = 0)
      : name(pName), id(ssId)
    { cout << "Constructed "  << name << endl; }
    // copy constructor
    Student(const Student& s)
      : name("Copy of " + s.name), id(s.id)
    { cout << "Constructed "  << name << endl; }
    ~Student() { cout << "Destructing " << name << endl; }
  protected:
    string name;
    int  id;
};
class Tutor
{
  public:
    Tutor(Student& s)
       : student(s), id(0)
    { cout << "Constructing Tutor object" << endl; }
  protected:
    Student student;
    int id;
};
void fn(Tutor tutor)
{
    cout << "In function fn()" << endl;
}
int main(int argcs, char* pArgs[])
{
    Student scruffy("Scruffy");
    Tutor tutor(scruffy);
    cout << "Calling fn()" << endl;
    fn(tutor);
    cout << "Back in main()" << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Constructed Scruffy
Constructed Copy of Scruffy
Constructing Tutor object
Calling fn()
Constructed Copy of Copy of Scruffy
In function fn()
Destructing Copy of Copy of Scruffy
Back in main()
Press Enter to continue...
Destructing Copy of
*/
```
