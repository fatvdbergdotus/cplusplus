# Simple example programs

## Celsius degrees into Fahrenheit
```cpp
//
//  Conversion - Program to convert temperature from
//               Celsius degrees into Fahrenheit:
//             
Fahrenheit = Celsius  * (212 - 32)/100 + 32
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // enter the temperature in Celsius
    int celsius;
    cout << "Enter the temperature in Celsius:";
    cin >> celsius;
    // calculate conversion factor for Celsius
    // to Fahrenheit
    int factor;
    factor = 212 - 32;
    // use conversion factor to convert Celsius
    // into Fahrenheit values
    int fahrenheit;
    fahrenheit = factor * celsius/100 + 32;
    // output the results (followed by a NewLine)
    cout << "Fahrenheit value is:";
    cout << fahrenheit << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Starting point template
```cpp
//
//  Template - provides a template to be used as the 
//             starting point
//
// the following include files define the majority of
// functions that any given program will need
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // your C++ code starts here
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout<< "Press Enter to continue..." <<endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0; 
}
```
## Compare input values yielding a boolean
```cpp
 // BoolTest - compare variables input from the
//            keyboard and store the results off
//            into a logical variable
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // set output format for bool variables
    // to true and false instead
    // of 1 and 0
    cout.setf(cout.boolalpha);
    // input two values
    int nArg1;
    cout << "Input value 1: ";
    cin >> nArg1;
    int nArg2;
    cout << "Input value 2: ";
    cin >> nArg2;
    // compare the two variables and store the results
    bool b;
    b = nArg1 == nArg2;
    cout << "The statement, " << nArg1
         << " equals "        << nArg2
         << " is "            
         << endl;
         << b
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

// Example output:
// Input value 1: 5
// Input value 2: 5
// The statement, 5 equals 5 is true
// Press Enter to continue...
```

## Illustrate bitwise operators
```cpp
 // BitTest - initialize two variables and output the
//           results of applying the ~,& , | and ^
//           operations
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // set output format to hexadecimal
    cout.unsetf(cout.dec);
    cout.setf(cout.hex);
    // initialize two arguments
    int nArg1 = 0x78ABCDEF;
    int nArg2 = 0x12345678;
    // now perform each operation in turn
    // first the unary NOT operator
    cout << " nArg1 = 0x" << nArg1  << endl;
    cout << "~nArg1 = 0x" << ~nArg1 << "\n" << endl;
    cout << " nArg2 = 0x" << nArg2  << endl;
    cout << "~nArg2 = 0x" << ~nArg2 << "\n" << endl;
    // now the binary operators
    cout << "  0x" << nArg1 << "\n"
         << "& 0x" << nArg2 << "\n"
         << "  ----------" << "\n"
         << "  0x" << (nArg1 & nArg2) << "\n"
         << endl;
    cout << "  0x" << nArg1 << "\n"
         << "| 0x" << nArg2 << "\n"
         << "  ----------" << "\n"
         << "  0x" << (nArg1 | nArg2) << "\n"
         << endl;
    cout << "  0x" << nArg1 << "\n"
         << "^ 0x" << nArg2 << "\n"
         << "  ----------" << "\n"
         << "  0x" << (nArg1 ^ nArg2) << "\n"
         << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/*
nArg1 = 0x78abcdef
~nArg1 = 0x87543210
nArg2 = 0x12345678
~nArg2 = 0xedcba987
  0x78abcdef
& 0x12345678
  ----------
  0x10204468
  0x78abcdef
| 0x12345678
  ----------
  0x7abfdfff
  0x78abcdef
^ 0x12345678
  ----------
  0x6a9f9b97
Press Enter to continue...
*/
```

## Branching demo depending on two inputs
```
// BranchDemo - input two numbers. Go down one path of the
//              program if the first argument is greater
//              than the first or the other path if not
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the first argument...
    int nArg1;
    cout << "Enter arg1: ";
    cin  >> nArg1;
    // ...and the second
    int nArg2;
    cout << "Enter arg2: ";
    cin  >> nArg2;
    // now decide what to do:
    if (nArg1 > nArg2)
    {
        cout<< "Argument 1 is greater than argument 2"
            << endl;
    }
    else
    {
        cout<< "Argument 1 is not greater than argument 2"
            << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```
