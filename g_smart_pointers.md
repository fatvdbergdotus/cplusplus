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
