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
