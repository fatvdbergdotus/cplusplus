# Lambda expressions
In a C++ lambda, the capture clause [], the parameter list (), and the function body {} each play a distinct role: the capture clause specifies which variables from the surrounding scope are accessible inside the lambda (either by value like [x], by reference like [&x], or more broadly with [=] or [&]), the parameter list defines the inputs the lambda accepts just like a normal function (e.g., (int a, int b)), and the body contains the actual logic that runs when the lambda is invoked, optionally returning a value; together, they let you create a compact, inline function that can both use external context and process new inputs at the same time.

## Overview

### Simple lambda function 1
```cpp
#include <iostream>
using namespace std;

int main() {
    // A lambda that takes two ints and returns their sum

    cout << [](int a, int b) { return a + b; } (3, 4); // Output: 7
}
```

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

## Lambda functions capture
```cpp
#include <iostream>
using namespace std;

/*
====================================================
LAMBDA DEMONSTRATION PROGRAM (Single File Version)
====================================================

This program demonstrates:
1. No-capture lambda
2. Capture by value and reference
3. Mutable lambda
4. Functor vs Lambda

Each example is placed in its own function
and called from main().
*/


/*
====================================================
1. No-capture lambda
====================================================
- A lambda that does NOT use any external variables
- Syntax: []() { ... }
- Equivalent to a simple inline function
*/
void noCaptureExample() {
    cout << "\n--- No Capture Lambda ---\n";

    // Define a lambda with no parameters and no capture
    auto greet = []() {
        cout << "Hello from a no-capture lambda!\n";
    };

    // Call the lambda like a function
    greet();
}


/*
====================================================
2. Capture lambda
====================================================
- Lambdas can "capture" variables from outer scope
- Two common types:
    [x]   -> capture by VALUE (copy)
    [&x]  -> capture by REFERENCE (original variable)

Key difference:
- Value: cannot modify original variable
- Reference: CAN modify original variable
*/
void captureLambdaExample() {
    cout << "\n--- Capture Lambda ---\n";

    int x = 10; // variable in outer scope

    // Capture by VALUE (copy of x is used)
    auto byValue = [x]() {
        // x is read-only here (const by default)
        cout << "Captured by value: x = " << x << endl;
    };

    // Capture by REFERENCE (original x is used)
    auto byRef = [&x]() {
        x += 5; // modifies original variable
        cout << "Captured by reference, modified x = " << x << endl;
    };

    byValue();  // prints 10
    byRef();    // modifies x → now 15

    // Show final value after modification
    cout << "Outside lambda, x = " << x << endl;
}


/*
====================================================
3. Mutable lambda
====================================================
- By default, value-captured variables are CONST
- 'mutable' allows modifying the COPY inside lambda

IMPORTANT:
- This does NOT change the original variable
- Only the internal copy is modified
*/
void mutableLambdaExample() {
    cout << "\n--- Mutable Lambda ---\n";

    int x = 5;

    // Capture by value, but allow modification of the copy
    auto modifyCopy = [x]() mutable {
        x += 10; // modifies ONLY the copy
        cout << "Inside lambda, modified copy x = " << x << endl;
    };

    modifyCopy();

    // Original value remains unchanged
    cout << "Outside lambda, original x = " << x << endl;
}


/*
====================================================
4. Functor vs Lambda
====================================================
Functor:
- A class that overloads operator()
- Can behave like a function

Lambda:
- Short, inline alternative to functors
- Usually preferred for simple use cases
*/

// Define a functor (function object)
class Functor {
    int value; // stored value

public:
    // Constructor initializes value
    Functor(int v) : value(v) {}

    // Overload function call operator
    void operator()() {
        cout << "Functor value = " << value << endl;
    }
};

void functorExample() {
    cout << "\n--- Functor vs Lambda ---\n";

    // Using functor
    Functor f(20);
    f(); // calls operator()

    // Equivalent lambda
    int value = 20;

    auto lambda = [value]() {
        cout << "Lambda value = " << value << endl;
    };

    lambda();
}


/*
====================================================
MAIN FUNCTION
====================================================
- Entry point of the program
- Calls all examples sequentially
*/
int main() {
    cout << "Lambda Demonstration Program\n";

    // Run each example one by one
    noCaptureExample();
    captureLambdaExample();
    mutableLambdaExample();
    functorExample();

    cout << "\nAll examples executed.\n";

    return 0; // indicates successful execution
}
```

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* =========================================================
   SECTION 1: Lambda with capture by reference
   Demonstrates capturing a variable (idx) by reference
   ========================================================= */
void demo_lambda_by_ref() {
    cout << "\n=== Demo: Lambda Capture by Reference ===\n";

    vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

    int max{5}, idx{-1}; // idx tracks position

    auto res = find_if(words.begin(), words.end(),
        // Capture max by value, idx by reference
        [max, &idx](const string& str) mutable {
            ++idx;
            return str.size() > max;
        }
    );

    if (res != words.end()) {
        cout << "The first word longer than " << max << " letters is: " << *res << endl;
        cout << "Index: " << idx << endl;
    }
}


/* =========================================================
   SECTION 2: Functor equivalent of lambda
   Shows how a class can replace a lambda expression
   ========================================================= */
class is_longer_than {
private:
    const int n;
    int& idx;

public:
    is_longer_than(const int n, int& idx) : n(n), idx(idx) {}

    bool operator()(const string& str) const {
        ++idx;
        return str.size() > n;
    }
};

void demo_functor() {
    cout << "\n=== Demo: Functor (Lambda Equivalent) ===\n";

    vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

    int max{5}, idx{-1};

    auto res = find_if(words.cbegin(), words.cend(), is_longer_than(max, idx));

    if (res != words.end()) {
        cout << "The first word longer than " << max << " letters is: " << *res << endl;
        cout << "Index: " << idx << endl;
    }
}


/* =========================================================
   SECTION 3: Capturing `this` in a lambda
   Demonstrates accessing class members inside a lambda
   ========================================================= */
class Test {
    int time{10};

public:
    void countdown() {
        // Capture current object (this pointer)
        [this]() {
            if (time > 0)
                cout << time << endl;
            else if (time == 0)
                cout << "Liftoff!" << endl;

            --time;
        }(); // Immediately invoked lambda
    }
};

void demo_capture_this() {
    cout << "\n=== Demo: Capture this ===\n";

    Test test;

    // Call multiple times to simulate countdown
    for (int i = 0; i < 12; ++i) {
        test.countdown();
    }
}


/* =========================================================
   MAIN FUNCTION
   Runs all demos
   ========================================================= */
int main() {
    demo_lambda_by_ref();
    demo_functor();
    demo_capture_this();

    return 0;
}
```

## Partial evaluation
```cpp
// ==== AUTO-GENERATED MINIMAL COMPILABLE MERGE ====

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


// ==== HEADERS (INLINED) ====


// ==== SOURCES ====

// ===== BEGIN SOURCE: partial_evaluation.cc =====
#include <iostream>
#include <string>

using namespace std;

// Function which returns a lambda function
auto greeter(const string& salutation) {
	return [salutation](const string& name) { return salutation + ", "s + name; };       // The lambda function
}

int main() {
	// Store the lambda function in a variable
	auto greet = greeter("Hello"s);

	// Call the lambda function
	cout << "Greeting: " << greet("James") << endl;
	cout << "Greeting: " << greet("students") << endl;

	auto greet_formal = greeter("Good morning"s);

	// Call the lambda function
	cout << "Formal greeting: " << greet_formal("Dr Stroustrup") << endl;
}
// ===== END SOURCE: partial_evaluation.cc =====

// ===== BEGIN SOURCE: return.cc =====
#include <iostream>
#include <string>

using namespace std;

// Function which returns a lambda function
auto greeter(const string& salutation) {
	return [salutation](const string& name) { return salutation + ", "s + name; };       // The lambda function
}

/* DISABLED EXTRA MAIN
int main() {
	// Store the lambda function in a variable
	auto greet = greeter("Hello"s);

	// Call the lambda function
	cout << "Greeting: " << greet("James") << endl;
	cout << "Greeting: " << greet("students") << endl;
}
*/

// ===== END SOURCE: return.cc =====

// ===== BEGIN SOURCE: stored_lambda.cc =====
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* DISABLED EXTRA MAIN
int main() {
	vector<string> words{"a", "collection", "of", "words", "with", "varying", "lengths"};
	int max{5};

	// Save the lambda expression in a variable
	auto is_longer_than = [max](const string& str) { return str.size() > max; };

	// Pass this variable as the predicate
	auto res = find_if(words.cbegin(), words.cend(), is_longer_than);

	// Display it
	if (res != words.end()) {
		cout << R"(The first word which is more than )" << max << R"( letters long is ")";
		cout << *res << R"(")" << endl;
	}
}
*/

// ===== END SOURCE: stored_lambda.cc =====

```

## C++ 14
```cpp
#include <iostream>
#include <string>

using namespace std;

// ---- From generalized.cc ----
void run_generalized() {
    auto add_two = [y = 2](int x) { return x + y; };

    cout << "[generalized]" << endl;
    cout << "Calling add_two(2) gives " << add_two(2) << endl;
    cout << "Calling add_two(5) gives " << add_two(5) << endl;
    cout << endl;
}

// ---- From generalized_init_capture.cc ----
void run_generalized_init_capture() {
    int z = 1;
    auto add_z_plus1 = [y = z + 1](int x) { return x + y; };

    cout << "[generalized_init_capture]" << endl;
    cout << "Calling add_z_plus1(2) gives " << add_z_plus1(2) << endl;
    cout << "Calling add_z_plus1(5) gives " << add_z_plus1(5) << endl;
    cout << endl;
}

// ---- From generic.cc ----
void run_generic() {
    string str1{"Hello, "};
    string str2{"World!"};

    auto func = [](auto x, auto y) { return x + y; };

    cout << "[generic]" << endl;
    cout << "Calling func(2, 5) gives " << func(2, 5) << endl;
    cout << "Calling func(3.141, 4.2) gives " << func(3.141, 4.2) << endl;
    cout << R"(Calling func(str1, str2) gives ")" 
         << func(str1, str2) << R"(")" << endl;
    cout << endl;
}

// ---- Single main ----
int main() {
    run_generalized();
    run_generalized_init_capture();
    run_generic();

    return 0;
}
```

## Map lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{1, 2, 3, 4};

    std::vector<int> result(v.size());

    std::transform(v.begin(), v.end(), result.begin(),
        [](int x) { return x * 2; }   // lambda
    );

    for (int x : result)
        std::cout << x << " ";  // 2 4 6 8
}
```

## Filter lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::vector<int> result;

    std::copy_if(v.begin(), v.end(), std::back_inserter(result),
        [](int x) { return x % 2 == 0; }   // lambda
    );

    for (int x : result)
        std::cout << x << " ";  // 2 4
}
```

## Reduce lambda
```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> v{1, 2, 3, 4};

    int sum = std::accumulate(v.begin(), v.end(), 0,
        [](int acc, int x) { return acc + x; }  // lambda
    );

    std::cout << sum << std::endl;  // 10
}
```
