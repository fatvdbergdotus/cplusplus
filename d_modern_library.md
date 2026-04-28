# Modern C++ Library features

## Initializer list
```cpp
#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

using namespace std;

// ===== Class demonstrating initializer_list in a constructor =====
class Test {
    vector<int> vec;  // Container to store integers

public:
    // Constructor accepts an initializer_list and uses it to initialize the vector
    Test(initializer_list<int> il) : vec(il) {}

    // Prints all elements in the vector
    void print() {
        for (auto i : vec)
            cout << i << ", ";
        cout << endl;
    }
};

// Runs the constructor demo
void run_constructor_demo() {
    // Create object using initializer_list syntax
    Test test{3, 4, 5};

    // Print stored values
    test.print();
}

// ===== Function demonstrating initializer_list in function parameters =====

// Prints a list of station names
void announce(initializer_list<string> stations) {
    cout << "This train will stop at: ";

    // Loop through each station and print it
    for (auto station : stations)
        cout << station << ", ";

    cout << endl;
}

// Runs the loop demo
void run_loop_demo() {
    // Example: fast train (only one stop)
    cout << "This is a fast train to London Waterloo.\n";
    announce({"London Waterloo only"});
    cout << "\n";

    // Example: stopping service (multiple stops)
    cout << "This is a stopping service to London Waterloo.\n";
    announce({"Clapham Junction", "Vauxhall", "London Waterloo"});
}

// ===== Entry point of the program =====
int main() {
    // Run constructor example
    cout << "=== Constructor Demo ===\n";
    run_constructor_demo();

    // Run initializer_list loop example
    cout << "\n=== Loop Demo ===\n";
    run_loop_demo();

    return 0; // Indicate successful execution
}
```
