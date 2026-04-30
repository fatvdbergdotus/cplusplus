# C++ 17 highlights

## Switch statements
The example shows how a C++17 switch statement with an initializer can be used to process characters in a string while keeping variables scoped neatly. The program loops through each character of a C-style string and, inside the switch, declares a temporary variable c (const char c = arr[i]) that exists only for that switch. It then checks whether c is a whitespace character (space ' ', tab '\t', or newline '\n'); if so, it increments a counter. Each case falls into the same action (incrementing), and break prevents unintended fallthrough. This approach keeps the code clean by avoiding extra variables outside the switch while clearly grouping conditions that share the same behavior.

```cpp
#include <iostream>      // for std::cout
#include <string>        // for std::string
#include <utility>       // for std::pair

using namespace std::literals; // enables "text"s string literal

// -------------------------
// Example 1: Basic switch with initializer
// -------------------------
void example_basic_switch() {
    int ws_count{0}; // counter for whitespace characters

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 1: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // loop until null terminator
        switch (const char c = arr[i]; c) { // C++17 switch initializer
            case ' ':      // if character is space
            case '\t':     // or tab
            case '\n':     // or newline
                ++ws_count; // increment counter
                break;      // exit switch
            default:       // any other character
                break;      // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n\n"; // print result
}

// -------------------------
// Example 2: Structured binding in switch
// -------------------------

// enum to represent result states
enum class Result { SUCCEEDED, TIMED_OUT, FAILED };

// function returning a pair (data + result)
auto fetch() {
    return std::pair{"abcdef"s, Result::SUCCEEDED}; // sample data
}

void example_structured_binding() {
    std::cout << "Example 2:\n"; // header

    // structured binding inside switch (C++17 feature)
    switch (auto [data, result] = fetch(); result) {
        case Result::SUCCEEDED: // success case
            std::cout << "Fetched data: " << data << '\n'; // print data
            break;
        case Result::TIMED_OUT: // timeout case
            std::cout << "The operation timed out\n";
            break;
        case Result::FAILED:    // failure case
            std::cout << "The operation failed\n";
            break;
    }

    std::cout << "\n"; // spacing
}

// -------------------------
// Example 3: Fallthrough attribute
// -------------------------
void example_fallthrough() {
    int ws_count{0}; // counter for whitespace

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 3: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // iterate characters
        switch (const char c = arr[i]; c) { // switch with initializer
            case ' ':              // space
                [[fallthrough]];  // intentional fallthrough
            case '\t':             // tab
                [[fallthrough]];  // intentional fallthrough
            case '\n':             // newline
                ++ws_count;       // count whitespace
                break;            // exit switch
            default:              // not whitespace
                break;            // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n"; // output result
}

// -------------------------
// Main function
// -------------------------
int main() {
    example_basic_switch();        // run first example
    example_structured_binding();  // run second example
    example_fallthrough();         // run third example

    return 0; // end program
}
```

## Copy elision
```cpp
#include <iostream>                 // Include input-output stream library for std::cout

class Test {                       // Define a class named Test
  public:
    Test() {                       // Default constructor
        std::cout << "Default constructor\n"; // Print when object is created
    }
    
    // Copy constructor with side effect
    Test(const Test& other) {      // Copy constructor (called when copying objects)
        std::cout << "Copying\n";  // Print when a copy happens
    }
};

// Function returning a temporary object
Test func()                        // Function that returns a Test object
{
    return Test{};                 // Return a temporary Test object (prvalue)
}

int main()                         // Entry point of the program
{
    std::cout << "Calling func()\n"; // Print before calling func()
    
    // How many times is "Copying" printed out?
    Test test = func();            // Initialize 'test' with return value of func()
                                   // In C++17, copy elision is guaranteed here
                                   // So NO copy constructor is called
    
    std::cout << "Returned from func()\n"; // Print after func() completes
}
```
