# C++ 17 Highlights

## Variant type
std::variant in C++ is a type-safe container that can hold exactly one value out of a fixed set of types, acting like a safer replacement for a traditional union by keeping track of which type is currently active; for example, std::variant<int, double, std::string> can store either an int, double, or string, and when you assign a new value it automatically switches to that type while discarding the old one, and you can safely access the stored value using tools like std::get (which throws if the type is wrong), std::get_if (which returns a pointer or nullptr), or std::holds_alternative (which checks the active type), making it useful when a variable can represent multiple known types without risking undefined behavior.

```cpp
#include <iostream>   // Provides std::cout for output
#include <variant>    // Provides std::variant (type-safe union)
#include <string>     // Provides std::string
#include <cmath>      // (not strictly needed here, but safe if extended)

using namespace std::literals;  // Enables "hello"s string literal

// ================= assign.cc =================
void example_assign() {
    std::variant<char, int, double> var;  
    // Variant can hold either char, int, or double
    // Default initializes first type → char = '\0'

    var = 3.1;  
    // Assigning a double switches active type to double

    // var = "abc"s;  
    // Error: std::string is not one of the allowed types
}

// ================= get.cc =================
void example_get() {
    std::variant<char, int, double> var;
    var = 3.1;  // Active type is now double

    try {
        std::cout << "get by type<double>: "
                  << std::get<double>(var) << '\n';
        // Safely retrieves the double value

        std::cout << "get by index<2>: "
                  << std::get<2>(var) << '\n';
        // Index 2 corresponds to double (0=char,1=int,2=double)

        std::cout << "get by type<int>: "
                  << std::get<int>(var) << '\n';
        // Throws exception: wrong active type

    } catch (std::bad_variant_access& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
        // Handles incorrect type access
    }
}

// ================= get_if.cc =================
void example_get_if() {
    std::variant<char, int, double> var;
    var = 3.1;  // Activate double

    std::cout << "get_if() by type<double>: ";

    if (auto ptr = std::get_if<double>(&var); ptr)
        std::cout << *ptr << '\n';
    // Returns pointer if correct type, otherwise nullptr

    std::cout << "get_if() by index<2>: ";

    if (auto ptr = std::get_if<2>(&var); ptr)
        std::cout << *ptr << '\n';

    std::cout << "get_if() by type<int>: ";

    if (auto ptr = std::get_if<int>(&var); ptr)
        std::cout << *ptr << '\n';
    else
        std::cout << "int alternative is not in use\n";
    // Safe alternative to std::get (no exception)
}

// ================= holds_alternative.cc =================
void example_holds_alternative() {
    std::variant<char, int, double> var;
    var = 3.1;  // Activate double

    if (std::holds_alternative<int>(var))
        std::cout << std::get<int>(var) << '\n';
    else
        std::cout << "Int alternative is not in use\n";
    // Checks active type before accessing

    auto idx = var.index();
    std::cout << "Alternative in use has index: " << idx << '\n';
    // Returns index of currently active type
}

// ================= variant.cc =================
void example_variant_basics() {
    std::variant<std::string, int> vsi;
    // Default initializes first type → empty string

    std::variant<int, std::string> vis;
    // Default initializes first type → int = 0

    std::variant<std::string, int> v1{"hello"s};
    // Chooses std::string alternative

    std::variant<std::string, int> v2{42};
    // Chooses int alternative

    // std::variant<std::string, std::string> v{"hello"s};
    // Error: ambiguous type (same type appears twice)
}

// ================= main =================
int main() {
    example_assign();
    example_get();
    example_get_if();
    example_holds_alternative();
    example_variant_basics();

    return 0;  // Program finished successfully
}
```

## Variant Type Applications
This program demonstrates how to use std::variant as a type-safe way to store different data types in a single container. It defines a TokenVisitor struct with overloaded operator() functions, each handling a specific type (char, int, or double) and printing a corresponding message. In main, a Token alias is created for a variant that can hold those three types, and a std::vector is initialized with mixed values. The program then loops through each element and uses std::visit to automatically call the correct visitor function based on the actual type stored in the variant, demonstrating runtime polymorphism without inheritance.

```cpp
#include <iostream>   // For std::cout (console output)
#include <variant>    // For std::variant (type-safe union)
#include <vector>     // For std::vector (dynamic array)

// Visitor struct to handle different types inside std::variant
struct TokenVisitor {
    // Called when the variant holds a char
    void operator()(const char c) { 
        std::cout << "Character: " << c << '\n'; 
    }

    // Called when the variant holds an int
    void operator()(const int i) { 
        std::cout << "Integer: " << i << '\n'; 
    }

    // Called when the variant holds a double
    void operator()(const double d) { 
        std::cout << "Floating-point: " << d << '\n'; 
    }
};

int main() {
    // Create an alias 'Token' for a variant that can hold char, int, or double
    using Token = std::variant<char, int, double>;

    // Create a vector of Token elements with mixed types
    std::vector<Token> tokens = {42, 3.14159, 'Z', 99};

    // Loop through each token in the vector
    for (auto token : tokens) {

        // std::visit applies the visitor to the currently held type in the variant
        // It calls the correct overload of operator() based on the stored type
        std::visit(TokenVisitor(), token);
    }

    return 0; // Indicate successful program execution
}
```

## Optional Type
```cpp
#include <iostream>      // for input/output streams
#include <string>        // for std::string
#include <string_view>   // for std::string_view (non-owning string reference)
#include <charconv>      // for std::from_chars (fast string-to-int conversion)
#include <utility>       // for std::pair

// =========================
// VERSION 1: Using std::pair
// =========================

// Convert a string to an int using std::pair
// first  -> parsed integer
// second -> success flag
std::pair<int, bool> str2int_pair(std::string_view str)
{
    int x;  // variable to store parsed integer

    // Attempt to convert string to integer
    auto res = std::from_chars(str.data(), str.data() + str.size(), x);

    // Check if conversion succeeded (no error code)
    if (res.ec == std::errc{})         
        return std::pair(x, true);     // success

    return std::pair(x, false);        // failure
}


// =========================
// VERSION 2: Using pointer
// =========================

// Convert a string to int using pointer
// Returns pointer to int if successful, nullptr otherwise
int* str2int_pointer(std::string_view str)
{
    int x;  // variable to store parsed integer

    // Attempt conversion
    auto res = std::from_chars(str.data(), str.data() + str.size(), x);

    // If successful, allocate memory and return pointer
    if (res.ec == std::errc{})        
        return new int(x);             // dynamic allocation

    return nullptr;                   // failure case
}


// =========================
// MAIN FUNCTION
// =========================

int main()
{
    std::string str;  // user input string

    while (true) {  // infinite loop for repeated input
        std::cout << "Enter a number: ";
        std::cin >> str;

        // -------- Using std::pair version --------
        if (auto [num, success] = str2int_pair(str); success)
            std::cout << "[PAIR] Parsed number: " << num << '\n';
        else
            std::cout << "[PAIR] Invalid number\n";

        // -------- Using pointer version --------
        if (int* px = str2int_pointer(str); px) {  // check if pointer is not null
            std::cout << "[POINTER] Parsed number: " << *px << '\n';
            delete px;  // free allocated memory (IMPORTANT)
        }
        else {
            std::cout << "[POINTER] Invalid number\n";
        }

        std::cout << "------------------------\n";
    }

    return 0;  // program end (never reached due to loop)
}
```
