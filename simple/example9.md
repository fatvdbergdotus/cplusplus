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

## Multiple inheritence factoring (#if TRYIT)
```cpp
//  MultipleInheritanceFactoring - a single class can
//               
inherit from more than one base class
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define TRYIT false
using namespace std;
// Furniture - more fundamental concept; this class
//             
has "weight" as a property
class Furniture
{
public:
Furniture(int w) : weight(w) {}
int weight;
};
class Bed : public Furniture
{
public:
Bed(int weight) : Furniture(weight) {}
void sleep(){ cout << "Sleep" << endl; }
};
class Sofa : public Furniture
{
public:
Sofa(int weight) : Furniture(weight) {}
void watchTV(){ cout << "Watch TV" << endl; }
};
// SleeperSofa - is both a Bed and a Sofa
class SleeperSofa : public Bed, public Sofa
{
public:
SleeperSofa(int weight) : Bed(weight), Sofa(weight) {}
void foldOut(){ cout << "Fold out" << endl; }
};
int main(int nNumberofArgs, char* pszArgs[])
{
    SleeperSofa ss(10);
    // Section 1 
    // the following is ambiguous; is this a
    // Furniture::Sofa or a Furniture::Bed?
#if TRYIT
    cout << "Weight = " << ss.weight << endl;
#endif
    // Section 2 
    // the following specifies the inheritance path
    // unambiguously but it sort of ruins the effect
    SleeperSofa* pSS = &ss;
    Sofa* pSofa = (Sofa*)pSS;
    Furniture* pFurniture = (Furniture*)pSofa;
    cout << "Weight = " << pFurniture->weight << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Virtual inheritence to share a common base
```cpp
//  VirtualInheritance - using virtual inheritance the
//            
Bed and Sofa classes can share a common base
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// Furniture - more fundamental concept; this class
//             has "weight" as a property
class Furniture
{
public:
    Furniture(int w) : weight(w) {}
    int weight;
};
class Bed : virtual public Furniture
{
public:
    Bed(int w = 0) : Furniture(w) {}
    void sleep(){ cout << "Sleep" << endl; }
};
class Sofa : virtual public Furniture
{
public:
    Sofa(int w = 0) : Furniture(w) {}
    void watchTV(){ cout << "Watch TV" << endl; }
};
// SleeperSofa - is both a Bed and a Sofa
class SleeperSofa : public Bed, public Sofa
{
public:
SleeperSofa(int w) : Furniture(w) {}
    void foldOut(){ cout << "Fold out" << endl; }
};
int main(int nNumberofArgs, char* pszArgs[])
{
    SleeperSofa ss(10);
    // the following is no longer ambiguous;
    // there's only one weight shared between Sofa and Bed
    // Furniture::Sofa or a Furniture::Bed?
    cout << "Weight = " << ss.weight << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Applying templates to functions (max template)
```cpp
// MaxTemplate - create a template max() function
//               that returns the greater of two types
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
template <class T> T maximum(T t1, T t2)
{
    return (t1 > t2) ? t1 : t2;
}
int main(int argc, char* pArgs[])
{
    // find the maximum of two int's;
    // here C++ creates maximum(int, int)
    cout << "maximum(-1, 2) = "<<maximum(-1, 2) << endl;
    // repeat for two doubles;
    // in this case, we have to provide T explicitly since
    // the types of the arguments are different
    cout << "maximum(1, 2.5) = "<<maximum<double>(1, 2.5)
         << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Applying templates to classes
```cpp
// TemplateVector - a simple templatized vector class
template <class T>
class TemplateVector
{
public:
    TemplateVector(int nArraySize)
    {
        // store off the number of elements
        nSize = nArraySize;
        array = new T[nArraySize];
        reset();
    }
    int size() { return nWriteIndex; }
    void reset() { nWriteIndex = 0; nReadIndex = 0; }
    void add(const T& object)
    {
        if (nWriteIndex < nSize)
        {
            array[nWriteIndex++] = object;
        }
    }
    T& get()
    {
        return array[nReadIndex++];
    }
  protected:
    int nSize;
    int nWriteIndex;
    int nReadIndex;
    T* array;

// TemplateVector - implement a vector that uses a
//                  template type
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "templatevector.h"
using namespace std;
// intFn() - manipulate a collection of integers
void intFn()
{
    // create a vector of integers
    TemplateVector<int> integers(10);
    // add values to the vector
    cout << "Enter integer values to add to a vector\n"
         << "(Enter a negative number to terminate):"
         << endl;
    for(;;)
    {
        int n;
        cin  >> n;
        if (n < 0) { break; }
        integers.add(n);
    }
    cout << "\nHere are the numbers you entered:" << endl;
    for(int i = 0; i < integers.size(); i++)
    {
        cout << i << ":" << integers.get() << endl;
    }
}
// Names - create and manipulate a vector of names
class Name
{
  public:
    Name() = default;
    Name(string s) : name(s) {}
    const string& display() { return name; }
  protected:
    string name;
};
void nameFn()
{
    // create a vector of Name objects
    TemplateVector<Name> names(20);
    // add values to the vector
    cout << "Enter names to add to a second vector\n"
         << "(Enter an 'x' to quit):" << endl;
    for(;;)
    {
        string s;
        cin >> s;
        if (s == "x" || s == "X") { break; }
        names.add(Name(s));
    }
    cout << "\nHere are the names you entered" << endl;
    for(int i = 0; i < names.size(); i++)
    {
        Name& name = names.get();
        cout << i << ":" << name.display() << endl;
    }
}
int main(int argc, char* pArgs[])
{
    intFn();
    nameFn();
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;

/* SAMPLE OUTPUT:
    Enter integer values to add to a vector
    (Enter a negative number to terminate):
    5
    10
    15-1
    Here are the numbers you entered:
    0:5
    1:10
    2:15
    Enter names to add to a second vector
    (Enter an 'x' to quit):
    Chester
    Trude
    Lollie
    Bodie
    x
    Here are the names you entered
    0:Chester
    1:Trude
    2:Lollie
    3:Bodie
    Press Enter to continue...
*/
}
};
```
