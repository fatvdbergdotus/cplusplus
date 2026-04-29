# Move semantics

## Swap
```cpp
#include <iostream>   // For input/output (cout, endl)
#include <string>     // For std::string

using namespace std; // Avoid writing std:: everywhere

// ==========================
// Class from overload.cc
// ==========================
class BufferManager {
private:
    int size;        // Size of the buffer
    char* buffer;    // Pointer to dynamically allocated buffer

public:
    // Constructor: allocate memory based on given size
    BufferManager(int size) : size(size), buffer(new char[size]) {}

    // Destructor: free allocated memory
    ~BufferManager() { delete[] buffer; }

    // Declare custom swap as friend so it can access private members
    friend void swap(BufferManager& l, BufferManager& r) noexcept;

    // Function to print object details
    void print() {
        cout << "BufferManager with size = " << size; // Print size
        cout << ": buffer address is " << static_cast<void*>(buffer); // Print memory address
    }
};

// Custom swap function for BufferManager
inline void swap(BufferManager& l, BufferManager& r) noexcept {
    using std::swap;       // Enable std::swap (important for ADL)
    swap(l.size, r.size);  // Swap sizes
    swap(l.buffer, r.buffer); // Swap buffer pointers
}

// ==========================
// Main function (merged)
// ==========================
int main() {

    // ==========================
    // Part 1: string swapping (from member.cc)
    // ==========================
    string s1{"Hello"};    // Initialize first string
    string s2{"Goodbye"};  // Initialize second string

    // Print before swapping
    cout << "Before swapping, s1 = " << s1 << " and s2 = " << s2 << endl;

    s1.swap(s2); // Member function swap

    // Print after member swap
    cout << "After swapping, s1 = " << s1 << " and s2 = " << s2 << endl;

    swap(s1, s2); // Non-member swap (std::swap)

    // Print after another swap
    cout << "After another swap, s1 = " << s1 << " and s2 = " << s2 << endl;


    // Add spacing for clarity
    cout << "\n==========================\n\n";


    // ==========================
    // Part 2: BufferManager swapping (from overload.cc)
    // ==========================
    BufferManager a(5), b(6); // Create two objects with different sizes

    cout << "Before swapping\n";

    cout << "a is ";
    a.print(); // Print object a

    cout << endl << "b is ";
    b.print(); // Print object b

    // Perform custom swap (calls our overloaded version)
    swap(a, b);

    cout << endl << endl << "After swapping\n";

    cout << "a is ";
    a.print(); // Print swapped object a

    cout << endl << "b is ";
    b.print(); // Print swapped object b

    cout << endl;

    return 0; // End program
}
```

# Lvalues and Rvalues
An lvalue is an expression that refers to a persistent object with a specific memory location—you can take its address and it typically appears on the left side of an assignment (like a named variable int x). An rvalue, on the other hand, is a temporary value that does not have a stable memory location and usually appears on the right side of an assignment (like 5 or x + 1). The key difference is that lvalues represent objects you can modify and refer to repeatedly, while rvalues represent temporary results that are used briefly and then discarded.

```cpp
#include <iostream>                         // Provides std::cout, std::endl for console output

using namespace std;                        // Allows us to write cout instead of std::cout

// ==========================================================
// SECTION 1: LVALUE REFERENCE BASICS
// ==========================================================

void lvalue_demo() {                        // Function to demonstrate how lvalue references behave

    // int& x = 3;                          // ERROR:
                                            // 3 is an rvalue (temporary value, no memory address you can modify)
                                            // Non-const lvalue references (int&) can ONLY bind to lvalues

    const int& x = 3;                       // VALID:
                                            // const lvalue references CAN bind to rvalues
                                            // The compiler creates a temporary variable behind the scenes
                                            // and binds 'x' to it safely (read-only)

    cout << "lvalue_demo: x = " << x << endl; // Prints the value stored in the temporary (3)
}

// ==========================================================
// SECTION 2: FUNCTION OVERLOADING WITH LVALUES & RVALUES
// ==========================================================

class Test { };                              // Simple empty class (no members needed for this demo)

// -------- Different overloads depending on value category --------

// 1. Non-const lvalue reference
void func(Test& test) {
    cout << "lvalue argument\n";             // Called when passing a modifiable named object (lvalue)
}

// 2. Const lvalue reference
void func(const Test& test) {
    cout << "const lvalue argument\n";       // Called when passing const objects OR when no better match exists
}

// 3. Rvalue reference
void func(Test&& test) {
    cout << "rvalue argument\n";             // Called when passing temporary objects (rvalues)
}

void overload_demo() {
    Test test;                               // 'test' is an lvalue (it has a name and memory location)
    const Test ctest;                        // 'ctest' is a const lvalue (cannot be modified)

    cout << "Calling func(test): ";
    func(test);                              // Matches Test& (best match: non-const lvalue reference)

    cout << "Calling func(ctest): ";
    func(ctest);                             // Matches const Test&
                                             // Cannot bind to Test& because object is const

    cout << "Calling func(Test()): ";
    func(Test());                            // Test() creates a temporary object → rvalue
                                             // Matches Test&& (rvalue reference)

    // IMPORTANT NOTE:
    // If the rvalue overload (Test&&) didn't exist,
    // the const Test& version would accept the rvalue instead.
}

// ==========================================================
// SECTION 3: RVALUE REFERENCES
// ==========================================================

void rvalue_ref_demo() {
    int y{2};                                // 'y' is an lvalue (named variable)

    // func(y);                              // If func expects int&&, this fails:
                                             // rvalue references (int&&) cannot bind to lvalues directly

    // Lambda function that accepts an rvalue reference
    auto func_int = [](int&& x) {             // 'x' is an rvalue reference parameter
        cout << "rvalue_ref_demo: x = " << x << endl;
    };

    func_int(2);                             // 2 is an rvalue → perfectly matches int&&

    // IMPORTANT CONCEPT:
    // Even though 'x' is declared as int&&,
    // INSIDE the function it becomes an lvalue (because it has a name!)
}

// ==========================================================
// MAIN FUNCTION (PROGRAM ENTRY POINT)
// ==========================================================

int main() {

    cout << "=== Lvalue Demo ===\n";
    lvalue_demo();                           // Demonstrates binding rules for lvalue references

    cout << "\n=== Overload Demo ===\n";
    overload_demo();                         // Shows how C++ chooses function overloads

    cout << "\n=== Rvalue Ref Demo ===\n";
    rvalue_ref_demo();                       // Demonstrates rvalue reference usage

    return 0;                                // Indicates successful execution
}
```

## Move operators (Copy constructor, move constructor, copy assignmen operator, move assignment operator)
In C++, the copy constructor and copy assignment operator create or update objects by duplicating data from another existing object (an lvalue), while the move constructor and move assignment operator improve efficiency by transferring resources from temporary or explicitly moved objects (rvalues) instead of copying them; the copy constructor is used when a new object is initialized from another, whereas the copy assignment operator is used when an already existing object is assigned new values, and similarly, the move constructor initializes a new object by “stealing” resources (like memory) from a temporary object, while the move assignment operator replaces the contents of an existing object by taking over those resources, leaving the source object in a valid but typically empty state—this distinction is crucial for performance, especially when working with large or resource-heavy objects.
```cpp
#include <iostream>              // Include input-output stream library

using namespace std;             // Avoid writing std:: everywhere

class MyClass {};                // Empty helper class (used as a member)

// Class demonstrating copy & move semantics
class Test {
  private:
    int i{0};                   // Integer member initialized to 0
    MyClass m;                  // Object of MyClass

  public:
    Test() = default;           // Default constructor (compiler-generated)

    // Copy constructor
    Test(const Test& other)     // Takes const reference to another Test object
        : i(other.i),           // Copy integer value
          m(other.m)            // Copy MyClass object
    {
        cout << "Copy constructor called" << endl; // Debug message
    }

    // Move constructor
    Test(Test&& other) noexcept // Takes rvalue reference (temporary object)
        : i(other.i),           // BUG FIXED: should copy from other.i (original had i(i))
          m(std::move(other.m)) // Move MyClass object instead of copying
    {
        cout << "Move constructor called" << endl; // Debug message
    }

    // Copy assignment operator
    Test& operator=(const Test& other) {   // Assign from lvalue
        cout << "Copy assignment operator called" << endl;

        if (this != &other) {              // Avoid self-assignment
            i = other.i;                  // Copy integer
            m = other.m;                 // Copy object
        }
        return *this;                     // Return current object
    }

    // Move assignment operator
    Test& operator=(Test&& other) noexcept { // Assign from rvalue
        cout << "Move assignment operator called" << endl;

        if (this != &other) {              // Avoid self-assignment
            i = other.i;                  // Transfer integer value
            m = std::move(other.m);       // Move object instead of copying
        }
        return *this;                     // Return current object
    }
};

int main() {
    Test test;                            // Default constructor

    cout << "Copying: ";
    Test test2 = test;                    // Calls copy constructor

    cout << "Moving temporary: ";
    Test test3 = Test();                  // Temporary → move constructor

    cout << "Moving rvalue ref: ";
    Test test4(std::move(test));          // Explicit move using std::move

    cout << endl;

    Test test5;
    cout << "Assigning: ";
    test5 = test;                         // Copy assignment

    Test test6;
    cout << "Assigning from temporary: ";
    test6 = Test();                       // Move assignment
}
```
