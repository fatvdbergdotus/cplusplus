# Lambda expressions

## Overview
```cpp
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// Version 1: Using STL algorithm + lambda
bool equal_strings_lambda(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size()) return false;

    return equal(lhs.begin(), lhs.end(), rhs.begin(),
                 [](char lc, char rc) {
                     return toupper(lc) == toupper(rc);
                 });
}

// Version 2: Manual implementation
bool equal_strings_manual(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    auto lit = lhs.cbegin();
    auto rit = rhs.cbegin();

    while (lit != lhs.cend() && rit != rhs.cend()) {
        if (toupper(*lit) != toupper(*rit))
            return false;
        ++lit;
        ++rit;
    }
    return true;
}

// Test function
void test(const string& str1, const string& str2) {
    cout << "Comparing: " << str1 << " and " << str2 << endl;

    cout << "Lambda version: "
         << (equal_strings_lambda(str1, str2) ? "equal" : "not equal")
         << endl;

    cout << "Manual version: "
         << (equal_strings_manual(str1, str2) ? "equal" : "not equal")
         << endl;

    cout << "------------------------" << endl;
}

int main() {
    test("lambda", "Lambda");
    test("lambda", "lambada");
    test("Hello", "hello");
}
```
