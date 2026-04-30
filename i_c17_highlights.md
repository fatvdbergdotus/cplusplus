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
