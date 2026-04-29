(c) 2026 Freek van den Berg. All rights reserved.

# Compile time programming

## Variadic Templates
```cpp
#include <iostream>   // for std::cout, std::ostream
#include <string>     // for std::string
#include <tuple>      // for std::tuple, std::make_tuple

using namespace std;  // avoid writing std:: everywhere (for simplicity)


// =========================
// SECTION 1: EXPAND EXAMPLE
// =========================

// Variadic template function (accepts any number of arguments)
template <typename... Args>                     // Args = parameter pack (types)
void expand_func(Args... args) {                // args = parameter pack (values)
    auto arg_tuple = make_tuple(args...);       // pack all arguments into a tuple
}


// =========================
// SECTION 2: PRINT EXAMPLE
// =========================

// Base case (non-variadic) - stops recursion
template <typename T>
ostream& print(ostream& os, const T& t) {
    return os << t;                             // print last element
}

// Recursive variadic function
template <typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args&... args) {
    os << t << ", ";                            // print current element
    return print(os, args...);                  // recursive call with remaining args
}


// =========================
// SECTION 3: PROCESS EXAMPLE
// =========================

// Base case (single argument)
template <typename T>
void process_func(T t) {
    cout << "Non-variadic template\n";          // indicates recursion end
    cout << "Processing argument " << t << endl;
}

// Variadic version
template <typename T, typename... Args>
void process_func(T t, Args... args) {
    size_t n_args = sizeof...(args) + 1;        // count total arguments
    cout << "Variadic template: compiler deduced "
         << n_args << " argument(s)\n";
    cout << "Processing argument " << t << endl;

    process_func(args...);                      // recursive call with remaining args
}


// =========================
// SECTION 4: SIZEOF EXAMPLE
// =========================

// Variadic template showing sizeof...
template <typename... Args>
void sizeof_func(Args... args) {
    cout << "Compiler deduced call with "
         << sizeof...(args)                    // number of arguments
         << " argument(s)\n";
}


// =========================
// MAIN FUNCTION
// =========================

int main() {

    int i{42};                                 // integer variable
    double d{0.0};                             // double variable
    string s{"text"};                           // string variable


    // ---- EXPAND EXAMPLE ----
    expand_func(s);                             // single argument
    expand_func(i, d, s);                       // multiple arguments


    cout << "\n--- PRINT EXAMPLE ---\n";
    print(cout, 2, 4.6, "Hello") << endl;       // prints all values


    cout << "\n--- PROCESS EXAMPLE ---\n";
    process_func(s);                            // single argument
    process_func(i, d, s);                      // multiple arguments


    cout << "\n--- SIZEOF EXAMPLE ---\n";
    sizeof_func(s);                             // 1 argument
    sizeof_func(i, d, s);                       // 3 arguments


    return 0;                                   // program ends successfully
}
```

## Various Template Functions
```cpp
// ==============================
// Combined single C++ file
// Merged from misc_template_features
// ==============================

#include <iostream>          // for std::cout
#include <typeinfo>          // for typeid
#include <cassert>           // for static_assert alternative

// ==============================
// extern_template.h (merged)
// ==============================

// Template declaration for a generic function
template <typename T>
void func(T value); // declaration only

// Explicit extern template declarations (avoid multiple instantiations)
extern template void func<int>(int);     // tell compiler: defined elsewhere
extern template void func<double>(double);

// ==============================
// extern_template_impls.cc (merged)
// ==============================

// Actual template definition
template <typename T>
void func(T value) {                     // define template
    std::cout << "Value: " << value      // print value
              << " type: "               // print type label
              << typeid(T).name()       // runtime type info
              << std::endl;             // newline
}

// Explicit instantiations (force generation here)
template void func<int>(int);            // generate int version
template void func<double>(double);     // generate double version

// ==============================
// extern_template1.cc (merged)
// ==============================

void use_func_int() {                   // function using int specialization
    func<int>(42);                     // call template with int
}

// ==============================
// extern_template2.cc (merged)
// ==============================

void use_func_double() {               // function using double specialization
    func<double>(3.14);                // call template with double
}

// ==============================
// extern_int1.cc (merged)
// ==============================

// Declare external integer
extern int shared_int;                 // defined elsewhere

void increment_int() {                 // function increments shared int
    shared_int++;                     // increase value
}

// ==============================
// extern_int2.cc (merged)
// ==============================

void print_int() {                     // function prints shared int
    std::cout << "shared_int = "      // label
              << shared_int           // value
              << std::endl;           // newline
}

// ==============================
// extern_int_impls.cc (merged)
// ==============================

// Define the shared integer
int shared_int = 0;                   // initialize global variable

// ==============================
// static_assert.cc (merged)
// ==============================

// Compile-time assertion example
static_assert(sizeof(int) >= 4,       // check int size
              "int must be at least 4 bytes"); // error message

// ==============================
// Main function (added)
// ==============================

int main() {                          // program entry point

    // --- Test extern template ---
    use_func_int();                   // call int version
    use_func_double();                // call double version

    // --- Test extern int ---
    print_int();                      // print initial value
    increment_int();                  // increment
    print_int();                      // print updated value

    return 0;                         // successful exit
}
```
