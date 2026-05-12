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
  Enter loop count: 5
  Only 4 loops to go
  Only 3 loops to go
  Only 2 loops to go
  Only 1 loops to go
  Only 0 loops to go
  Press Enter to continue...
*/
```

