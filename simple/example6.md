# Simple example

## Constructing a single object (2 ways)
```cpp
//  Constructor - example that invokes a constructor
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
public:
Student()
{
cout << "constructing student" << endl;
        semesterHours = 0;
        gpa = 0.0;
    }
    // ...other public members...
  protected:
    int  semesterHours;
    double gpa;
};
int main(int nNumberofArgs, char* pszArgs[])
{
    cout << "Creating a new Student object" << endl;
    Student s;
    cout << "Creating a new object off the heap" << endl;
    Student* pS = new Student;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Creating a new Student object
constructing student
Creating a new object off the heap
constructing student
Press Enter to continue...  
*/
```

## Constructing multiple objects
```cpp
//  ConstructArray - example that invokes a constructor
//                   on an array of objects
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    Student()
    {
        cout << "constructing student" << endl;
    }
};
int main(int nNumberofArgs, char* pszArgs[])
{
    cout << "Creating an array of 5 Student objects"
         << endl;
    Student s[5];
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Creating an array of 5 Student objects
constructing student
constructing student
constructing student
constructing student
constructing student
Press Enter to continue...
*/
```

## Constructing a duplex
If a class contains a data member that is an object of another class, the constructor for that class is called automatically as well. Consider the following ConstructMembers example program. I added output statements so that you can see the order in which the objects are invoked.

```cpp
//  ConstructMembers - the member objects of a class
//                     are each constructed before the
//                     container class constructor gets
//                     a shot at it
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Course
{
  public:
    Course(){ cout << "constructing course" << endl;}
};
class Student
{
  public:
    Student()
    {
        cout << "constructing student" << endl;
        semesterHours = 0;
        gpa = 0.0;
    }
  protected:
    int  semesterHours;
    double gpa;
};
class Teacher
{
  public:
    Teacher(){cout << "constructing teacher" << endl;}
  protected:
    Course c;
};
class TutorPair
{
  public:
    TutorPair()
    {
        cout << "constructing tutorpair" << endl;
        noMeetings = 0;
    }
  protected:
    Student student;
    Teacher teacher;
    int   noMeetings;
};
int main(int nNumberofArgs, char* pszArgs[])
{
    cout << "Creating TutorPair object" << endl;
    TutorPair tp;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Creating TutorPair object
constructing student
constructing course
constructing teacher
constructing tutorpair
Press Enter to continue...        
/*
```

