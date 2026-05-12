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
