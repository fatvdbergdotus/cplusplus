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

## Inheriting a class example
```cpp
//  InheritanceExample - demonstrate an inheritance
//               relationship in which the subclass
//               constructor passes argument information
//               to the constructor in the base class
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Advisor {}; // define an empty class
class Student
{
  public:
    Student(const char *pName = "no name")
       : name(pName), average(0.0), semesterHours(0)
    {
        cout << "Constructing student " << name << endl;
    }
    void addCourse(int hours, float grade)
    {
        cout << "Adding grade to " << name << endl;
        average = semesterHours * average + grade;
        semesterHours += hours;
        average = average / semesterHours;
    }
    int hours() { return semesterHours;}
    float gpa() { return average;}
  protected:
    string name;
    double average;
    int    semesterHours;
};
class GraduateStudent : public Student
{
  public:
    GraduateStudent(const char *pName, Advisor adv,
                    double qG = 0.0)
        : Student(pName), advisor(adv), qualifierGrade(qG)
    {
        cout << "Constructing graduate student "
             << pName << endl;
    }
    double qualifier() { return qualifierGrade; }
  protected:
    Advisor advisor;
    double qualifierGrade;
};
int main(int nNumberofArgs, char* pszArgs[])
{
    // create a dummy advisor to give to GraduateStudent
    Advisor adv;
    // create two Student types
    Student llu("Cy N Sense");
    GraduateStudent gs("Matt Madox", adv, 1.5);
    // now add a grade to their grade point average
    llu.addCourse(3, 2.5);
    gs.addCourse(3, 3.0);
    // display the graduate student's qualifier grade
    cout << "Matt's qualifier grade = "
         << gs.qualifier() << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* Output:
  Constructing student Cy N Sense
  Constructing student Matt Madox
  Constructing graduate student Matt Madox
  Adding grade to Cy N Sense
  Adding grade to Matt Madox
  Matt's qualifier grade = 1.5
  Press Enter to continue...
*/
```

## Examining virtual member functions (overload at compile time vs. runtime)

```cpp
//  OverloadOverride - demonstrate when a function is
//     overloaded at compile time vs. overriden at runtime
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Student
{
  public:
    // uncomment one or the other of the next
    // two lines; one binds calcTuition() early and
    // the other late
//          void calcTuition()
    virtual void calcTuition()
    {
        cout << "We're in Student::calcTuition" << endl;
    }
};
class GraduateStudent : public Student
{
  public:
    void calcTuition()
    {
      cout<<"We're in GraduateStudent::calcTuition"<<endl;
    }
};
void fn(Student& x)
{
    x.calcTuition(); // which calcTuition()?
}
int main(int nNumberofArgs, char* pszArgs[])
{
    // pass a base class object to function
    // (to match the declaration)
    Student s;
    fn(s);
    // pass a specialization of the base class instead
    GraduateStudent gs;
    fn(gs);
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
}

/* output (when virtual void calcTuition()):
  We're in Student::calcTuition
  We're in GraduateStudent::calcTuition
*/

/* output (when void calcTuition())
We're in Student::calcTuition
We're in Student::calcTuition
*/
```

## Implementing abstract classes
```cpp
// Account - this class is an abstract class
class Account
{
public:
  Account(unsigned accNo, double initialBalance = 0.0);
  // access functions
  unsigned int accountNo( );
  double acntBalance( );
  static int noAccounts( );
  // transaction functions
  void deposit(double amount);
  // the following is a pure virtual function
  virtual void withdrawal(double amount) = 0;
protected:
  // keep accounts in a linked list so there's no limit
  // to the number of accounts
  static int count;     
  // number of accounts
  unsigned accountNumber;
  double balance;
};
```

## overloading the assignment operator
```cpp
//DemoAssignmentOperator - demonstrate the assignment
//                        operator on a user defined class
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// DArray - a dynamically sized array class used to
//        demonstrate the assignment and copy constructor
//        operators
class DArray
{
  public:
    DArray(int nLengthOfArray = 0)
      : nLength(nLengthOfArray), pArray(nullptr)
    {
        cout << "Creating DArray of length = "
             << nLength << endl;
        if (nLength > 0)
        {
            pArray = new int[nLength];
        }
    }
    DArray(DArray& da)
    {
        cout << "Copying DArray of length = "
             << da.nLength << endl;
        copyDArray(da);
    }
    ~DArray()
    {
        deleteDArray();
    }
    //assignment operator
    DArray& operator=(const DArray& s)
    {
        cout << "Assigning source of length = "
             << s.nLength
             << " to target of length = "
             << this->nLength << endl;
        //delete existing stuff...
        deleteDArray();
        //...before replacing with new stuff
        copyDArray(s);
        //return reference to existing object
        return *this;
    }
    int& operator[](int index)
    {
        return pArray[index];
    }
    int size() { return nLength; }
    void display(ostream& out)
    {
        if (nLength > 0)
        {
            out << pArray[0];
            for(int i = 1; i < nLength; i++)
            {
                out << ", " << pArray[i];
            }
        }
    }
  protected:
    void copyDArray(const DArray& da);
    void deleteDArray();
    int nLength;
    int* pArray;
};
//copyDArray() - create a copy of a dynamic array of ints
void DArray::copyDArray(const DArray& source)
{
    nLength = source.nLength;
    pArray = nullptr;
    if (nLength > 0)
    {
        pArray = new int[nLength];
        for(int i = 0; i < nLength; i++)
        {
            pArray[i] = source.pArray[i];
        }
    }
}
//deleteDArray() - return heap memory
void DArray::deleteDArray()
{
    nLength = 0;
    delete pArray;
    pArray = nullptr;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    // a dynamic array and assign it values
    DArray da1(5);
    for (int i = 0; i < da1.size(); i++)
    {
        // uses user defined index operator to access
        // members of the array
        da1[i] = i;
    }
    cout << "da1="; da1.display(cout); cout << endl;
    // now create a copy of this dynamic array using
    // copy constructor; this is same as da2(da1)
    DArray da2 = da1;
    da2[2] = 20;   // change a value in the copy
    cout << "da2="; da2.display(cout); cout << endl;
    // overwrite the existing da2 with the original da1
    da2 = da1;
    cout << "da2="; da2.display(cout); cout << endl;
// wait until user is ready before terminating program
// to allow the user to see the program results
cout << "Press Enter to continue..." << endl;
cin.ignore(10, '\n');
cin.get();
return 0;
}

/* OUTPUT:
Creating DArray of length = 5
da1=0, 1, 2, 3, 4
Copying DArray of length = 5
da2=0, 1, 20, 3, 4
Assigning source of length = 5 to target of length = 5
da2=0, 1, 2, 3, 4
Press Enter to continue...
*/
```
