(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++

## Exceptions

### No try catch
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	cout << v[2] << endl;            // Invalid element - program continues in undefined state
	cout << v.at(2) << endl;        // Invalid element - exception thrown
}
```

### Try catch
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	try {
		cout << v.at(2) << endl;                // Throws an exception
	}
	catch (const std::exception& e) {           // Will handle all subclasses of std::exception
		cout << "Exception caught: " << e.what() << endl;               // Print out a description of the exception
	}
}
```

### Try catch with a throw
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	try {
		if (v.size() < 3)
			throw std::out_of_range("Oops");
		cout << v[2] << endl;
	}
	catch (const std::exception& e) {           // Will handle all subclasses of std::exception
		cout << "Exception caught: " << e.what() << endl;               // Print out a description of the exception
	}
}
```

### Promise to not throw exceptions
If the function does throw an exception, the program terminates immediately.

```cpp
#include <iostream>
using namespace std;

// Function that guarantees it will NOT throw exceptions
void func() noexcept {
    cout << "This function does not throw exceptions" << endl;
}

int main() {
    func();   // Safe to call, no exceptions expected
    return 0;
}
```

## Templates (generics)

```cpp
#include <iostream>
using namespace std;

// Template function (works with any type T)
template <typename T>
T add(T a, T b) {
    return a + b;   // Works as long as + is defined for T
}

int main() {
    // Using template with different data types
    cout << add<int>(2, 3) << endl;        // int version
    cout << add<double>(2.5, 3.5) << endl; // double version

    // Compiler can also deduce the type automatically
    cout << add(10, 20) << endl;           // T = int

    return 0;
}
```

## Namespaces

### Simple namespace
```cpp
#include <iostream>

using namespace std;

int x{23};                          // x defined in the global namespace

namespace A {
	int x{47};                          // x defined in the namespace A - hides global x
	void func() { 
		cout << "x = " << x << endl;        // Will use A's x ==> 47
		cout << "::x = " << ::x << endl;    // Will use global x ==> 23
	}
}

int main() {
	A::func();
}
```

```cpp
#include <iostream>
using namespace std;

// Define a namespace
namespace MyNamespace {
    int value = 10;

    void show() {
        cout << "Inside MyNamespace, value = " << value << endl;
    }
}

int main() {
    // Access namespace members using scope resolution operator ::
    cout << MyNamespace::value << endl;
    MyNamespace::show();

    return 0;
}
```

### Nested namespace
```cpp
#include <iostream>

namespace Outer {
    namespace Inner {
        void greet() {
            std::cout << "Hello from Inner namespace!" << std::endl;
        }
    }
}

int main() {
    Outer::Inner::greet();  // access nested namespace
    return 0;
}
```

### Inline namespace
```cpp
#include <iostream>

// Outer namespace
namespace Library {

    // Inline namespace (automatically used)
    inline namespace v1 {
        void print() {
            std::cout << "Version 1\n";
        }
    }

    // Another version (not inline)
    namespace v2 {
        void print() {
            std::cout << "Version 2\n";
        }
    }
}

int main() {
    Library::print();      // Calls v1::print() (default)
    Library::v2::print();  // Explicitly call version 2

    return 0;
```

## Synthesized functions
The following code demonstrates how C++ handles object creation and copying when no custom constructors or operators are defined: the compiler automatically provides a default constructor, copy constructor, and assignment operator, which are used when creating objects (Test test), copying them (Test test3 = test), and assigning them (test = test2); however, because the member variable i is never initialized, all objects contain undefined (garbage) values, showing the importance of explicitly initializing class members even when relying on compiler-generated behavior.

```cpp
#include <iostream>

using namespace std;

class Test {
    int i;   // Member variable (uninitialized!)

public:
    // Default constructor (currently missing)
    // If you uncomment this, it will initialize i
    // Test() : i(0) {}

    // Parameterized constructor
    // Test(int i) : i(i) {}

    // Copy constructor
    // Test(const Test& other) : i(other.i) {}

    // Assignment operator
    // Test& operator=(const Test& other) {
    //     i = other.i;
    //     return *this;
    // }

    // Destructor
    // ~Test() {}

    // Function to print value of i
    void print() {
        cout << i << endl;   // Undefined value if i is not initialized
    }
};

int main() {
    // Default constructor is called (compiler-generated)
    Test test;

    cout << "test after default constructor: ";
    test.print();   // i is uninitialized, garbage value

    // Another object using default constructor
    Test test2;

    cout << "test2 after default constructor: ";
    test2.print();  // also uninitialized

    // Copy constructor is called here
    Test test3 = test;

    cout << "test3 after copy constructor: ";
    test3.print();  // copies the same (garbage) value

    // Assignment operator is called here
    test = test2;

    cout << "test after assignment operator: ";
    test.print();   // now has same value as test2

    return 0;
}
```

## Casting 
### C-style cast (old, not recommended)
```cpp
#include <iostream>

using namespace std;

int main() {
	int c = 'A';
	cout << c << endl;
	cout << (char)c << endl;
}
```

### static_cast (most common, used for safe, compile-time conversions)
```cpp
#include <iostream>

using namespace std;

int main() {
	int c = 'A';
	cout << c << endl;
	cout << static_cast<char>(c) << endl;
}
```

### dynamic_cast (runtime, polymorphism)
```cpp
class Base { virtual void f() {} };
class Derived : public Base {};

Base* b = new Derived;
Derived* d = dynamic_cast<Derived*>(b);

if (d) {
    // successful cast
}
```

### Const_cast (Used to add or remove const)
Dangerous if you modify something that was originally const
```cpp
#include <iostream>

using namespace std;

void print(char *str) {       // Doesn't mutate str, but not declared const
    cout << str << endl;
}

int main() {
	const char *msg = "Hello, world!";
	//print(msg);               // Error - invalid conversion
	print(const_cast<char *>(msg));
}
```


