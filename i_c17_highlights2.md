# C++ 17 highlights

## Switch statements
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
