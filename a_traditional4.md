(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++

## Run-time type information
### Typeid
```cpp
#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {};

int main() {
	Derived derived;
	Base *pBase = &derived;
	
	if (typeid(*pBase) == typeid(derived))
		cout << "pBase points to a Derived object" << endl;
	else
		cout << "pBase does not point to a Derived object" << endl;
}
```

### Type_info
```cpp
#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {};

int main() {
	Derived derived;
	Base *pBase = &derived;
	
	const type_info& tBase = typeid(*pBase);
	const type_info& tDerived = typeid(derived);
	
	cout << "Dynamic type of pBase is " << tBase.name() << endl;
	cout << "Dynamic type of derived is " << tDerived.name() << endl;
}
```

### Dynamic cast
Checks wheter it is possible to convert from the base class to a derived class at run-time.
```cpp
#include <iostream>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {
	public:
	void derived_func() { cout << "Calling derived_func()\n"; }
};

int main() {
	Derived d;
	Base *pBase = &d;
	
	Derived *pDerived = dynamic_cast<Derived *>(pBase);
	
	// Dangerous!
	pDerived->derived_func();
}
```

## Miscellaneous features

### Booleans
```cpp
#include <iostream>

using namespace std;

int main() {
	int x = -7;
	bool neg = x < 0;
	cout << "Is x negative?" << endl;
	cout << neg << endl; // 1
	cout << boolalpha << neg << endl; // true (because not zero)
}
```

### Without Explicit (implicit conversion allowed)
```cpp
#include <iostream>
using namespace std;

class Test {
    int value;
public:
    Test(int v) : value(v) {}   // NOT explicit

    void print() {
        cout << value << endl;
    }
};

void show(Test t) {
    t.print();
}

int main() {
    show(5);   // int → Test conversion happens automatically
}
```

### With Explicit (safer)
```cpp
#include <iostream>
using namespace std;

class Test {
    int value;
public:
    explicit Test(int v) : value(v) {}   // explicit constructor

    void print() {
        cout << value << endl;
    }
};

void show(Test t) {
    t.print();
}

int main() {
    // show(5);   ERROR: implicit conversion not allowed

    show(Test(5));   // must be explicit
}
```

