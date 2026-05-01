(c) 2026 Freek van den Berg. All rights reserved.

# C++ 17 Highlights

## Constructors and argument deduction
```cpp
#include <iostream>        // for std::cout
#include <tuple>           // for std::tuple
#include <mutex>           // for std::mutex, std::lock_guard
#include <vector>          // for std::vector
#include <array>           // for std::array
#include <string>          // for std::string

using namespace std::literals; // enables "text"s string literal

std::mutex global_mtx;     // global mutex for demonstration

// ---------- TEMPLATE CLASS EXAMPLE (older.cc merged) ----------
template <typename T>      // define a template with type T
class Test {
public:
    Test(T t) {}           // constructor taking a value of type T
    // ... (other members could go here)
};

// ---------- PRINT FUNCTIONS (nested.cc merged) ----------

// print a 1D vector
void print(const std::vector<int>& vec)
{
    std::cout << "1 dimensional vector: "; // label output
    for (auto v : vec)                    // iterate over elements
        std::cout << v << ", ";           // print each element
    std::cout << '\n';                    // newline
}

// print a 2D vector
void print(const std::vector<std::vector<int>>& vec)
{
    std::cout << "2 dimensional vector:\n"; // label output
    int n = 0;                              // row counter
    for (auto vi : vec) {                   // iterate rows
        std::cout << "Row " << ++n << ": "; // print row number
        for (auto v : vi) {                 // iterate columns
            std::cout << v << ", ";         // print element
        }
        std::cout << '\n';                  // newline after each row
    }
}

// ---------- MAIN FUNCTION ----------
int main()
{
    // ----- Class Template Argument Deduction (deduced.cc) -----

    std::pair pr(1, 3.142); // deduced as std::pair<int, double>
    std::cout << "Pair elements: " << pr.first << ", " << pr.second << "\n";

    std::tuple tup{1, 2.0, "three"s}; // deduced tuple types
    std::cout << "Tuple elements: "
              << std::get<0>(tup) << ", "
              << std::get<1>(tup) << ", "
              << std::get<2>(tup) << "\n";

    std::vector vec{1, 2, 3}; // deduced as std::vector<int>
    std::cout << "Vector elements: ";
    for (auto v : vec)        // iterate vector
        std::cout << v << ", ";
    std::cout << "\n";

    std::array arr{"Bart"s, "Lisa"s, "Maggie"s}; // deduced std::array<std::string, 3>
    std::cout << "Array size: " << arr.size() << "\n";
    std::cout << "Array elements: ";
    for (auto a : arr)        // iterate array
        std::cout << a << ", ";
    std::cout << "\n";

    std::lock_guard lk(global_mtx); // lock mutex using CTAD

    // ----- Nested vector examples (nested.cc) -----

    std::vector v1{1, 2, 3};  // vector<int>
    print(v1);                // print 1D

    std::vector v2{4, 5, 6, 7}; // vector<int>
    print(v2);                  // print 1D

    std::vector v3{v1, v2};   // vector<vector<int>>
    print(v3);                // print 2D

    std::vector v4{v1};       // still vector<int>, not nested
    print(v4);                // print 1D

    // ----- Template deduction example (older.cc) -----

    // Test test(3);          // ERROR: no template argument (before C++17 CTAD)
    Test<int> test(3);        // explicit template argument

    return 0;                 // end program
}
```

## Structured bindings
Structured bindings are a C++17 feature that let you unpack multiple values from an object into separate variables in one line. Think of it as a clean way to “destructure” things like pairs, tuples, arrays, or structs.

```cpp
#include <iostream>              // For std::cout
#include <tuple>                 // For std::tuple
#include <string>                // For std::string
#include <utility>               // For std::pair

using namespace std::literals;   // Enables "text"s string literal

// Define a struct for the struct example
struct Numbers {
    int x;                       // Integer member
    double y;                    // Double member
    std::string z;               // String member
};

int main()
{
    // =======================
    // 1. std::pair example
    // =======================

    std::pair pr(1, 3.142);      // Create a pair<int, double> with values (1, 3.142)

    auto [pi, pd] = pr;          // Structured binding: pi = 1, pd = 3.142

    std::cout << "[pair] ";      // Label output
    std::cout << "i = " << pi    // Print integer part
              << ", d = " << pd  // Print double part
              << '\n';           // New line

    // =======================
    // 2. struct example
    // =======================

    Numbers numbers{1, 2.0, "three"s}; // Initialize struct with values

    // Structured binding (C++17)
    auto [si, sd, ss] = numbers; // si=1, sd=2.0, ss="three"

    std::cout << "[struct] ";    // Label output
    std::cout << "i = " << si    // Print int
              << ", d = " << sd  // Print double
              << ", s = " << ss  // Print string
              << '\n';           // New line

    // =======================
    // 3. std::tuple example
    // =======================

    std::tuple t = std::make_tuple(1, 2.0, "three"s); // Create tuple<int, double, string>

    // Structured binding (C++17)
    auto [ti, td, ts] = t;      // ti=1, td=2.0, ts="three"

    std::cout << "[tuple] ";    // Label output
    std::cout << "i = " << ti   // Print int
              << ", d = " << td // Print double
              << ", s = " << ts // Print string
              << '\n';          // New line

    return 0;                   // End program successfully
}
```

## Structured bindings and maps
This C++ program demonstrates how to use std::map to store key–value pairs and compares older C++11/14 techniques with newer C++17 features. It defines two insert functions: one uses the traditional std::pair return from map::insert to check if insertion succeeded, while the other uses structured bindings (a C++17 feature) to unpack the result more cleanly. In main, a map is initialized with a few entries, then printed twice—first using the older loop style with .first and .second, and then using structured bindings for clearer syntax. Finally, both insert functions are tested with duplicate and new keys to show how the map prevents duplicate keys and how each version reports success or failure, illustrating both backward-compatible and modern C++ approaches.

```cpp
#include <iostream>              // For std::cout
#include <map>                   // For std::map container
#include <string>                // For std::string

using namespace std::literals;   // Enables "text"s string literal

// ----------- C++11/14 INSERT FUNCTION -----------
void cpp14_insert(std::map<int, std::string>& m, int new_key, std::string new_val) {
    // Insert returns pair<iterator, bool>
    auto pr = m.insert({new_key, new_val});  // Try inserting key-value pair

    if (pr.second)                           // Check if insertion succeeded
        std::cout << "Inserted a new element\n";  // Success message
    else {
        auto el = pr.first;                  // Iterator to existing element
        std::cout << "Insert failed ";       // Failure message
        std::cout << "due to an element with key: " << el->first
                  << " and value: " << el->second << '\n'; // Show conflicting element
    }
}

// ----------- C++17 INSERT FUNCTION (STRUCTURED BINDINGS) -----------
void cpp17_insert(std::map<int, std::string>& m, int new_key, std::string new_val) {
    auto [iter, success] = m.insert({new_key, new_val}); // Structured binding

    if (success)                                         // Check success
        std::cout << "Inserted a new element\n";          // Success message
    else {
        auto [key, value] = *iter;                       // Unpack iterator result
        std::cout << "Insert failed ";                   // Failure message
        std::cout << "due to an element with key: " << key
                  << " and value: " << value << '\n';    // Show conflicting element
    }
}

// ----------- MAIN FUNCTION -----------
int main() {
    // Create a map with initial elements
    std::map<int, std::string> m = {
        {1, "Hello"s},
        {2, "How are you?"s},
        {3, "Goodbye"s}
    };

    // ----------- LOOP EXAMPLE C++11/14 -----------
    std::cout << "Map elements (C++11/14):\n";  // Header output
    for (auto el : m)                           // Iterate through map
        std::cout << "Key = " << el.first       // Access key
                  << ", Value = " << el.second  // Access value
                  << '\n';                      // New line

    // ----------- LOOP EXAMPLE C++17 -----------
    std::cout << "Map elements (C++17):\n";     // Header output
    for (auto [key, value] : m)                 // Structured binding unpack
        std::cout << "Key = " << key            // Print key
                  << ", Value = " << value      // Print value
                  << '\n';                      // New line

    // ----------- INSERT TESTS -----------
    std::cout << "\nTesting insert (C++11/14):\n"; // Section header
    cpp14_insert(m, 1, "Hello again"s);            // Duplicate key (fail)
    cpp14_insert(m, 4, "New value"s);              // New key (success)

    std::cout << "\nTesting insert (C++17):\n";    // Section header
    cpp17_insert(m, 2, "Duplicate"s);              // Duplicate key (fail)
    cpp17_insert(m, 5, "Another value"s);          // New key (success)

    return 0;                                      // End program
}
```

## If statements
This merged C++17 program demonstrates how modern language features make code more concise and safer by limiting variable scope and improving readability: instead of declaring variables before an if, C++17 allows you to initialize them directly inside the if statement (e.g., iterators or search results), ensuring they only exist where needed; when working with containers like std::map, the program shows how insertion returns both an iterator and a success flag, which can be unpacked using structured bindings (auto [iter, success]) for clearer logic; it also compares older C++14 patterns with newer C++17 approaches for tasks like searching in strings, highlighting that the newer style reduces clutter while keeping checks (like avoiding invalid iterators or missing values) explicit and safe, ultimately leading to cleaner, more maintainable code.

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std::literals;

// ------------------------------------------------------------
// Example 1: Demonstrating C++17 if-initializer with iterators
// ------------------------------------------------------------
void vector_example()
{
    std::vector<int> vec = {1, 2, 3};

    // C++17 feature:
    // Declare and initialize 'iter' inside the if-statement.
    // Scope of 'iter' is limited to this if block.
    if (auto iter = vec.begin(); iter != vec.end()) {
        // We safely dereference because we already checked it's not end()
        std::cout << "First element of vec: " << *iter << '\n';
    }
}


// ------------------------------------------------------------
// Example 2: Inserting into a map and checking success
// ------------------------------------------------------------
void map_insert_example()
{
    std::map<int, std::string> m = { {1, "Hello"s} };

    // insert() returns a pair:
    // - iterator to element
    // - bool indicating success of insertion
    if (auto result = m.insert({2, "How are you?"s}); result.second) {
        std::cout << "Insertion successful\n";
    } else {
        std::cout << "Insertion failed (key already exists)\n";
    }
}


// ------------------------------------------------------------
// Example 3: Structured bindings (C++17)
// ------------------------------------------------------------
void map_insert_binding_example()
{
    std::map<int, std::string> m = { {1, "hello"s} };

    // Structured binding splits the returned pair into:
    // iter  -> iterator to element
    // success -> bool indicating insertion success
    if (auto [iter, success] = m.insert({1, "goodbye"s}); success) {
        std::cout << "Inserted new element\n";
    } else {
        std::cout << "Insert failed (duplicate key)\n";

        // Access existing element via iterator
        auto [key, value] = *iter;
        std::cout << "Existing -> Key: " << key
                  << ", Value: " << value << '\n';
    }

    // Range-based loop with structured bindings
    std::cout << "All map elements:\n";
    for (auto [key, value] : m) {
        std::cout << key << " => " << value << '\n';
    }
}


// ------------------------------------------------------------
// Example 4: Searching characters in a string
// ------------------------------------------------------------

// C++14 style (separate variable + if)
void find_cpp14(const std::string& str, char c)
{
    auto pos = str.find(c);  // find position of character

    if (pos != std::string::npos) {
        std::cout << "Found '" << c << "' at index " << pos << '\n';
    } else {
        std::cout << "Character '" << c << "' not found\n";
    }
}


// C++17 style (if with initializer)
void find_cpp17(const std::string& str, char c)
{
    // 'pos' exists only inside this if statement
    if (auto pos = str.find(c); pos != std::string::npos) {
        std::cout << "Found '" << c << "' at index " << pos << '\n';
    } else {
        std::cout << "Character '" << c << "' not found\n";
    }
}


// ------------------------------------------------------------
// Main function to run all examples
// ------------------------------------------------------------
int main()
{
    std::cout << "=== Vector Example ===\n";
    vector_example();

    std::cout << "\n=== Map Insert Example ===\n";
    map_insert_example();

    std::cout << "\n=== Map Structured Binding Example ===\n";
    map_insert_binding_example();

    std::cout << "\n=== String Search (C++14 vs C++17) ===\n";
    std::string text = "Hello";
    find_cpp14(text, 'l');
    find_cpp17(text, 'o');

    return 0;
}
```
