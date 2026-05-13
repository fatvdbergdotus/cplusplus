# Simple example

## Variable sizes
```cpp
// VariableSize - output the size of each type of variable
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
bool        
b; char  c; int    n; long         
l;
long long  ll; float f; double d; long double ld;
    cout << "sizeof a bool        = " << sizeof b << endl;
    cout << "sizeof a char        = " << sizeof c << endl;
    cout << "sizeof an int        = " << sizeof n << endl;
    cout << "sizeof a long        = " << sizeof l << endl;
    cout << "sizeof a long long   = " << sizeof ll<< endl;
    cout << "sizeof a float       = " << sizeof f << endl;
    cout << "sizeof a double      = " << sizeof d << endl;
    cout << "sizeof a long double = " << sizeof ld<< endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* OUTPUT:
sizeof a bool        = 1
sizeof a char        = 1
sizeof an int        = 4
sizeof a long        = 4
sizeof a long long   = 8
sizeof a float       = 4
sizeof a double      = 8
sizeof a long double = 12
Press Enter to continue...
*/
```

## Address operators
```cpp
// Layout - this program tries to give the
//          
reader an idea of the layout of
//          
local memory in her compiler
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
int  start;
int    
n; long    
l; long long   ll;
float  f; double  d; long double ld;
int  end;
// set output to hex mode
    cout.setf(ios::hex);
    cout.unsetf(ios::dec);
    // output the address of each variable
    // in order to get an idea of how variables are
    // laid out in memory
    cout << "--- = " << &start << endl;
    cout << "&n  = " << &n     << endl;
    cout << "&l  = " << &l     << endl;
    cout << "&ll = " << &ll    << endl;
    cout << "&f  = " << &f     << endl;
    cout << "&d  = " << &d     << endl;
    cout << "&ld = " << &ld    << endl;
    cout << "--- = " << &end   << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* POSSIBLE OUTPUT:
--- = 0x28fefc
&n  = 0x28fef8
&l  = 0x28fef4
&ll = 0x28fee8
&f  = 0x28fee4
&d  = 0x28fed8
&ld = 0x28fec0--- = 0x28febc
Press Enter to continue...
*/
```

## Limited scope
```cpp
// the following variable is accessible to
// all functions and defined as long as the
// program is running(global scope)
int intGlobal;
// the following variable intChild is accessible
// only to the function and is defined only
// as long as C++ is executing child() or a 
// function which child() calls (function scope)
void child(void)
{
int intChild;
}
// the following variable intParent has function
// scope
void parent(void)
{
int intParent = 0;
child();
int intLater = 0;
intParent = intLater;
}
int main(int nArgs, char* pArgs[])
{
parent();
}
```
