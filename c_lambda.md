# Lambda expressions

## Overview

### Simple lambda function 1
```cpp
#include <iostream>
using namespace std;

int main() {
    // A lambda that takes two ints and returns their sum

    cout << [](int a, int b) { return a + b; } (3, 4); // Output: 7
}
```cpp

### Simple lambda function 2
```cpp
#include <iostream>
using namespace std;

int main() {
    // A lambda that takes two ints and returns their sum
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << add(3, 4); // Output: 7
}
```

### String compare with lambda
```cpp
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// ------------------------------------------------------------
// Version 1: Using STL algorithm + lambda
// This function compares two strings ignoring case differences
// by using std::equal with a custom comparison (lambda).
// ------------------------------------------------------------
bool equal_strings_lambda(const string& lhs, const string& rhs) {
    // If lengths differ, strings cannot be equal
    if (lhs.size() != rhs.size()) return false;

    // std::equal compares elements from lhs and rhs
    // The lambda defines how characters are compared
    return equal(lhs.begin(), lhs.end(), rhs.begin(),
                 [](char lc, char rc) {
                     // Convert both characters to uppercase
                     // before comparing to ignore case differences
                     return toupper(lc) == toupper(rc);
                 });
}

// ------------------------------------------------------------
// Version 2: Manual implementation
// This function does the same comparison but without STL helpers.
// It iterates through both strings character by character.
// ------------------------------------------------------------
bool equal_strings_manual(const string& lhs, const string& rhs) {
    // If lengths differ, strings cannot be equal
    if (lhs.size() != rhs.size())
        return false;

    // Create constant iterators for both strings
    auto lit = lhs.cbegin();
    auto rit = rhs.cbegin();

    // Loop through both strings simultaneously
    while (lit != lhs.cend() && rit != rhs.cend()) {
        // Compare characters ignoring case
        if (toupper(*lit) != toupper(*rit))
            return false; // Stop early if mismatch found

        // Move both iterators forward
        ++lit;
        ++rit;
    }

    // If loop completes, all characters matched
    return true;
}

// ------------------------------------------------------------
// Test helper function
// Runs both implementations on the same input and prints results
// ------------------------------------------------------------
void test(const string& str1, const string& str2) {
    cout << "Comparing: " << str1 << " and " << str2 << endl;

    // Call lambda-based version
    cout << "Lambda version: "
         << (equal_strings_lambda(str1, str2) ? "equal" : "not equal")
         << endl;

    // Call manual version
    cout << "Manual version: "
         << (equal_strings_manual(str1, str2) ? "equal" : "not equal")
         << endl;

    cout << "------------------------" << endl;
}

// ------------------------------------------------------------
// Main function: entry point of the program
// Runs several test cases to demonstrate functionality
// ------------------------------------------------------------
int main() {
    // Same word, different case → should be equal
    test("lambda", "Lambda");

    // Different words → should not be equal
    test("lambda", "lambada");

    // Another case-insensitive match
    test("Hello", "hello");

    return 0;
}
```
