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

    return 0;                                // End program
}
```
