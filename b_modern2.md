# Modern C++

## Constructors
```cpp
#include <iostream>
using namespace std;

// =====================================================
// Version 1: init.cc style
// Demonstrates: basic constructor with simple setup
// =====================================================
class FridgeInit {
public:
    // Default constructor
    FridgeInit() {
        cout << "[Init] Constructor called\n";
    }
};


// =====================================================
// Version 2: inplace.cc style
// Demonstrates: in-class member initialization (C++11+)
// =====================================================
class FridgeInplace {
    int temperature{2};  // initialized directly where declared

public:
    FridgeInplace() {
        cout << "[Inplace] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 3: constructors.cc style
// Demonstrates: parameterized constructor + initializer list
// =====================================================
class FridgeConstructors {
    int temperature;

public:
    // Constructor using initializer list (best practice)
    FridgeConstructors(int t) : temperature(t) {
        cout << "[Constructors] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 4: default.cc style
// Demonstrates: assigning values inside constructor body
// =====================================================
class FridgeDefault {
    int temperature;

public:
    // Default constructor
    FridgeDefault() {
        temperature = 2;  // assignment (less efficient than init list)
        cout << "[Default] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 5: delegate.cc style
// Demonstrates: constructor delegation (C++11+)
// =====================================================
class FridgeDelegate {
    int temperature;

public:
    // Default constructor delegates to another constructor
    FridgeDelegate() : FridgeDelegate(2) {}

    // Main constructor
    FridgeDelegate(int t) : temperature(t) {
        cout << "[Delegate] temperature = " << temperature << endl;
    }
};


// =====================================================
// MAIN FUNCTION
// Only ONE main() is allowed in a program
// Creates one object from each version
// =====================================================
int main() {
    cout << "Creating all fridge versions:\n\n";

    // Each object demonstrates a different initialization style
    FridgeInit f1;              // basic constructor
    FridgeInplace f2;           // in-class initialization
    FridgeConstructors f3(5);   // parameterized constructor
    FridgeDefault f4;           // assignment in constructor body
    FridgeDelegate f5;          // constructor delegation

    return 0;
}
```

## Delete and Default keywords for Classes
A default constructor is a special function that creates an object with no arguments (e.g., Test t;), while a copy constructor creates a new object as a copy of an existing one (e.g., Test t2 = t1;), meaning it runs during initialization of a new object from another. In contrast, the copy assignment operator does not create a new object but instead copies data into an already existing object (e.g., t2 = t1;). The key difference is that the default and copy constructors are used when an object is being created, whereas the assignment operator is used after objects already exist; together, they control how objects are initialized and how their data is duplicated or reassigned in C++.

```cpp
#include <iostream>

// ============================================================
// Example 1: Modern C++ way — using =delete
// ============================================================

class TestDeleted {
public:
    // Delete the copy constructor
    // This means objects of this class CANNOT be copied
    TestDeleted(const TestDeleted&) = delete;

    // Delete the copy assignment operator
    // This prevents assigning one object to another
    TestDeleted& operator=(const TestDeleted&) = delete;

    // Default constructor is still allowed
    // So we can create objects normally
    TestDeleted() = default;
};

// Function to demonstrate behavior of TestDeleted
void runDeletedExample() {
    TestDeleted t1, t2;   // OK: default construction works

    // The following lines are intentionally commented out
    // because they would cause compilation errors:

    // TestDeleted t3(t1);
    // Error: copy constructor is deleted

    // t2 = t1;
    // Error: assignment operator is deleted

    // This pattern is useful when you want to explicitly
    // forbid copying (e.g., for resource management classes)
}


// ============================================================
// Example 2: Old C++98 technique — private copy operations
// ============================================================

class TestUncopyable {
private:
    // Copy constructor declared PRIVATE
    // This prevents copying from outside the class
    TestUncopyable(const TestUncopyable&);

    // Copy assignment operator also PRIVATE
    TestUncopyable& operator=(const TestUncopyable&);

public:
    // Public default constructor allows object creation
    TestUncopyable() {}
};

// Function to demonstrate behavior of TestUncopyable
void runUncopyableExample() {
    TestUncopyable t1, t2;   // OK: objects can be created

    // The following lines would cause compilation errors:

    // TestUncopyable t3(t1);
    // Error: copy constructor is private

    // t2 = t1;
    // Error: assignment operator is private

    // Note:
    // In old C++ (before C++11), this was the common way
    // to prevent copying.
    // However, it's less clear and less safe than =delete.
}


// ============================================================
// Main function
// ============================================================

int main() {
    // Run both examples
    runDeletedExample();
    runUncopyableExample();

    // If program reaches here, everything compiled fine
    std::cout << "Examples compiled successfully.\n";

    return 0;
}
```

## Conversion operator
```cpp
#include <iostream>
using namespace std;

/*
========================================================
1. IMPLICIT CONVERSION OPERATOR
========================================================
*/
namespace implicit_demo {

class Test {
    int i{42};
public:
    operator int() const { return i; }
};

void run() {
    cout << "[Implicit conversion]\n";
    Test t;
    cout << t << endl;
    cout << endl;
}

}


/*
========================================================
2. EXPLICIT CONVERSION OPERATOR
========================================================
*/
namespace explicit_demo {

class Test {
    int i{42};
public:
    explicit operator int() const { return i; }
};

void run() {
    cout << "[Explicit conversion]\n";
    Test t;
    cout << static_cast<int>(t) << endl;
    cout << endl;
}

}


/*
========================================================
3. EXPLICIT BOOL + INT CONVERSION
========================================================
*/
namespace explicit_bool_demo {

class Test {
    int i{42};
public:
    explicit operator int() const { return i; }
    explicit operator bool() const { return i; }
};

void run() {
    cout << "[Explicit bool + int conversion]\n";
    Test t;

    cout << static_cast<int>(t) << endl;

    if (t)
        cout << "OK" << endl;

    cout << endl;
}

}


/*
========================================================
4. FUNCTION CALL OPERATOR (operator())
- Makes objects behave like functions
========================================================
*/
namespace function_call_demo {

class Multiplier {
    int factor;
public:
    Multiplier(int f) : factor(f) {}

    // Function call operator
    int operator()(int value) const {
        return value * factor;
    }
};

void run() {
    cout << "[Function call operator()]\n";

    Multiplier doubleIt(2);
    Multiplier tripleIt(3);

    cout << "doubleIt(5): " << doubleIt(5) << endl;
    cout << "tripleIt(5): " << tripleIt(5) << endl;

    cout << endl;
}

}


/*
========================================================
5. SURPRISING CASE
========================================================
*/
namespace surprise_demo {

void run() {
    cout << "[Surprise example]\n";

    int i = 99;

    // Avoid confusing operator misuse like:
    // cin << i;

    cout << "cin << i compiles in some contexts but is meaningless.\n";
    cout << endl;
}

}


/*
========================================================
MAIN FUNCTION
========================================================
*/
int main() {
    implicit_demo::run();
    explicit_demo::run();
    explicit_bool_demo::run();
    function_call_demo::run();
    surprise_demo::run();

    return 0;
}
```



