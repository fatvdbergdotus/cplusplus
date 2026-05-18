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
```
