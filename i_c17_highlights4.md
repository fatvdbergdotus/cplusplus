# C++ 17 highlights

## Map instertion
```cpp
#include <iostream>   // For input/output (std::cout)
#include <map>        // For std::map container
#include <string>     // For std::string

int main() {
    std::map<std::string, int> scores;  // Create a map storing (name -> score)

    // ============================================================
    // 1. Using insert (classic approach, pre-C++17)
    // ============================================================

    auto res_insert = scores.insert(std::make_pair("Graham", 66)); 
    // Try to insert ("Graham", 66) into the map
    // Returns pair<iterator, bool>
    // - iterator: points to element with key "Graham"
    // - bool: true if inserted, false if key already existed

    auto iter_insert = res_insert.first;  // Extract iterator to element

    if (res_insert.second) {  // If insertion succeeded
        std::cout << "[insert] Inserted new element: "
                  << iter_insert->first << " -> " << iter_insert->second << '\n';
    } else {  // If key already existed
        std::cout << "[insert] Key exists, updating value manually\n";
        iter_insert->second = 66;  // Manually update value
    }

    // ============================================================
    // 2. Using insert_or_assign (C++17)
    // ============================================================

    auto res_assign = scores.insert_or_assign("Graham", 77);
    // If key does NOT exist → insert
    // If key exists → overwrite value
    // Returns pair<iterator, bool> (same structure as insert)

    auto iter_assign = res_assign.first;  // Get iterator

    if (res_assign.second) {  // True if inserted
        std::cout << "[insert_or_assign] Inserted: "
                  << iter_assign->first << " -> " << iter_assign->second << '\n';
    } else {  // False if assigned (updated)
        std::cout << "[insert_or_assign] Modified: "
                  << iter_assign->first << " -> " << iter_assign->second << '\n';
    }

    // ============================================================
    // 3. Using structured bindings (C++17 modern syntax)
    // ============================================================

    if (auto [element, inserted] = scores.insert_or_assign("Graham", 88); inserted) {
        // element = iterator
        // inserted = bool
        std::cout << "[structured binding] Inserted: "
                  << element->first << " -> " << element->second << '\n';
    } else {
        std::cout << "[structured binding] Modified: "
                  << element->first << " -> " << element->second << '\n';
    }

    return 0;  // Program finished successfully
}
```

## Map emplace
```cpp
#include <iostream>   // For std::cout
#include <map>        // For std::map
#include <string>     // For std::string

// A simple class to demonstrate object construction behavior
class refrigerator {
    int temperature;   // Stores temperature
    bool door_open;    // Indicates if door is open
    bool power_on;     // Indicates if power is on

public:
    // Constructor
    refrigerator(int temp, bool open, bool power)
        : temperature(temp), door_open(open), power_on(power)
    {
        std::cout << "Constructor called\n"; // Prints when object is constructed
    }

    // Copy constructor
    refrigerator(const refrigerator& other)
        : temperature(other.temperature),
          door_open(other.door_open),
          power_on(other.power_on)
    {
        std::cout << "Copy constructor called\n"; // Prints when object is copied
    }

    // Function to print object state
    void print() const {
        std::cout << "Temp: " << temperature
                  << ", Door: " << (door_open ? "Open" : "Closed")
                  << ", Power: " << (power_on ? "On" : "Off") << "\n";
    }
};

int main() {
    // Create a map with string keys and refrigerator values
    std::map<std::string, refrigerator> fridge_map;

    std::cout << "=== Using emplace ===\n";

    // emplace constructs the object before inserting
    fridge_map.emplace(
        "kitchen",                      // Key
        refrigerator(5, false, true)   // Value (temporary object created first)
    );

    // If key already exists, emplace still constructs the object first
    fridge_map.emplace(
        "kitchen",                      // Same key (already exists)
        refrigerator(10, true, false)  // Still constructs object (wasted work)
    );

    std::cout << "\n=== Using try_emplace ===\n";

    // try_emplace constructs ONLY if key does not exist
    fridge_map.try_emplace(
        "garage",   // New key
        2, true, true // Arguments forwarded to constructor (no temporary object)
    );

    // If key exists, try_emplace does NOT construct the object
    fridge_map.try_emplace(
        "garage",   // Existing key
        8, false, false // Constructor NOT called here
    );

    std::cout << "\n=== Final Map Contents ===\n";

    // Iterate through map and print contents
    for (const auto& pair : fridge_map) {
        std::cout << pair.first << " -> "; // Print key
        pair.second.print();               // Print value
    }

    return 0; // End of program
}
```

## Constexpr if statement (simple)
std::is_integral<T> is a compile-time type trait from the C++ standard library (in <type_traits>) that checks whether a given type T is an integral (whole-number) type, such as int, char, bool, or long; it provides the result as a constant boolean value via std::is_integral<T>::value (or the cleaner std::is_integral_v<T> in C++17+), which is commonly used in templates and if constexpr to enable or restrict code paths based on whether a type belongs to the family of integer types, while excluding non-integral types like float, double, classes, or pointers.

```cpp
#include <iostream>
#include <type_traits>

// Function template that behaves differently depending on type
template <typename T>
void printType(T value)
{
    if constexpr (std::is_integral<T>::value)
    {
        std::cout << "Integer: " << value << '\n';
    }
    else
    {
        std::cout << "Not an integer: " << value << '\n';
    }
}

int main()
{
    printType(10);        // Integer
    printType(3.14);      // Not an integer
    printType("hello");   // Not an integer
}
```

## Constexpr if statement
std::is_same_v<T, U> is a C++17 compile-time utility from <type_traits> that evaluates to true if the two types T and U are exactly identical and false otherwise; it’s a shorthand for std::is_same<T, U>::value and is commonly used in templates to make decisions during compilation, especially with if constexpr, enabling different code paths depending on the type while avoiding compilation errors that would occur with a normal if.

```cpp
#include <iostream>     // For std::cout
#include <string>       // For std::string
#include <type_traits>  // For std::is_same_v and std::enable_if_t

// ============================================================
// 1. Regular if (THIS WILL NOT COMPILE FOR ALL TYPES)
// ============================================================

namespace regular_if
{
    template<typename T>
    std::string get_string(const T& arg)  // Generic function
    {
        // Normal if (evaluated at runtime, both branches must compile)
        if (std::is_same_v<std::string, T>)   // Check if T is std::string
            return arg;                       // ERROR if T is not string
        else
            return std::to_string(arg);       // ERROR if T is string
    }
}

// ============================================================
// 2. if constexpr (C++17 solution)
// ============================================================

namespace constexpr_if
{
    template<typename T>
    std::string get_string(const T& arg)  // Generic function
    {
        // Compile-time if (only one branch is compiled)
        if constexpr (std::is_same_v<std::string, T>)  // True if T == std::string
            return arg;                                // Only compiled for string
        else
            return std::to_string(arg);                // Only compiled otherwise
    }
}

// ============================================================
// 3. SFINAE (Substitution Failure Is Not An Error)
// ============================================================

namespace sfinae
{
    // Enabled ONLY when T is NOT std::string
    template<typename T, std::enable_if_t<!std::is_same_v<std::string, T>, int> = 0>
    std::string get_string(const T& arg)   // Handles non-string types
    {
        return std::to_string(arg);        // Convert numeric types to string
    }

    // Enabled ONLY when T IS std::string
    template<typename T, std::enable_if_t<std::is_same_v<std::string, T>, int> = 0>
    std::string get_string(const T& arg)   // Handles std::string
    {
        return arg;                        // Return string directly
    }
}

// ============================================================
// 4. Template Specialization
// ============================================================

namespace specialization
{
    // General template (for non-string types)
    template<typename T>
    std::string get_string(const T& arg)
    {
        return std::to_string(arg);  // Convert to string
    }

    // Specialization for std::string
    template<>
    std::string get_string<std::string>(const std::string& arg)
    {
        return arg;  // Return string directly
    }
}

// ============================================================
// MAIN FUNCTION (demonstrates all methods)
// ============================================================

int main()
{
    int x{42};                          // Example integer
    std::string str{"hello"};           // Example string

    std::cout << "===== if constexpr =====\n";  // Section header
    std::cout << constexpr_if::get_string(x) << '\n';    // Works for int
    std::cout << constexpr_if::get_string(str) << '\n';  // Works for string

    std::cout << "\n===== SFINAE =====\n";       // Section header
    std::cout << sfinae::get_string(x) << '\n';   // Works for int
    std::cout << sfinae::get_string(str) << '\n'; // Works for string

    std::cout << "\n===== Specialization =====\n"; // Section header
    std::cout << specialization::get_string(x) << '\n';   // Works for int
    std::cout << specialization::get_string(str) << '\n'; // Works for string

    // NOTE:
    // regular_if version is NOT called because it would fail to compile
    // Uncommenting below will likely cause compilation errors:
    /*
    std::cout << regular_if::get_string(x) << '\n';
    std::cout << regular_if::get_string(str) << '\n';
    */

    return 0;  // Program finished successfully
}
```

## Constexpr if statement (fibonacci)
```cpp
// ===================== Example 1: constexpr Fibonacci (compile-time recursion) =====================
#include <iostream>

// Template-based Fibonacci computed at compile time using constexpr and if constexpr
template<int N>
constexpr int fibonacci_constexpr()
{
    // if constexpr ensures only the valid branch is compiled
    if constexpr (N > 1)
        // Recursive compile-time evaluation
        return fibonacci_constexpr<N-1>() + fibonacci_constexpr<N-2>();

    // Base cases: fibonacci(0) = 0, fibonacci(1) = 1
    return N;
}

void run_constexpr_example()
{
    constexpr int n{10};  // evaluated at compile time
    std::cout << "[constexpr] Fibonacci(" << n << ") = "
              << fibonacci_constexpr<n>() << '\n';
}


// ===================== Example 2: Template Specialization Fibonacci =====================
#include <iostream>

// General case: recursive template instantiation
template <int N>
int fibonacci_specialized()
{
    return fibonacci_specialized<N-1>() + fibonacci_specialized<N-2>();
}

// Base case specialization: stops recursion at N = 1
template<>
int fibonacci_specialized<1>()
{
    return 1;
}

// Base case specialization: stops recursion at N = 0
template<>
int fibonacci_specialized<0>()
{
    return 0;
}

void run_specialization_example()
{
    constexpr int n{10};
    std::cout << "[specialization] Fibonacci(" << n << ") = "
              << fibonacci_specialized<n>() << '\n';
}


// ===================== Example 3: Nested if constexpr =====================
#include <string>
#include <limits>
#include <type_traits>

// Demonstrates safe compile-time branching with nested if constexpr
template <typename T>
constexpr void func_nested()
{
    // First check: is T an integral type?
    if constexpr (std::is_integral<T>::value)
    {
        // Second check: does T have a large range (greater than 255)?
        if constexpr (std::numeric_limits<T>::max() > 255)
        {
            std::cout << "[nested] Large integral type\n";
        }
        else
        {
            std::cout << "[nested] Small integral type\n";
        }
    }
    else
    {
        // This branch is compiled instead for non-integral types
        std::cout << "[nested] Not an integral type\n";
    }
}

void run_nested_example()
{
    func_nested<int>();        // integral, large
    func_nested<bool>();       // integral, small
    func_nested<std::string>(); // not integral (safe!)
}


// ===================== Example 4: Short-circuit pitfall =====================

// Demonstrates why combining conditions in a single if constexpr can be dangerous
template <typename T>
constexpr void func_short_circuit()
{
    // Problem:
    // Even though this looks like a short-circuit condition,
    // BOTH sides must still be valid during compilation.
    // std::numeric_limits<T> must exist, or compilation fails.
    if constexpr (std::is_integral<T>::value &&
                  std::numeric_limits<T>::max() > 255)
    {
        std::cout << "[short-circuit] Large integral type\n";
    }
}

void run_short_circuit_example()
{
    func_short_circuit<int>(); // OK

    // This would FAIL to compile if uncommented:
    // func_short_circuit<std::string>();
    //
    // Reason:
    // std::numeric_limits<std::string> is invalid,
    // and template substitution fails BEFORE condition evaluation.
}


// ===================== Unified main =====================

int main()
{
    run_constexpr_example();
    run_specialization_example();
    run_nested_example();
    run_short_circuit_example();

    return 0;
}
```
