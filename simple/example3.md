# Simple example

## Nested loop

```cpp
  // NestedDemo - input a series of numbers.
//              Continue to accumulate the sum
//              of these numbers until the user
//              enters a 0. Repeat the process
//              until the sum is 0.
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // the outer loop
    cout << "This program sums multiple series\n"
         << "of numbers. Terminate each sequence\n"
         << "by entering a negative number.\n"
         << "Terminate the series by entering two\n"
         << "negative numbers in a row\n";
    // continue to accumulate sequences
    int accumulator;
    for(;;)
    {
        // start entering the next sequence
        // of numbers
        accumulator = 0;
        cout << "Start the next sequence\n";
        // loop forever
        for(;;)
        {
            // fetch another number
            int nValue = 0;
            cout << "Enter next number: ";
            cin  >> nValue;
            // if it's negative...
            if (nValue < 0)
            {
                // ...then exit
                break;
            }
            // ...otherwise add the number to the
            // accumulator
            accumulator += nValue;
        }
        // exit the loop if the total accumulated is 0
        if (accumulator == 0)
        {
            break;
        }
        // output the accumulated result and start over
        cout << "The total for this sequence is "
            << accumulator << endl << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Function demo
```cpp
 // FunctionDemo - demonstrate the use of functions
//                by breaking the inner loop of the
//                NestedDemo program off into its own
//                function
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// displayExplanation - prompt the user as to the rules
//                      of the game
void displayExplanation(void)
{
    cout << "This program sums multiple series\n"
         << "of numbers. Terminate each sequence\n"
         << "by entering a negative number.\n"
         << "Terminate the series by entering an\n"
         << "empty sequence.\n"
         << endl;
    return;
}

// sumSequence - add a sequence of numbers entered from
//               the keyboard until the user enters a
//               negative number.
//               return - the summation of numbers entered
int sumSequence(void)
{
    // loop forever
    int accumulator = 0;
    for(;;)
    {
        // fetch another number
        int nValue = 0;
        cout << "Enter next number: ";
        cin  >> nValue;
        // if it's negative...
        if (nValue < 0)
        {
            // ...then exit from the loop
            break;
        }
        // ...otherwise add the number to the
        // accumulator
        accumulator += nValue;
    }
    // return the accumulated value
    return accumulator;
}

int main(int nNumberofArgs, char* pszArgs[])
{
    // display prompt to the user
    displayExplanation();
    // accumulate sequences of numbers...
    for(;;)
    {
        // sum a sequence of numbers entered from
        // the keyboard
        cout << "Enter next sequence" << endl;
        int accumulatedValue = sumSequence();
        // terminate the loop if sumSequence() returns
        // a zero
        if (accumulatedValue == 0)
        {
            break;
        }
        // now output the accumulated result
        cout << "The total is " << accumulatedValue
             << endl << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Function demo with arguments

```cpp
// SquareDemo - demonstrate the use of a function
//              
which processes arguments
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// square - returns the square of its argument
//          doubleVar - the value to be squared
//          returns - square of doubleVar
double square(double doubleVar)
{
    return doubleVar * doubleVar;
}

// displayExplanation - prompt the user as to the rules
//                      of the game
void displayExplanation(void)
{
    cout << "This program sums the square of multiple\n"
         << "series of numbers. Terminate each sequence\n"
         << "by entering a negative number.\n"
         << "Terminate the series by entering an\n"
         << "empty sequence.\n"
         << endl;
    return;
}

// sumSquareSequence - accumulate the square of the number
//               entered at the keyboard into a sequence
//               until the user enters a negative number
double sumSquareSequence(void)
{
    // loop forever
    double accumulator = 0.0;
    for(;;)
    {
        // fetch another number
        double dValue = 0;
        cout << "Enter next number: ";
        cin  >> dValue;
        // if it's negative...
        if (dValue < 0)
        {
            // ...then exit from the loop
            break;
        }
        // ...otherwise calculate the square
        double value = square(dValue);
        // now add the square to the
        // accumulator
        accumulator += value;
    }
    // return the accumulated value
    return accumulator;
}

int main(int nNumberofArgs, char* pszArgs[])
{
    displayExplanation();
    // Continue to accumulate numbers...
    for(;;)
    {
        // sum a sequence of numbers entered from
        // the keyboard
        cout << "Enter next sequence" << endl;
        double accumulatedValue = sumSquareSequence();
        // terminate if the sequence is zero or negative
        if (accumulatedValue <= 0.0)
        {
            break;
        }
        // now output the accumulated result
        cout << "\nThe total of the values squared is "
             << accumulatedValue << endl << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## Using an array
```cpp
// ArrayDemo - demonstrate the use of arrays
//             by reading a sequence of integers
//             and then displaying them and their sum
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// prototype declarations
int readArray(int integerArray[], int maxNumElements);
int sumArray(int integerArray[], int numElements);
void displayArray(int integerArray[], int numElements);
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    cout << "This program sums values entered "
         << "by the user\n";
    cout << "Terminate the loop by entering "
         << "a negative number\n";
    cout << endl;
    // read numbers to be summed from the user into a
    // local array
    int inputValues[128];
    int numberOfValues = readArray(inputValues, 128);
    // now output the values and the sum of the values
    displayArray(inputValues, numberOfValues);
    cout << "The sum is "
         << sumArray(inputValues, numberOfValues)
         << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
// readArray - read integers from the operator into
//             'integerArray' until operator enters neg.
//             Return the number of elements stored.
int readArray(int integerArray[], int maxNumElements)
{
    int numberOfValues;
    for(numberOfValues = 0;
        numberOfValues < maxNumElements;
        numberOfValues++)
    {
        // fetch another number
        int integerValue;
        cout << "Enter next number: ";
        cin  >> integerValue;
        // if it's negative...
        if (integerValue < 0)
        {
            // ...then exit
            break;
        }
        // ... otherwise store the number
        // into the  storage array
        integerArray[numberOfValues] = integerValue;
    }
    // return the number of elements read
    return numberOfValues;
}
// displayArray - display the members of an
//                array of length sizeOfloatArray
void displayArray(int integerArray[], int numElements)
{
    cout << "The value of the array is:" << endl;
    for (int i = 0; i < numElements; i++)
    {
        cout << i << ": " << integerArray[i] << endl;
    }
}
cout << endl;
// sumArray - return the sum of the members of an
//            
integer array
int sumArray(int integerArray[], int numElements)
{
int accumulator = 0;
for (int i = 0; i < numElements; i++)
{
accumulator += integerArray[i];
}
return accumulator;
}

/* POSSIBLE OUTPUT:
This program sums values entered by the user
Terminate the loop by entering a negative number
Enter next number: 10
Enter next number: 20
Enter next number: 30
Enter next number: 40
Enter next number: -1
The value of the array is:
0: 10
1: 20
2: 30
3: 40
The sum is 100
Press Enter to continue...
*/
```

## Creating an array of characters
```cpp
// CharDisplay - output a character array to
//               standard output, the MS-DOS window
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// prototype declarations
void displayCharArray(char charArray[], int sizeOfArray);
int main(int nNumberofArgs, char* pszArgs[])
{
    char charMyName[]={'S', 't', 'e', 'p', 'h', 'e', 'n'};
    displayCharArray(charMyName, 7);
    cout << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
// displayCharArray - display an array of characters
//                    by outputing one character at
//                    a time
void displayCharArray(char charArray[], int sizeOfArray)
{
    for(int i = 0; i< sizeOfArray; i++)
    {
        cout << charArray[i];
    }
}
```

## Concatenate two strings
```cpp
// Concatenate - concatenate two strings
//               with a " - " in the middle
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// prototype declarations
void concatString(char szTarget[], const char szSource[]);
int main(int nNumberofArgs, char* pszArgs[])
{
    // read first string...
    char szString1[256];
    cout << "Enter string #1:";
    cin.getline(szString1, 128);
    // ...now the second string...
    char szString2[128];
    cout << "Enter string #2:";
    cin.getline(szString2, 128);
    // ...concatenate a " - " onto the first...
    concatString(szString1, " - ");
    // ...now add the second string...
    concatString(szString1, szString2);
    // ...and display the result
    cout << "\n" << szString1 << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
// concatString - concatenate the szSource string
//                onto the end of the szTarget string
void concatString(char szTarget[], const char szSource[])
{
    // find the end of the first string
    int targetIndex = 0;
    while(szTarget[targetIndex])
    {
        targetIndex++;
    }
    // tack the second onto the end of the first
    int sourceIndex = 0;
    while(szSource[sourceIndex])
    {
        szTarget[targetIndex] =
            szSource[sourceIndex];
        targetIndex++;
        sourceIndex++;
    }
    // tack on the terminating null
    szTarget[targetIndex] = '\0';
}

/* EXAMPLE OUTPUT:
Enter string #1:this is a string
Enter string #2:THIS IS A STRING
this is a string - THIS IS A STRING
Press Enter to continue...
*/
```
