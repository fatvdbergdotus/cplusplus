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
```
    return 0; // End program
}
