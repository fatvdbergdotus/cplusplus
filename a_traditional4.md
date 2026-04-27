# Traditional C++

## Run-time type information
### Typeid
```
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
```
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
```
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




