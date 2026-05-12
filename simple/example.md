# Simple example programs

## Celsius degrees into Fahrenheit
```
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
```
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

```
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
```
