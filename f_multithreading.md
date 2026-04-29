# Multithreading

```cpp
#include <thread>      // For std::thread
#include <iostream>    // For std::cout
#include <string>      // For std::string
#include <functional>  // For std::cref

using namespace std;   // Avoid std:: prefix (for simplicity)

// ------------------- Example 1: No arguments -------------------

// Thread function with no parameters
void hello_no_arg() {                         // Define a function to run in a thread
    cout << "Hello, Thread (no arg)!\n";      // Print message
}

// ------------------- Example 2: Pass by value -------------------

// Thread function taking argument by value
void hello_value(string arg) {                // Copy of string is passed
    cout << arg << endl;                     // Print the copied string
}

// ------------------- Example 3: Pass by reference -------------------

// Thread function taking argument by const reference
void hello_ref(const string& arg) {           // Reference avoids copying
    cout << arg << endl;                     // Print referenced string
}

// ------------------- Main -------------------

int main() {

    // ----------- Example 1: No argument -----------
    thread t1{ hello_no_arg };               // Create thread running hello_no_arg
    t1.join();                               // Wait for thread to finish

    // ----------- Example 2: Pass by value -----------
    thread t2{ hello_value, "Hello, Thread (value)!"s }; // Pass temporary string (copied)
    t2.join();                               // Wait for thread to finish

    // ----------- Example 3: Pass by reference -----------
    string str{ "Hello, Thread (reference)!" }; // Create string variable
    thread t3{ hello_ref, cref(str) };        // Pass reference using std::cref
    t3.join();                               // Wait for thread to finish

    // std::cref is a helper function from the C++ standard library (<functional>)
    // that lets you pass an argument by reference to things like std::thread, which normally copy arguments.

    return 0;                                // End program
}
```

## Shared data
```cpp
#include <iostream>      // For standard input/output (cout)
#include <thread>        // For std::thread
#include <chrono>        // For time utilities like sleep_for

using namespace std;     // Avoid writing std:: repeatedly

// Function that prints a string multiple times
void print(string str) {
    // Loop 5 times
    for (int i = 0; i < 5; ++i) {
        // Print the first three characters of the string
        cout << str[0] << str[1] << str[2] << endl;

        // Pause the thread for 50 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    // Create thread t1 and pass "abc" to print()
    std::thread t1{print, "abc"};

    // Create thread t2 and pass "def" to print()
    std::thread t2{print, "def"};

    // Create thread t3 and pass "xyz" to print()
    std::thread t3{print, "xyz"};

    // Wait for thread t1 to finish before continuing
    t1.join();

    // Wait for thread t2 to finish
    t2.join();

    // Wait for thread t3 to finish
    t3.join();

    // End of program
    return 0;
}
```
