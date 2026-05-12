# Simple examples

## While demo (input dependent times)
```cpp
 // WhileDemo - input a loop count. Loop while
//             outputting astring arg number of times.
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    int nLoopCount;
    cout << "Enter loop count: ";
    cin  >> nLoopCount;
    // now loop that many times
    while (nLoopCount > 0)
    {
        nLoopCount = nLoopCount - 1;
        cout << "Only " << nLoopCount
             << " loops to go" << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/*
  POSSIBLE OUTPUT:
  Enter loop count: 5
  Only 4 loops to go
  Only 3 loops to go
  Only 2 loops to go
  Only 1 loops to go
  Only 0 loops to go
  Press Enter to continue...
*/
```

## For demo (input dependent times)

```cpp
// ForDemo1 - input a loop count. Loop while
//           outputting astring arg number of times.
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    int nLoopCount;
    cout << "Enter loop count: ";
    cin  >> nLoopCount;
    // count up to the loop count limit
    for (; nLoopCount > 0;)
    {
        nLoopCount = nLoopCount - 1;
        cout << "Only " << nLoopCount
             << " loops to go" << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
```

## For loop 2 (input dependent times) with a second counter
```cpp
 // ForDemo2 - input a loop count. Loop while
//            outputting astring arg number of times.
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    int nLoopCount;
    cout << "Enter loop count: ";
    cin  >> nLoopCount;
    // count up to the loop count limit
    for (int i = 1; i <= nLoopCount; i++)
    {
        cout << "We've finished " << i
             << " loops" << endl;
    }
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
/* POSSIBLE OUTPUT:
 Enter loop count: 5
We've finished 1 loops
We've finished 2 loops
We've finished 3 loops
We've finished 4 loops
We've finished 5 loops
Press Enter to continue...
*/
```

## For each demo

```cpp
// ForEachDemo - C++ includes a form of the "for each"
//               
which iterates through each member of
//               
a list
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    cout << "The primes less than 20 are:" << endl;
    for(int n : {1, 2, 3, 5, 7, 11, 13, 17, 19})
    {
        cout << n << ", ";
    }
    cout << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

// The primes less than 20 are:
// 1, 2, 3, 5, 7, 11, 13, 17, 19,
// Press Enter to continue...
```

## Break demo

```cpp
// BreakDemo - input a series of numbers.
//             Continue to accumulate the sum
//             of these numbers until the user
//             enters a negative number.
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    int accumulator = 0;
    cout << "This program sums values from the user\n"
         << "Terminate by entering a negative number"
         << endl;
    // loop "forever"
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
        // ...otherwise add the number to the accumulator
        accumulator += nValue;
    }
    // now that we've exited the loop
    // output the accumulated result
    cout << "\nThe total is "
         << accumulator
         << endl;
    // wait until user is ready before terminating program
    // to allow the user to see the program results
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}

/* POSSIBLE OUTPUT:
This program sums values from the user
Terminate by entering a negative number
Enter next number: 1
Enter next number: 2
Enter next number: 3
Enter next number: -1
The total is 6
Press Enter to continue...
*/
```

