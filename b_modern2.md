# Modern C++

## Constructors
```cpp
#include <iostream>
using namespace std;

// ===== Version 1: init.cc =====
class FridgeInit {
public:
    FridgeInit() {
        cout << "[Init] Constructor called\n";
    }
};

// ===== Version 2: inplace.cc =====
class FridgeInplace {
    int temperature{2};
public:
    FridgeInplace() {
        cout << "[Inplace] temperature = " << temperature << endl;
    }
};

// ===== Version 3: constructors.cc =====
class FridgeConstructors {
    int temperature;
public:
    FridgeConstructors(int t) : temperature(t) {
        cout << "[Constructors] temperature = " << temperature << endl;
    }
};

// ===== Version 4: default.cc =====
class FridgeDefault {
    int temperature;
public:
    FridgeDefault() {
        temperature = 2;
        cout << "[Default] temperature = " << temperature << endl;
    }
};

// ===== Version 5: delegate.cc =====
class FridgeDelegate {
    int temperature;

public:
    FridgeDelegate() : FridgeDelegate(2) {}

    FridgeDelegate(int t) : temperature(t) {
        cout << "[Delegate] temperature = " << temperature << endl;
    }
};

// ===== ONE main() =====
int main() {
    cout << "Creating all fridge versions:\n\n";

    FridgeInit f1;
    FridgeInplace f2;
    FridgeConstructors f3(5);
    FridgeDefault f4;
    FridgeDelegate f5;

    return 0;
}
```
