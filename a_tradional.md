# Traditional C++
## C++ Parameter Passing: Value vs Pointer vs Reference

This document explains three common ways to pass arguments to functions in C++:
- Pass by Value
- Pass by Pointer
- Pass by Reference

---

### 1. Pass by Value

```cpp
#include <iostream>
using namespace std;

int func(int y) {
    cout << "Address of y is " << &y << endl;
    return y;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    int z = func(x);
    cout << "Address of z is " << &z << endl;
    cout << "After calling func(), z = " << z << endl;
}
```
### 2. Pass by pointer

```cpp
#include <iostream>
using namespace std;

void func(int *y) {
    cout << "Address of y is " << y << endl;
    *y = 1;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    func(&x);
    cout << "After calling func(), x = " << x << endl;
}
```

### 3. Pass by reference

```cpp
#include <iostream>
using namespace std;

void func(int& y) {
    cout << "Address of y is " << &y << endl;
    y = 1;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    func(x);
    cout << "After calling func(), x = " << x << endl;
}
```
