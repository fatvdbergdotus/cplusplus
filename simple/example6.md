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

