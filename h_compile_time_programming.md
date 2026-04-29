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
