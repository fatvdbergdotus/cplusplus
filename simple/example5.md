# Simple examples

## Class example: Student and grade point average
```cpp
//  CallMemberFunction - define and invoke a function
//               that's a member of the class Student
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    // add a completed course to the record
    double addCourse(int hours, double grade)
    {
        // calculate the sum of all courses times
        // the average grade
        double weightedGPA;
        weightedGPA = semesterHours * gpa;
        // now add in the new course
        semesterHours += hours;
        weightedGPA += grade * hours;
        gpa = weightedGPA / semesterHours;
        // return the new gpa
        return gpa;
    }
    int  semesterHours;
    double gpa;
};
int main(int nNumberofArgs, char* pszArgs[])
{
    // create a Student object and initialize it
    Student s;
    s.semesterHours = 3;
    s.gpa = 3.0;
    // the values before the call
    cout << "Before: s = (" << s.semesterHours
         << ", " << s. gpa  << ")" << endl;
    // the following subjects the data members of the s
    // object to the member function addCourse()
    cout << "Adding 3 hours with a grade of 4.0" << endl;
    s.addCourse(3, 4.0); // call the member function
    // the values are now changed
    cout << "After: s = (" << s.semesterHours
         << ", " << s. gpa  << ")" << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Class exampling: using a .h (including definition) and .cpp file
The Savings.h is as follows.

```cpp
// Savings - define a class that includes the ability
//           to make a deposit
class Savings
{
  public:
    // define a member function deposit()
    double deposit(double amount)
    {
        balance += amount;
        return balance;
    }
    unsigned int accountNumber;
    double  balance;
};
```

The Saving.cpp is as follows.

```cpp
//
//  SavingsClassInline - invoke a member function that's
//                       both declared and defined within
//                       the class Student
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Savings.h"
int main(int nNumberofArgs, char* pszArgs[])
{
    Savings s;
    s.accountNumber = 123456;
    s.balance = 0.0;
    // now add something to the account
    cout << "Depositing 10 to account "
         << s.accountNumber << endl;
    s.deposit(10);
    cout << "Balance is " << s.balance << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Class exampling: using a .h and .cpp (including definition) file
The Saving.cpp is as follows.

```cpp
// Savings - define a class that includes the ability
//           to make a deposit
class Savings
{
  public:
    // declare but don't define member function
    double deposit(double amount);
};
```

The Saving.cpp is as follows.

```cpp
//  SavingsClassOutline - invoke a member function that's
//                        
declared within a class but
//                        
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Savings.h"
defined in a separate file
// define the member function Savings::deposit()
// (normally this is contained in a separate file that is
// then combined with a different file that is combined)
double Savings::deposit(double amount)
{
  balance += amount;
  return balance;
}
// the main program
int main(int nNumberofArgs, char* pszArgs[])
{
    Savings s;
    s.accountNumber = 123456;
    s.balance = 0.0;
    // now add something to the account
    cout << "Depositing 10 to account "
         << s.accountNumber << endl;
    s.deposit(10);
    cout << "Balance is " << s.balance << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Declaring pointers to objects
```cpp
// ObjPtr - define and use a pointer to a Student object
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    int  semesterHours;
    double gpa;
    double addCourse(int hours, double grade);
};
int main(int argc, char* pArgs[])
{
    // create a Student object
    Student s;
    s.gpa = 3.0;
    // now create a pointer pS to a Student object
    Student* pS;
    // make pS point to our Student object
    pS = &s;
    // now output the gpa of the object, once thru
    // the variable name and a second time thru pS
    cout << "s.gpa   = " << s.gpa   << "\n"
         << "pS->gpa = " << pS->gpa << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;

    // note:  ps->gpa is equivalent to(*pS).gpa
}
```

## Calling a function with an object value

### Without pointer
```cpp
// PassObjVal - attempts to change the value of an object
//              in a function fail when the object is
//              passed by value
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    int  semesterHours;
    double gpa;
};
void someFn(Student copyS)
{
    copyS.semesterHours = 10;
    copyS.gpa           = 3.0;
    cout << "The value of copyS.gpa = "<<copyS.gpa<< endl;
}
int main(int argc, char* pArgs[])
{
    Student s;
    s.gpa = 0.0;
    // display the value of s.gpa before calling someFn()
    cout << "The value of s.gpa = " << s.gpa << endl;
    // pass the address of the existing object
    cout << "Calling someFn(Student)" << endl;
    someFn(s);
    cout << "Returned from someFn(Student)" << endl;
    // the value of s.gpa remains 0
    cout << "The value of s.gpa = " << s.gpa << endl;
    // wait until user is ready before terminating program
// to allow the user to see the program results
cout << "Press Enter to continue..." << endl;
cin.ignore(10, '\n');
cin.get();
return 0;
}

/* OUTPUT:
The value of s.gpa = 0
Calling someFn(Student)
The value of copyS.gpa = 3
Returned from someFn(Student)
The value of s.gpa = 0
Press Enter to continue...
*/

### With pointer
```cpp
// PassObjPtr - change the contents of an object in
//              
a function by passing a pointer
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
public:
int  semesterHours;
double gpa;
};
void someFn(Student* pS)
{
pS->semesterHours = 10;
    pS->gpa           = 3.0;
    cout << "The value of pS->gpa = " << pS->gpa << endl;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    Student s;
    s.gpa = 0.0;
    // display the value of s.gpa before calling someFn()
    cout << "The value of s.gpa = " << s.gpa << endl;
    // pass the address of the existing object
    cout << "Calling someFn(Student*)" << endl;
    someFn(&s);
    cout << "Returned from someFn(Student*)" << endl;
    // the value of s.gpa is now 3.0
    cout << "The value of s.gpa = " << s.gpa << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/*
The value of s.gpa = 0
Calling someFn(Student*)
The value of pS->gpa = 3
Returned from someFn(Student*)
The value of s.gpa = 3
Press Enter to continue...
*/
```

### By reference
```cpp
// PassObjRef - change the contents of an object in
//              a function by using a reference
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    int  semesterHours;
    double gpa;
};
// same as before, but this time using references
void someFn(Student& refS)
{
    refS.semesterHours = 10;
    refS.gpa      = 3.0;
    cout << "The value of copyS.gpa = " <<refS.gpa<< endl;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    Student s;
    s.gpa = 0.0;
    // display the value of s.gpa before calling someFn()
    cout << "The value of s.gpa = " << s.gpa  << endl;
    // pass the address of the existing object
    cout << "Calling someFn(Student*)" << endl;
    someFn(s);
    cout << "Returned from someFn(Student&)" << endl;
    // the value of s.gpa is now 3.0
    cout << "The value of s.gpa = " << s.gpa << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

## Store data in a linked list of objects
```cpp
// LinkedListData - store data in a linked list of objects
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// NameDataSet - stores a person's name (these objects
//               
could easily store any other information
//               
desired).
class NameDataSet
{
public:
string sName;
// the link to the next entry in the list
NameDataSet* pNext;
};
// the pointer to the first entry in the list
NameDataSet* pHead = nullptr;
// add - add a new member to the linked list
void add(NameDataSet* pNDS)
{
    // point the current entry to the beginning of list
    pNDS->pNext = pHead;
    // point the head pointer to the current entry
    pHead = pNDS;
}
// getData - read a name and social security
//           number; return null if no more to read
NameDataSet* getData()
{
    // read the first name
    string name;
    cout << "Enter name:";
    cin  >> name;
    // if the name entered is 'exit'...
    if (name == "exit")
    {
        // ...return a null to terminate input
        return nullptr;
    }
    // get a new entry and fill in values
    NameDataSet* pNDS = new NameDataSet;
    pNDS->sName = name;
    pNDS->pNext = nullptr; // zero link
    // return the address of the object created
    return pNDS;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    cout << "Read names of students\n"
         << "Enter 'exit' for first name to exit"
         << endl;
    // create (another) NameDataSet object
    NameDataSet* pNDS;
    while (pNDS = getData())
    {
        // add it to the list of NameDataSet objects
        add(pNDS);
    }
    // to display the objects, iterate through the
    // list (stop when the next address is NULL)
    cout << "\nEntries:" << endl;
    for(NameDataSet *pIter = pHead;
                       pIter; pIter = pIter->pNext)
    {
        // display name of current entry
        cout << pIter->sName << endl;
   }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```


