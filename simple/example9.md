# Simple example

## Simple try-catch
```cpp
//  FactorialException - demonstrate exceptions using
//  a factorial function
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// factorial - compute factorial
int factorial(int n)
{
    // you can't handle negative values of n;
    // better check for that condition first
    if (n < 0)
    {
        throw string("Argument for factorial negative");
    }
    // go ahead and calculate factorial
    int accum = 1;
    while(n > 0)
    {
        accum *= n;
        n--;
    }
    return accum;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    try
    {
        // this will work
        cout << "Factorial of 3 is "
             << factorial(3) << endl;
        // this will generate an exception
        cout << "Factorial of -1 is "
             << factorial(-1) << endl;
        // control will never get here
        cout << "Factorial of 5 is "
             << factorial(5) << endl;
    }
    // control passes here
    catch(string error)
    {
        cout << "Error occurred: " << error << endl;
    }
    catch(...)
    {
        cout << "Default catch " << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Factorial of 3 is 6
Factorial of -1 is Error occurred: Argument for factorial negative
Press Enter to continue...
*/
```

## Cascading try-catches
```cpp
// CascadingException - the following program demonstrates
//              
an example of stack unwinding
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// prototypes of some functions that we will need later
void f1();
void f2();
void f3();
class Obj
{
public:
    Obj(char c) : label(c)
    { cout << "Constructing object " << label << endl;}
    ~Obj()
    { cout << "Destructing object " << label << endl; }
protected:
    char label;
};
int main(int nNumberofArgs, char* pszArgs[])
{
    f1();
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
void f1()
{
    Obj a('a');
    try
    {
        Obj b('b');
        f2();
    }
    catch(float f)
    {
        cout << "Float catch" << endl;
    }
    catch(int i)
    {
        cout << "Int catch" << endl;
    }
    catch(...)
    {
        cout << string("Generic catch") << endl;
    }
}
void f2()
    {
        try
        {
            Obj c('c');
            f3();
    }
    catch(string msg)
    {
        cout << "String catch" << endl;
    }
}
void f3()
{
    Obj d('d');
    throw 10;
}

/*
    Constructing object a
    Constructing object b
    Constructing object c
    Constructing object d
    Destructing object d
    Destructing object c
    Destructing object b
    Int catch
    Destructing object a
    Press Enter to continue...
*/
```

## Custom exception class
```cpp
//
//  CustomExceptionClass - demonstrate the flexibility
//              of the exception mechanism by creating
//              a custom exception class
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
// MyException - generic exception handling class
class MyException
{
  public:
    MyException(const char* pMsg, int n,
                const char* pFunc,
                const char* pFile, int nLine)
      : msg(pMsg), errorValue(n),
        funcName(pFunc), file(pFile), lineNum(nLine){}
    virtual string display()
    {
        ostringstream out;
        out << "Error <" << msg << ">"
            << " - value is " << errorValue << "\n"
            << "in function " << funcName << "()\n"
            << "in file " << file
            << " line #" << lineNum << ends;
        return out.str();
    }
  protected:
    // error message
    string msg;
    int    errorValue;
    // function name, file name and line number
    // where error occurred
    string funcName;
    string file;
    int lineNum;
};
// factorial - compute factorial
int factorial(int n) throw(MyException)
{
    // you can't handle negative values of n;
    // better check for that condition first
    if (n < 0)
    {
        throw MyException("Negative argument not allowed",
                        n, __func__, __FILE__, __LINE__);
    }
    // go ahead and calculate factorial
    int accum = 1;
    while(n > 0)
    {
        accum *= n;
        n--;
    }
    return accum;
}
int main(int nNumberofArgs, char* pszArgs[])
{
    try
    {
        // this will work
        cout << "Factorial of 3 is "
             << factorial(3) << endl;
        // this will generate an exception
        cout << "Factorial of -1 is "
             << factorial(-1) << endl;
        // control will never get here
        cout << "Factorial of 5 is "
             << factorial(5) << endl;
    }
    // control passes here
    catch(MyException e)
    {
        cout << e.display() << endl;
    }
    catch(...)
    {
        cout << "Default catch " << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
Factorial of 3 is 6
Error <Negative argument not allowed> - value is -1
in function factorial()
in file
C:\CPP_Programs_from_Book\Chap24\CustomExceptionClass\main.cpp
line #52
Press Enter to continue...
*/
```

## Multiple inheritance
```cpp
//  MultipleInheritance - a single class can inherit from
//                        more than one base class
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
class Bed
{
  public:
    Bed(){}
    void sleep(){ cout << "Sleep" << endl; }
    int weight;
};
class Sofa
{
  public:
    Sofa(){}
    void watchTV(){ cout << "Watch TV" << endl; }
    int weight;
};
// SleeperSofa - is both a Bed and a Sofa
class SleeperSofa : public Bed, public Sofa
{
  public:
    SleeperSofa(){}
    void foldOut(){ cout << "Fold out" << endl; }
};
int main(int nNumberofArgs, char* pszArgs[])
{
    SleeperSofa ss;
    // you can watch TV on a sleeper sofa like a sofa...
    ss.watchTV();     // calls Sofa::watchTV()
    //...and then you can fold it out...
    ss.foldOut();     // calls SleeperSofa::foldOut()
    // ...and sleep on it
    ss.sleep();       // calls Bed::sleep()
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
    Watch TV
    Fold out
    Sleep
    Press Enter to continue...
*/
```
