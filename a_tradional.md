# Traditional C++
## C++ Parameter Passing: Value vs Pointer vs Reference

This section explains three common ways to pass arguments to functions in C++:
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

## String versus Vectors

### String index
```
#include <iostream>
#include <string>

using namespace std;

int main() {
    string hello("Hello");  
    // Creates a std::string object and initializes it with "Hello"
    // Memory is allocated dynamically and managed automatically

    cout << hello[0];  
    // Accesses first character → 'H' (index starts at 0)

    cout << hello[4];  
    // Accesses fifth character → 'o'

    hello[3] = 'b';  
    // Modifies the string: "Hello" → "Helbo"
    // Strings in C++ are mutable (can be changed)

    int i;
    for (i = 0; i < hello.size(); ++i) {
        cout << "Element with index " << i 
             << " has value " << hello[i] << "\n";
    }
    // Iterates through the string using .size()
    // Prints each character and its index

} 
// At the end of main(), the string is automatically destroyed
// Memory is freed (RAII — no manual delete needed)
```

### Vector index
```
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;  
    // Creates an empty vector of integers
    // No elements initially, size = 0

    vec.push_back(4);  
    vec.push_back(2);  
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(1);
    // Adds elements to the end of the vector
    // After this: vec = {4, 2, 3, 4, 1}

    cout << "Element with index 0 has value " << vec[0] << endl;
    // First element → 4

    cout << "Element with index 2 has value " << vec[2] << endl;
    // Third element → 3

    cout << "Element with index 4 has value " << vec[4] << endl;
    // Fifth element → 1 (note: comment in original code had a small mistake)

    cout << endl << "Modifying element with index 2 to have value 6" << endl;
    vec[2] = 6;
    // Changes vector: {4, 2, 3, 4, 1} → {4, 2, 6, 4, 1}

    cout << endl << "Printing out all elements: " << endl;

    int i;
    for (i = 0; i < vec.size(); ++i) {
        cout << "Element with index " << i 
             << " has value " << vec[i] << endl;
    }
    // Iterates through all elements using .size()
}
```

### String find
```
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str ("Hello world");
	cout << "The string is \"" << str << "\"" << endl;
	cout << "First occurrence of \'o\' is at index " << str.find('o') << endl;     // Returns 4
	cout << "First occurrence of \"or\" is at index " << str.find("or") << endl;   // Returns 7

	cout << "Does 'O' occur in the string? ";
	
	if (str.find('O') == string::npos)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
}
```

## Iterators

### String loop
```
#include <iostream>   // Required for input/output (cout)

using namespace std;

int main() {
    // Define a character array (not null-terminated, just 5 characters)
    const char str[] = {'H','e','l','l','o'};

    // Pointer to one past the last element of the array
    // This is a common technique for marking the "end"
    const char *pEnd = str + 5;

    // Pointer to the first element of the array
    const char *p = str;

    // Loop until the pointer reaches the end position
    while (p != pEnd) {
        // Dereference pointer to get current character and print it
        cout << *p << ", ";

        // Move pointer to the next character in the array
        ++p;
    }

    // Program ends successfully
    return 0;
}
```

### String iterators
```
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str("Hello");
	
	for (string::iterator it = str.begin(); it != str.end(); ++it)
        cout << *it << ", ";
}
```



