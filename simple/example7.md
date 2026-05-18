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

Destructing Copy of Scruffy
Destructing Scruffy
*/
```

## Creating Shallow Copies versus Deep Copies

### Shallow copy
```cpp
//  ShallowCopy - performing a byte-by-byte (shallow) copy
//                is not correct when the class holds assets
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Person
{
  public:
    Person(const char *pN)
    {
        cout << "Constructing " << pN << endl;
        pName = new string(pN);
    }
    ~Person()
    {
        cout << "Destructing " << pName
             << " (" << *pName << ")" << endl;
        *pName = "already destructed memory";
        // delete pName;
    }
protected:
    string *pName;
};
void fn()
{
    // create a new object
    Person p1("This_is_a_very_long_name");
    // copy the contents of p1 into p2
    Person p2(p1);
}
int main(int argcs, char* pArgs[])
{
    cout << "Calling fn()" << endl;
    fn();
    cout << "Back in main()" << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
 Calling fn()
Constructing This_is_a_very_long_name
Destructing 0x3f2bb8 (This_is_a_very_long_name)
Destructing 0x3f2bb8 (already destructed memory)
Back in main()
Press Enter to continue...
*/
```

### Deep copy
```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Person
{
  public:
    Person(const char *pN)
    {
        cout << "Constructing " << pN << endl;
        pName = new string(pN);
    }
    Person(Person& person)
    {
        cout << "Copying " << *(person.pName) << endl;
        pName = new string(*person.pName);
    }
    ~Person()
    {
        cout << "Destructing " << pName
             << " (" << *pName << ")" << endl;
        *pName = "already destructed memory";
        // delete pName;
    }
protected:
    string *pName;
}
void fn()
{
    // create a new object
    Person p1("This_is_a_very_long_name");
    // copy the contents of p1 into p2
    Person p2(p1);
}
int main(int argcs, char* pArgs[])
{
    cout << "Calling fn()" << endl;
    fn();
    cout << "Back in main()" << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Calling fn()
Constructing This_is_a_very_long_name
Copying This_is_a_very_long_name
Destructing 0x9f2be0 (This_is_a_very_long_name)
Destructing 0x9f2ba0 (This_is_a_very_long_name)
Back in main()
Press Enter to continue...
*/
```

## Moving temporary rather than creating a copy constructor
```cpp
//
//  MoveCopy  - demonstrate the principle of moving a
//              
temporary rather than creating a copy
.
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Person
{
  public:
    Person(const char *pN)
    {
        pName = new string(pN);
        cout << "Constructing " << *pName << endl;
    }
    Person(Person& p)
    {
        cout << "Copying " << *p.pName << endl;
        pName = new string("Copy of ");
        *pName += *p.pName;
    }
    Person(Person&& p)
    {
        cout << "Moving " << *p.pName << endl;
        pName = p.pName;
        p.pName = nullptr;
    }
    ~Person()
    {
        if (pName)
        {
            cout << "Destructing " << *pName << endl;
            delete pName;
        }
        else
        {
            cout << "Destructing null object" << endl;
        }
    }
protected:
    string* pName;
};
Person fn2(Person p)
{
  cout << "Entering fn2" << endl;
  return p;
}
Person fn1(char* pName)
{
  cout << "Entering fn1" << endl;
  return fn2(*new Person(pName));
}
int main(int argcs, char* pArgs[])
{
  Person s(fn1("Scruffy"));
  // wait until user is ready before terminating program
  // to allow the user to see the program results
  cout << "Press Enter to continue..." << endl;
  cin.ignore(10, '\n');
  cin.get();
  return 0;
}

/* OUTPUT:
Entering fn1
Constructing Scruffy
Copying Scruffy
Entering fn2
Moving Copy of Scruffy
Destructing null object
Press Enter to continue...
Destructing Copy of Scruffy
*/
```
