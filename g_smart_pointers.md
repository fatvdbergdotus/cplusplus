# Smart pointers
A smart pointer is an object in languages like C++ that behaves like a regular pointer but also manages the lifetime of dynamically allocated memory automatically, helping prevent leaks and dangling pointers. Instead of requiring the programmer to manually delete memory, smart pointers use techniques like RAII (Resource Acquisition Is Initialization) to ensure resources are released when the pointer goes out of scope. Common types include std::unique_ptr for exclusive ownership, std::shared_ptr for shared ownership with reference counting, and std::weak_ptr for non-owning references that avoid circular dependencies. By encapsulating memory management logic, smart pointers make code safer, cleaner, and less error-prone.

In C++, std::unique_ptr, std::shared_ptr, and std::weak_ptr are smart pointers that differ mainly in how they manage ownership of dynamically allocated objects: std::unique_ptr provides exclusive ownership, meaning only one pointer can own the object at a time and it cannot be copied (only moved), making it lightweight and efficient; std::shared_ptr allows multiple owners of the same object using reference counting, and the object is automatically deleted when the last shared pointer releases it, though this adds some overhead and can lead to memory leaks if circular references occur; std::weak_ptr is a non-owning observer used alongside shared_ptr, meaning it does not contribute to the reference count and is primarily used to safely access shared objects without preventing their deletion, especially useful for breaking cyclic dependencies.

## Unique pointer
```cpp
#include <iostream>     // For input/output (cout, endl)
#include <memory>       // For smart pointers like unique_ptr

using namespace std;    // Avoid writing std:: repeatedly

// ==========================
// Shared data structure
// ==========================

// Data structure representing a point on the screen
struct point {
    int x;              // x-coordinate
    int y;              // y-coordinate
};

// ==========================
// Factory function example
// ==========================

// Function that creates and returns a unique_ptr to a point
unique_ptr<point> point_ptr(int x, int y) { 
    point p{0};                         // Create a local point instance (initialized to 0)
    p.x = x;                            // Assign x value
    p.y = y;                            // Assign y value
    
    // Create a unique_ptr managing a copy of p
    unique_ptr<point> ptr{ make_unique<point>(p) };
    
    return ptr;                         // Return ownership (move happens automatically)
}

// ==========================
// Demo: basic unique_ptr usage
// ==========================
void demo_example() {
    // Create a unique_ptr to a point initialized with {3, 6}
    auto p{ make_unique<point>( point{3, 6} ) };

    // Access members using -> (like a normal pointer)
    cout << "Example: " << p->x << ", " << p->y << endl;
}

// ==========================
// Demo: factory function usage
// ==========================
void demo_factory() {
    // Call factory function to get a unique_ptr
    auto upp { point_ptr(3, 6) };

    // Print values stored in the point
    cout << "Factory: " << upp->x << ", " << upp->y << endl;
}

// ==========================
// Demo: initialization styles
// ==========================
void demo_init() {
    // Allocate a single int with value 42
    unique_ptr<int> p1{ new int(42) };      // C++11 style (manual new)

    // Allocate array of 6 ints
    unique_ptr<int []> p2{ new int[6] };    // Array version of unique_ptr

    // Preferred modern way (C++14+)
    auto p3{ make_unique<int>(42) };        // Safer and cleaner
    auto p4{ make_unique<int []>(6) };      // Array version

    // Access values
    cout << "Init p1: " << *p1 << endl;     // Dereference single object
    cout << "Init p2[0]: " << p2[0] << endl;// Access array element

    // Transfer ownership using move
    unique_ptr<int> p5(std::move(p3));      // p3 becomes nullptr after move

    // NOTE: p4 cannot be moved into unique_ptr<int> (different type)
}

// ==========================
// Main function
// ==========================
int main() {

    demo_example();     // Run first demo
    demo_factory();     // Run factory demo
    demo_init();        // Run initialization demo

    return 0;           // Indicate successful execution
}
```

## Unique pointer appications
```cpp
#include <iostream>      // Provides std::cout for console output
#include <memory>        // Provides smart pointers like std::unique_ptr

/// ===== Simulated C-style Networking API =====
struct destination { /* Represents a remote endpoint (details omitted) */ };

struct connection { /* Represents an active connection (details omitted) */ };

// Opens a connection to a destination and returns it by value
connection connect(destination dest) {
    std::cout << "Connecting\n";   // Log that a connection is being established
    connection conn;               // Create a connection object
    return conn;                   // Return it (copy or move)
}

// Closes a connection
void disconnect(connection conn) {
    std::cout << "Disconnecting\n"; // Log that the connection is closing
}
/// ===== End of C-style API =====


// --- Example 1: Incorrect use of std::unique_ptr ---
void get_data_bad(const destination& dest) {
    connection conn = connect(dest);     // Create a connection on the stack

    // PROBLEM:
    // unique_ptr assumes ownership of a heap-allocated object.
    // Here we pass the address of a stack variable → leads to undefined behavior
    // when unique_ptr tries to delete it.
    std::unique_ptr<connection> ptr(&conn);

    std::cout << "Getting data...\n";    // Simulate work
}   // ptr goes out of scope → tries to delete stack memory →  BUG


// --- Example 2: Custom deleter (still problematic design) ---

// Lambda that defines how to properly "close" a connection
auto end_connection = [](connection* conn) {
    disconnect(*conn);  // Call API cleanup function
};

void get_data_custom_deleter(const destination& d) {
    connection conn = connect(d);   // Stack-allocated connection

    // Uses unique_ptr with a custom deleter
    // This avoids calling delete, but still manages a stack object → risky design
    std::unique_ptr<connection, decltype(end_connection)> p(&conn, end_connection);

    std::cout << "Getting data...\n";  // Simulate work
}   // Calls end_connection, but does NOT delete memory (safe-ish but awkward)


// --- Example 3: Proper use of polymorphism with unique_ptr ---

#include <vector>   // Needed for std::vector

using namespace std;  // Avoids std:: prefix (not recommended in headers, okay in examples)

// Abstract base class
class Shape {
public:
    virtual void draw() = 0;        // Pure virtual function → must be implemented
    virtual ~Shape() = default;     // Virtual destructor for safe polymorphic deletion
};

// Derived class: Circle
class Circle : public Shape {
public:
    void draw() override {          // Override base class method
        cout << "I'm a Circle!\n";  // Print shape type
    }
};

// Derived class: Triangle
class Triangle : public Shape {
public:
    void draw() override {
        cout << "I'm a Triangle!\n";
    }
};

// Derived class: Square
class Square : public Shape {
public:
    void draw() override {
        cout << "I'm a Square!\n";
    }
};


// --- Main demonstrating correct modern C++ usage ---
int main() {
    destination dest;   // Create a destination object

    // Demonstrate problematic patterns (for learning only)
    get_data_bad(dest);               //  Undefined behavior
    get_data_custom_deleter(dest);    //  Works but not ideal design

    // Correct usage of unique_ptr with polymorphism
    vector<unique_ptr<Shape>> shapes;  // Vector of owning smart pointers

    // Create objects safely on heap and transfer ownership into vector
    shapes.emplace_back(make_unique<Circle>());
    shapes.emplace_back(make_unique<Triangle>());
    shapes.emplace_back(make_unique<Square>());

    // Iterate and call virtual function → runtime polymorphism
    for (auto& it : shapes)
        it->draw();

    return 0;  // Indicate successful execution
}
```

## Interface/Implementation Separation
```cpp
#include <iostream>              // for std::cout
#include <memory>                // for std::unique_ptr

// ===================== Date (formerly Date.h) =====================

// Concrete implementation class (hidden in pImpl normally)
class Date {
    int day;                    // stores day
    int month;                  // stores month
    int year;                   // stores year

public:
    // Constructor initializes all members
    Date(int day, int month, int year) : day(day), month(month), year(year) {}

    // Setter for day
    void set_day(int d) { 
        day = d;                // assign new day
    }

    // Print date in DD/MM/YYYY format
    void print() { 
        std::cout << day << "/" << month << "/" << year; // output formatted date
    }
};

// ===================== Handle (formerly Handle.h + Handle.cpp) =====================

// Forward declaration is not needed anymore since Date is above,
// but kept conceptually for pImpl understanding
// class Date;

// Handle class using pImpl idiom
class Handle {
    std::unique_ptr<Date> body; // pointer to implementation (Date)

public:
    // Constructor: creates the hidden implementation
    Handle(int day, int month, int year) {
        body = std::make_unique<Date>(day, month, year); // allocate Date safely
    }

    // Destructor (default is enough because unique_ptr cleans up)
    ~Handle() = default;

    // Move constructor (defaulted for efficiency)
    Handle(Handle&&) noexcept = default;

    // Move assignment operator (defaulted)
    Handle& operator=(Handle&&) noexcept = default;

    // Forward set_day to implementation
    void set_day(int day) {
        body->set_day(day);     // delegate to Date
    }

    // Forward print to implementation
    void print() {
        body->print();          // delegate to Date
    }
};

// ===================== Client (formerly Client.cpp) =====================

int main() {
    // Date date(16, 11, 2019); // direct usage (commented out in original)

    Handle date(16, 11, 2019); // create Handle object (pImpl wrapper)

    date.print();              // print initial date
    std::cout << "\n";         // newline

    date.set_day(17);          // modify day through Handle

    date.print();              // print updated date
    std::cout << "\n";         // newline

    return 0;                  // successful execution
}
```

## Shared pointer
```cpp
#include <iostream>   // Includes input/output stream library for cout
#include <memory>     // Includes smart pointers like shared_ptr

using namespace std;  // Allows using standard library names without std:: prefix

int main() {
    // Create a shared_ptr that manages an int initialized to 36
    auto ptr{make_shared<int>(36)};
    
    // Print the value pointed to by ptr
    cout << "shared_ptr's data is " << *ptr << endl;
    
    // Copy the shared_ptr (both ptr and ptr2 now share ownership)
    auto ptr2 = ptr;
    
    // Print the value again (same underlying data)
    cout << "Copied shared_ptr's data is " << *ptr << endl;
    
    // Declare an empty shared_ptr
    shared_ptr<int> ptr3;
    
    // Assign ptr to ptr3 (now ptr, ptr2, and ptr3 share ownership)
    ptr3 = ptr;
    
    // Print the value again
    cout << "Assigned shared_ptr's data is " << *ptr << endl;
}
```

## Weak pointer
```cpp
#include <iostream>   // for std::cout, std::endl
#include <memory>     // for std::shared_ptr, std::weak_ptr, std::make_shared

using namespace std;  // avoid writing std:: repeatedly (not recommended in large projects)

int main() {

    // Create a shared_ptr that owns an integer with value 36
    auto ptr{make_shared<int>(36)};   // reference count = 1

    // Print the value stored in shared_ptr
    cout << "shared_ptr's data is " << *ptr << endl;

    // Create a weak_ptr that observes ptr (does NOT increase reference count)
    weak_ptr<int> wptr = ptr;         // reference count still = 1

    // Reset ptr, destroying the managed object (since ref count goes to 0)
    ptr = nullptr;                   // object deleted, wptr becomes expired

    // Try to convert weak_ptr back to shared_ptr safely
    shared_ptr<int> sp1 = wptr.lock();  // lock() returns nullptr if object is gone

    // Check if the object is still valid
    if (sp1) {                         // true if object still exists
        cout << "shared_ptr's data is " << *sp1 << endl;
    }
    else {
        cout << "shared_ptr not available" << endl;  // expected path here
    }

    // Attempt to directly construct shared_ptr from weak_ptr
    // This will throw std::bad_weak_ptr if the object is already destroyed
    shared_ptr<int> sp2(wptr);        // unsafe if expired!

    return 0;                         // indicate successful program execution
}
```
