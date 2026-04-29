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
```cpp
#include <iostream>                     // Include input/output stream library

using namespace std;                   // Avoid std:: prefix for convenience

// ---------- SECTION 1: LVALUE REFERENCE BASICS ----------
void lvalue_demo() {                   // Function to demonstrate lvalue reference behavior
    // int& x = 3;                    // ERROR: cannot bind non-const lvalue reference to rvalue (3)
    const int& x = 3;                 // OK: const lvalue reference can bind to rvalue
    cout << "lvalue_demo: x = " << x << endl; // Print value
}

// ---------- SECTION 2: FUNCTION OVERLOADING (Lvalue vs Rvalue) ----------
class Test { };                        // Simple empty class

void func(Test& test) {                // Overload for non-const lvalue reference
    cout << "lvalue argument\n";       // Prints when lvalue is passed
}

void func(const Test& test) {          // Overload for const lvalue reference
    cout << "const lvalue argument\n";// Prints when const lvalue is passed
}

void func(Test&& test) {               // Overload for rvalue reference
    cout << "rvalue argument\n";      // Prints when rvalue is passed
}

void overload_demo() {                 // Function to demonstrate overload resolution
    Test test;                        // Create non-const object (lvalue)
    const Test ctest;                 // Create const object (const lvalue)

    cout << "Calling func(test): ";   // Message before call
    func(test);                       // Calls lvalue overload

    cout << "Calling func(ctest): ";  // Message before call
    func(ctest);                      // Calls const lvalue overload

    cout << "Calling func(Test()): "; // Message before call
    func(Test());                     // Calls rvalue overload (temporary object)
}

// ---------- SECTION 3: RVALUE REFERENCE BASICS ----------
void rvalue_ref_demo() {               // Function to demonstrate rvalue references
    int y{2};                         // Define an lvalue variable

    // func(y);                      // ERROR: cannot bind rvalue reference to lvalue

    auto func_int = [](int&& x) {     // Lambda with rvalue reference parameter
        cout << "rvalue_ref_demo: x = " << x << endl; // Print value
    };

    func_int(2);                      // OK: 2 is an rvalue
}

// ---------- MAIN FUNCTION ----------
int main() {                          // Entry point of the program
    cout << "=== Lvalue Demo ===\n";  // Section header
    lvalue_demo();                    // Run lvalue example

    cout << "\n=== Overload Demo ===\n"; // Section header
    overload_demo();                  // Run overload example

    cout << "\n=== Rvalue Ref Demo ===\n"; // Section header
    rvalue_ref_demo();                // Run rvalue reference example

    return 0;                         // Indicate successful execution
}
```
