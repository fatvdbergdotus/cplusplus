# Modern C++ Libraries

## Std::array
std::array is preferred over C-style arrays because it keeps the array’s size as part of its type, making code safer and easier to use, especially when passing arrays to functions. Unlike raw arrays, it provides useful features like .size(), .at() for bounds-checked access, and compatibility with standard algorithms such as std::sort, while still having no performance overhead since it’s stored on the stack. It also supports direct copying and assignment, which C-style arrays do not. Overall, std::array gives you the efficiency of traditional arrays with the safety and convenience of modern C++.

You need to provide the 5 in std::array<int, 5> because the size is part of the type itself, not just a runtime value. This means the compiler must know the exact number of elements at compile time so it can allocate the right amount of memory and enable features like .size() and safe copying. In fact, std::array<int, 5> and std::array<int, 10> are completely different types, not just arrays of different lengths. Without specifying the size, the compiler wouldn’t know how much space to reserve or how the object should behave, so the template requires it explicitly.

```cpp
#include <iostream>
#include <array>

using namespace std;

// --------------------------------------------------
// Function for built-in C-style arrays
// - Takes pointer to first element (int*)
// - 'n' is required because size information is lost
// --------------------------------------------------
void somefunc(int *pi, int n) {
    for (int i = 0; i < n; ++i)
        cout << pi[i] << ", ";
    cout << endl;
}

// --------------------------------------------------
// Function for std::array
// - Size is part of the type (array<int, 5>)
// - Can safely use .size() and iterators
// --------------------------------------------------
void somefunc(array<int, 5> arr) {
    // Access via index
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << ", ";

    // Access via iterator
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << ", ";

    cout << endl;
}

int main() {

    // ==================================================
    // SECTION 1: Basic std::array usage
    // ==================================================
    cout << "=== Array Usage ===" << endl;

    // Declare and initialize std::array
    array<int, 5> arr {1, 2, 3, 4, 5};

    // Access element by index (no bounds checking!)
    cout << "arr[3] = " << arr[3] << endl;

    // Modify element
    arr[2] = 6;
    cout << "After assignment, arr[2] = " << arr[2] << endl;

    // Copy array (deep copy)
    array<int, 5> five_els;
    five_els = arr;

    // ==================================================
    // SECTION 2: Different ways to loop over array
    // ==================================================
    cout << "\n=== Array Loops ===" << endl;

    // Iterator-based loop
    cout << "Iterator loop: ";
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << ", ";
    cout << endl;

    // Range-based for loop (modern C++)
    cout << "Range-for loop: ";
    for (auto el : arr)
        cout << el << ", ";
    cout << endl;

    // Classic index-based loop
    cout << "Indexed loop: ";
    for (size_t i = 0; i < arr.size(); ++i)
        cout << arr[i] << ", ";
    cout << endl;

    // Show copied array
    cout << "Elements of five_els: ";
    for (auto el : five_els)
        cout << el << ", ";
    cout << endl;

    // ==================================================
    // SECTION 3: Passing arrays to functions
    // ==================================================
    cout << "\n=== Functions ===" << endl;

    // -------- Built-in array --------
    cout << "Built-in array\n";

    // C-style array
    int raw_arr[] = {1, 2, 3, 4, 5};

    // Calculate number of elements manually
    int n = sizeof(raw_arr) / sizeof(raw_arr[0]);

    // Pass pointer + size
    somefunc(raw_arr, n);

    // -------- std::array --------
    cout << "std::array\n";

    // Size is known at compile time
    array<int, 5> std_arr {1, 2, 3, 4, 5};

    // Pass directly (size is preserved)
    somefunc(std_arr);

    return 0;
}
```

