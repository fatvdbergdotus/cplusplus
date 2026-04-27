# Traditional C++

## Exceptions

### No try catch
```
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
```
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
```
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
```
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

```
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
```
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

```
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



