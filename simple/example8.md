# Simple example

## Two ways to call a static member function
```cpp
// CallStaticMember - demonstrate two ways to call a
//                    static member function
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    Student(const char* pN = "no name") : sName(pN)
    {
        noOfStudents++;
    }
    ~Student() { noOfStudents--; }
    const string& name() { return sName; }
    static int number() { return noOfStudents; }
  protected:
    string sName;
    static int noOfStudents;
};
int Student::noOfStudents = 0;
int main(int argcs, char* pArgs[])
{
    // create two students and ask the class "how many?"
    Student s1("Chester");
    Student* pS2 = new Student("Scooter");
    cout << "Created " << s1.name()
         << " and "    << pS2->name() << endl;
    cout << "Number of students is "
         << s1.number() << endl;
    // now get rid of a student and ask again
    cout << "Deleting " << pS2->name() << endl;
    delete pS2;
    cout << "Number of students is "
         << Student::number() << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* Output:
  Created Chester and Scooter
  Number of students is 2
  Deleting Scooter
  Number of students is 1
  Press any key to continue...
*/
```

## This keyword
```cpp
// NameDataSet - stores a person's name (these objects
//               could easily store any other information
//               desired).
class NameDataSet
{
  public:
    NameDataSet(string& refName)
      : sName(refName), pNext(nullptr) {}
    // add self to beginning of list
    void add()
    {
        this->pNext = pHead;
        pHead = this;
    }
    // access methods
    static NameDataSet* first() { return pHead; }
           NameDataSet* next()  { return pNext; }
          const string& name()  { return sName; }
  protected:
    string sName;
    // the link to the first and next member of list
    static NameDataSet* pHead;
    NameDataSet* pNext;
};
// allocate space for the head pointer
NameDataSet* NameDataSet::pHead = nullptr;
```
