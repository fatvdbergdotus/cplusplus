# Traditional C++
```
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
