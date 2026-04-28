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

## Miscellaneous Containers
A forward_list in C++ is a lightweight container from the Standard Library that implements a singly linked list, meaning each element stores a value and a pointer to the next element only, allowing traversal in one direction (forward). It is memory-efficient compared to a doubly linked list because it doesn’t store backward links, but this also means it lacks features like reverse traversal and direct access by index. Elements are typically added or removed at the front using push_front() and pop_front(), and other operations like insert_after() and erase_after() are used because you can only modify elements relative to a known position. It’s best used when you need fast insertions/removals at the beginning and don’t require random access or backward navigation.

An unordered_map in C++ is a container from the Standard Library that stores key–value pairs using a hash table, which allows for very fast average-time operations like insertion, deletion, and lookup (typically O(1)). Unlike a regular map, it does not keep elements sorted, so the order of items is unpredictable and may change. Each element is accessed using a unique key, and the container uses a hash function to determine where to store and find values efficiently. It’s ideal when you need quick access to data by key and don’t care about maintaining any specific order of elements.

```cpp
#include <iostream>
#include <forward_list>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

// ---------- forward_list helper function ----------
// Prints all elements of a forward_list
void print(const forward_list<int>& fl) {
    cout << "List elements are: ";
    for (auto node : fl)
        cout << node << ",";
    cout << endl;
}

// ---------- forward_list demo ----------
// Demonstrates basic operations on a forward_list
void demo_forward_list() {
    forward_list<int> fl;

    // Add elements to the front of the list
    // (Note: forward_list only supports push_front)
    fl.push_front(2);
    fl.push_front(4);
    fl.push_front(1);
    fl.push_front(5);
    fl.push_front(3);

    // Check if the list is empty
    cout << "fl is" << (fl.empty() ? "" : " not") << " empty" << endl;
    print(fl);

    // Sort the list (ascending order)
    cout << "\nSorting list\n";
    fl.sort();
    print(fl);

    // Insert an element AFTER a specific value (3)
    cout << "\nInserting element in list\n";
    auto three = find(fl.begin(), fl.end(), 3); // find element 3
    if (three != fl.end()) {
        fl.insert_after(three, 0); // insert 0 after 3
    }
    print(fl);

    // Remove the first element
    // erase_after(before_begin()) removes the first node
    cout << "\nRemoving first element\n";
    fl.erase_after(fl.before_begin());
    print(fl);

    // Clear all elements from the list
    cout << "\nClearing list\n";
    fl.clear();

    // Check again if empty
    cout << "fl is" << (fl.empty() ? "" : " not") << " empty" << endl;
    print(fl);
}

// ---------- map / unordered_map demo ----------
// Demonstrates difference between unordered_map and map
void demo_maps() {
    // unordered_map: NOT sorted, faster average access
    unordered_map<string, int> scores;

    // Insert key-value pairs
    scores.insert({"Graham", 78});
    scores.insert({"Grace", 66});
    scores.insert({"Hareesh", 77});

    // Print unordered_map (order is arbitrary)
    cout << "\nUnordered map\n";
    for (auto score : scores)
        cout << score.first << " has a score of " << score.second << endl;

    // map: sorted by key (alphabetically for strings)
    map<string, int> sorted_scores;

    // Copy elements from unordered_map to map
    copy(scores.begin(), scores.end(),
         inserter(sorted_scores, sorted_scores.end()));

    // Print sorted map
    cout << "\nstd::map (sorted)\n";
    for (auto score : sorted_scores)
        cout << score.first << " has a score of " << score.second << endl;
}

// ---------- main function ----------
// Entry point of the program
int main() {
    cout << "=== Forward List Demo ===\n";
    demo_forward_list(); // run forward_list example

    cout << "\n=== Map Demo ===\n";
    demo_maps(); // run map example

    return 0; // indicate successful execution
}
```
