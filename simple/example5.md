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

