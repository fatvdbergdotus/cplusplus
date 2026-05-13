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

## Constructing and destructing a duplex
```cpp
//  DestructMembers - this program both constructs and
//                    destructs a set of data members
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Course
{
  public:
    Course()  { cout << "constructing course" << endl; }
    ~Course() { cout << "destructing course" << endl;  }
};
class Student
{
  public:
    Student() { cout << "constructing student" << endl;}
    ~Student() { cout << "destructing student" << endl; }
};
class Teacher
{
  public:
    Teacher()
    {
        cout << "constructing teacher" << endl;
        pC = new Course;
    }
    ~Teacher()
    {
        cout << "destructing teacher" << endl;
        delete pC;
    }
  protected:
    Course* pC;
};
class TutorPair
{
  public:
    TutorPair(){cout << "constructing tutorpair" << endl;}
   ~TutorPair(){cout << "destructing tutorpair" << endl; }
  protected:
    Student student;
    Teacher teacher;
};
TutorPair* fn()
{
    cout << "Creating TutorPair object in function fn()"
         << endl;
    TutorPair tp;
    cout << "Allocating TutorPair off the heap" << endl;
    TutorPair*  pTP = new TutorPair;
    cout << "Returning from fn()" << endl;
    return pTP;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    // call function fn() and then return the
    // TutorPair object returned to the heap
    TutorPair* pTPReturned = fn();
    cout << "Return heap object to the heap" << endl;
    delete pTPReturned;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
}
cin.ignore(10, '\n');
cin.get();

/* OUTPUT:
Creating TutorPair object in function fn()
constructing student
constructing teacher
constructing course
constructing tutorpair
Allocating TutorPair off the heap
constructing student
constructing teacher
constructing course
constructing tutorpair
Returning from fn()
destructing tutorpair
destructing teacher
destructing course
destructing student
Return heap object to the heap
destructing tutorpair
destructing teacher
destructing course
destructing student
Press Enter to continue...
*/
```

## Constructor with arguments
```cpp
//  ConstructorWArg - a class may pass along arguments
//                    to the members' constructors
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    Student(const char* pName)
    {
        cout << "constructing Student " << pName << endl;
        name = pName;
        semesterHours = 0;
        gpa = 0.0;
    }
  // ...other public members...
  protected:
    string  name;
    int     semesterHours;
    double  gpa;
};
int main(int argcs, char* pArgs[])
{
    // create a student locally and one off of the heap
    Student s1("Jack");
    Student* pS2 = new Student("Scruffy");
    // be sure to delete the heap student
    delete pS2;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Overloading the constructor
```cpp
//  OverloadConstructor - provide the class multiple
//                        ways to create objects by
//                        overloading the constructor
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;
class Student
{
  public:
    Student()
    {
        cout << "constructing student No Name" << endl;
        name = "No Name";
        semesterHours = 0;
        gpa = 0.0;
    }
    Student(const char *pName)
    {
        cout << "constructing student " << pName << endl;
        name = pName;
        semesterHours = 0;
        gpa = 0;
    }
    Student(const char *pName, int xfrHours, float xfrGPA)
    {
        cout << "constructing student " << pName << endl;
        name = pName;
        semesterHours = xfrHours;
        gpa = xfrGPA;
    }
  protected:
    string  name;
    int     semesterHours;
    float   gpa;
};
int main(int argcs, char* pArgs[])
{
    // the following invokes three different constructors
    Student noName;
    Student freshman("Marian Haste");
    Student xferStudent("Pikup Andropov", 80, 2.5);
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Constructor with defaults
```cpp
//  ConstructorWDefaults - multiple constructors can often
//                         be combined with the definition
//                         of default arguments
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    Student(const char *pName  = "No Name",
            int xfrHours = 0,
            double xfrGPA = 0.0)
    {
        cout << "constructing student " << pName << endl;
        name = pName;
        semesterHours = xfrHours;
        gpa = xfrGPA;
    }
  protected:
    string  name;
    int     semesterHours;
    double  gpa;
};

int main(int argcs, char* pArgs[])
{
    // the following invokes three different constructors
    Student noName;
    Student freshman("Marian Haste");
    Student xferStudent("Pikup Andropov", 80, 2.5);
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Constructors calling each other
```cpp
//  ConstructorsCallingEachOther - new for 2011,
//          one constructor can invoke another constructor
//          in the same class
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    Student(const char *pName,
            int xfrHours,
            double xfrGPA)
    {
        cout << "constructing student " << pName << endl;
        name = pName;
        semesterHours = xfrHours;
        gpa = xfrGPA;
    }
    Student() : Student("No Name", 0, 0.0) {}
    Student(const char *pName): Student(pName, 0, 0.0){}
  protected:
    string  name;
    int     semesterHours;
    double  gpa;
};

int main(int argcs, char* pArgs[])
{
    // the following invokes three different constructors
    Student noName;
    Student freshman("Marian Haste");
    Student xferStudent("Pikup Andropov", 80, 2.5);
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Constructing class members (counting class ID)
```cpp
//
//  ConstructingMembers - a class may pass along arguments
//                        
to the members' constructors
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int nextStudentId = 1000; // first legal Student ID
class StudentId
{
  public:
    // default constructor assigns id's sequentially
    StudentId()
    {
        value = nextStudentId++;
        cout << "Take next student id " << value << endl;
    }
    // int constructor allows user to assign id
    StudentId(int id)
    {
        value = id;
        cout << "Assign student id " << value << endl;
    }
  protected:
    int value;
};
class Student
{
  public:
    Student(const char* pName)
    {
        cout << "constructing Student " << pName << endl;
        name = pName;
        semesterHours = 0;
        gpa = 0.0;
    }
  // ...other public members...
  protected:
    string    name;
    int       semesterHours;
    double    gpa;
    StudentId id;
};
int main(int argcs, char* pArgs[])
{
    // create a couple of students
    Student s1("Jack");
Student s2("Scruffy");
// wait until user is ready before terminating program
// to allow the user to see the program results
cout << "Press Enter to continue..." << endl;
cin.ignore(10, '\n');
cin.get();
return 0;
}

/* OUTPUT:
Take next student id 1000
constructing Student Jack
Take next student id 1001
constructing Student Scruffy
Press Enter to continue...
*/
```

## Constructing class members (arbitrary class ID)
```cpp
//  ConstructMembersWithInitializers - this program
//          demonstrates what happens when a data member
//          with an initializer is constructed
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class StudentId
{
  public:
    StudentId(int id) : value(id)
    {
        cout << "id = " << value << endl;
    }
  protected:
    int value;
};
int nextStudentId = 1000;
class Student
{
  public:
    Student(const char *pName, int ssId)
      : name(pName), id(ssId)
    {
        cout << "constructing student " << pName << endl;
    }
    Student(const char *pName): name(pName)
    {
        cout << "constructing student " << pName << endl;
    }
  protected:
    string name;
    StudentId id = nextStudentId++;
};
int main(int argcs, char* pArgs[])
{
    Student s1("Jack", 1234);
Student s2("Scruffy");
// wait until user is ready before terminating program
// to allow the user to see the program results
cout << "Press Enter to continue..." << endl;
cin.ignore(10, '\n');
cin.get();
return 0;
}

/* OUTPUT:
id = 1234
constructing student Jack
id = 1000
constructing student Scruffy
Press Enter to continue..
*/

