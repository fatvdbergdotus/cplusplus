# C++ 17 highlights

## Switch statements
The example shows how a C++17 switch statement with an initializer can be used to process characters in a string while keeping variables scoped neatly. The program loops through each character of a C-style string and, inside the switch, declares a temporary variable c (const char c = arr[i]) that exists only for that switch. It then checks whether c is a whitespace character (space ' ', tab '\t', or newline '\n'); if so, it increments a counter. Each case falls into the same action (incrementing), and break prevents unintended fallthrough. This approach keeps the code clean by avoiding extra variables outside the switch while clearly grouping conditions that share the same behavior.

```cpp
#include <iostream>      // for std::cout
#include <string>        // for std::string
#include <utility>       // for std::pair

using namespace std::literals; // enables "text"s string literal

// -------------------------
// Example 1: Basic switch with initializer
// -------------------------
void example_basic_switch() {
    int ws_count{0}; // counter for whitespace characters

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 1: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // loop until null terminator
        switch (const char c = arr[i]; c) { // C++17 switch initializer
            case ' ':      // if character is space
            case '\t':     // or tab
            case '\n':     // or newline
                ++ws_count; // increment counter
                break;      // exit switch
            default:       // any other character
                break;      // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n\n"; // print result
}

// -------------------------
// Example 2: Structured binding in switch
// -------------------------

// enum to represent result states
enum class Result { SUCCEEDED, TIMED_OUT, FAILED };

// function returning a pair (data + result)
auto fetch() {
    return std::pair{"abcdef"s, Result::SUCCEEDED}; // sample data
}

void example_structured_binding() {
    std::cout << "Example 2:\n"; // header

    // structured binding inside switch (C++17 feature)
    switch (auto [data, result] = fetch(); result) {
        case Result::SUCCEEDED: // success case
            std::cout << "Fetched data: " << data << '\n'; // print data
            break;
        case Result::TIMED_OUT: // timeout case
            std::cout << "The operation timed out\n";
            break;
        case Result::FAILED:    // failure case
            std::cout << "The operation failed\n";
            break;
    }

    std::cout << "\n"; // spacing
}

// -------------------------
// Example 3: Fallthrough attribute
// -------------------------
void example_fallthrough() {
    int ws_count{0}; // counter for whitespace

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 3: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // iterate characters
        switch (const char c = arr[i]; c) { // switch with initializer
            case ' ':              // space
                [[fallthrough]];  // intentional fallthrough
            case '\t':             // tab
                [[fallthrough]];  // intentional fallthrough
            case '\n':             // newline
                ++ws_count;       // count whitespace
                break;            // exit switch
            default:              // not whitespace
                break;            // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n"; // output result
}

// -------------------------
// Main function
// -------------------------
int main() {
    example_basic_switch();        // run first example
    example_structured_binding();  // run second example
    example_fallthrough();         // run third example

    return 0; // end program
}
```

## Copy elision
```cpp
#include <iostream>                 // Include input-output stream library for std::cout

class Test {                       // Define a class named Test
  public:
    Test() {                       // Default constructor
        std::cout << "Default constructor\n"; // Print when object is created
    }
    
    // Copy constructor with side effect
    Test(const Test& other) {      // Copy constructor (called when copying objects)
        std::cout << "Copying\n";  // Print when a copy happens
    }
};

// Function returning a temporary object
Test func()                        // Function that returns a Test object
{
    return Test{};                 // Return a temporary Test object (prvalue)
}

int main()                         // Entry point of the program
{
    std::cout << "Calling func()\n"; // Print before calling func()
    
    // How many times is "Copying" printed out?
    Test test = func();            // Initialize 'test' with return value of func()
                                   // In C++17, copy elision is guaranteed here
                                   // So NO copy constructor is called
    
    std::cout << "Returned from func()\n"; // Print after func() completes
}
```

## Converting Strings to Numbers
```cpp
#include <iostream>      // For std::cout
#include <charconv>      // For std::from_chars
#include <string>        // For std::string
#include <system_error>  // For std::errc

// Function demonstrating error handling with from_chars
void convert(const std::string& str) // Takes a string to convert
{
    std::cout << "str: " << str << '\n'; // Print input string

    const char* const first = str.data();              // Pointer to beginning of string
    const char* const last  = first + str.size();      // Pointer to end of string

    int number{0}; // Variable to store parsed integer

    auto res = std::from_chars(first, last, number); // Attempt conversion

    if (res.ptr != last) // If parsing didn’t consume entire string
        std::cout << "Error caused by character " << *(res.ptr) << '\n';

    std::cout << "Parsed " << res.ptr - first << " chars\n"; // Show how many chars parsed

    if (res.ec == std::errc::result_out_of_range) // If number too large/small
        std::cout << "result_out_of_range: " << number << "\n";
    else if (res.ec == std::errc::invalid_argument) // If no valid conversion possible
        std::cout << "invalid_argument\n";
    else
        std::cout << "Result: " << number << '\n'; // Successful result

    std::cout << '\n'; // Blank line for readability
}

int main()
{
    // ---------------------------
    // Example 1: Integer parsing
    // ---------------------------

    std::string str1{"100"}; // String containing integer
    std::cout << "str1: " << str1 << '\n';

    int number1{0}; // Variable to store result

    // Convert string to integer (base 10 by default)
    auto res1 = std::from_chars(str1.data(), str1.data() + str1.size(), number1);

    std::cout << "number1: " << number1 << '\n';

    // Convert using base 16 (hexadecimal)
    res1 = std::from_chars(str1.data(), str1.data() + str1.size(), number1, 16);

    std::cout << "number1 (base 16): " << number1 << "\n\n";


    // ---------------------------
    // Example 2: Floating parsing
    // ---------------------------

    std::string str2{"3.14159"}; // String containing floating-point number
    std::cout << "str2: " << str2 << '\n';

    double number2{0.0}; // Variable to store double

    // Specify format for floating-point parsing
    auto format = std::chars_format::general;

    // Convert string to double
    auto res2 = std::from_chars(str2.data(), str2.data() + str2.size(), number2, format);

    std::cout << "number2: " << number2 << "\n\n";


    // ---------------------------
    // Example 3: Error handling
    // ---------------------------

    convert("3875");       // Valid number
    convert("387err5");    // Stops at invalid character
    convert("Oops");       // Completely invalid input

    return 0; // End of program
}
```

## Converting Numbers to Strings
```cpp
#include <iostream>      // for std::cout
#include <charconv>      // for std::to_chars
#include <system_error>  // for std::errc
#include <string>        // for std::string

// Function to test conversion of double values to string
void test(double dbl)                      // define a function that takes a double
{
    const int size{100};                   // buffer size for conversion
    char buf[size];                        // character buffer to hold result

    auto res = std::to_chars(buf, buf + size, dbl); // convert double to char array

    // Check if conversion failed due to insufficient buffer size
    if (res.ec == std::errc::value_too_large) // error condition
        std::cout << "value_too_large\n";     // print error message
    else {
        *(res.ptr) = '\0';                   // add null terminator to make it C-string
        std::cout << "Result: " << buf << '\n'; // print converted result
    }
}

int main()                                  // main entry point
{
    // -------- Integer conversion example --------
    int number{42};                         // integer to convert
    const int size{100};                    // buffer size
    char buf[size];                         // buffer for integer conversion

    auto res = std::to_chars(buf, buf + size, number); // convert int to chars

    *(res.ptr) = '\0';                      // add null terminator
    std::cout << "Integer Result (C-string): " << buf << '\n'; // print raw buffer

    std::string result(buf, res.ptr - buf); // construct std::string from buffer
    std::cout << "Integer Result (std::string): " << result << "\n"; // print string

    // -------- Double conversion examples --------
    test(3.14159);                          // test with a normal double

    test(1.23456789012345678901234567890123456789012345678901234567890L);
    // test with a very large precision number (may be truncated)

    return 0;                               // indicate successful execution
}
```

## String view
std::string_view is a lightweight, non-owning view of a string introduced in C++17 that lets you refer to existing character data (like a std::string, string literal, or char array) without copying it; internally, it just stores a pointer to the data and a length, making it fast and efficient for read-only operations such as passing strings to functions or slicing substrings, but because it doesn’t own the memory, you must ensure the original data remains valid for as long as the string_view is used, otherwise you risk undefined behavior (dangling references).

```cpp
#include <iostream>
#include <string>        // for std::string
#include <string_view>   // for std::string_view

// -----------------------------
// Version 1: using std::string
// -----------------------------
// Takes a const reference to std::string
// This may create a temporary std::string when passing string literals
void greet_string(const std::string& person)
{
    std::cout << "[std::string] Hello, " << person << '\n';
}

// -----------------------------------
// Version 2: using std::string_view
// -----------------------------------
// Takes a std::string_view (non-owning view of a string)
// No allocation or copy when passing string literals
void greet_string_view(std::string_view person)
{
    std::cout << "[string_view] Hello, " << person << '\n';
}

int main()
{
    // -----------------------------
    // Calling std::string version
    // -----------------------------
    // "World" (const char*) is converted to a temporary std::string
    // This involves allocation + copy
    greet_string("World");

    // -----------------------------
    // Calling string_view version
    // -----------------------------
    // "World" is directly viewed (no allocation, no copy)
    // string_view just points to existing memory
    greet_string_view("World");

    // -----------------------------
    // Additional comparison example
    // -----------------------------
    std::string name = "Alice";

    // No extra allocation here (already a std::string)
    greet_string(name);

    // string_view simply references the existing string data
    greet_string_view(name);

    return 0;
}
```

## String view usage
```cpp
#include <iostream>        // For std::cout
#include <string>          // For std::string
#include <string_view>     // For std::string_view

using namespace std::literals; // Enables "sv" literal

// Function that takes a string_view (no copy, efficient)
void greet(std::string_view person) // Accepts many string types
{
    std::cout << "Hello, " << person << "\n"; // Print greeting
}

int main()
{
    // ===== 1. Basic string_view construction =====

    std::string_view sv1{"Hello"}; // From string literal
    std::cout << "sv1: " << sv1 << "\n"; // Print value
    greet(sv1); // Use greet with string_view

    std::string str{"World"}; // Create std::string
    std::string_view sv2{str}; // View into string
    std::cout << "sv2: " << sv2 << "\n"; // Print value
    greet(str);  // Pass std::string (auto converts)
    greet(sv2);  // Pass string_view directly

    const char arr[] = "C-style string"; // Char array
    std::string_view sv3(arr); // View from char array
    std::cout << "sv3: " << sv3 << "\n"; // Print value
    greet(arr); // Pass C-string

    // ===== 2. Using "sv" literal =====

    greet("Literal example"sv); // Direct string_view literal

    // ===== 3. string_view interface operations =====

    std::string_view sv{"Hello, World!"}; // Create string_view
    std::cout << "Original: " << sv << "\n"; // Print original
    greet(sv); // Greet before modification

    std::cout << "Removing 7 characters from front\n"; // Info
    sv.remove_prefix(7); // Remove "Hello, "
    std::cout << "Now: " << sv << "\n"; // Should be "World!"
    greet(sv); // Greet modified view

    std::cout << "Removing 1 character from back\n"; // Info
    sv.remove_suffix(1); // Remove '!'
    std::cout << "Now: " << sv << "\n"; // Should be "World"
    greet(sv); // Greet final view

    // ===== 4. Converting back to std::string =====

    std::string finalStr{sv.data(), sv.size()}; // Safe conversion
    std::cout << "finalStr: " << finalStr << "\n"; // Print result
    greet(finalStr); // Works with std::string too

    return 0; // End program
}
```

## String view caveats
```cpp
#include <iostream>         // For std::cout
#include <string>           // For std::string
#include <string_view>      // For std::string_view
#include <vector>           // For std::vector

using namespace std::literals; // Enables "text"s literal for std::string

// ---------- Example 1: Lifetime issues ----------
std::string func()                  // Function returning a std::string
{
    // Beware of short-string optimization (SSO)
    return std::string{"A string which contains many characters"}; // Returns temporary string
}

// ---------- Example 2: Class with std::string& ----------
class ref_member_string {
    std::string& str;               // Reference to std::string (must bind to existing object)
public:
    ref_member_string(std::string& str) : str(str) {} // Constructor binds reference
};

// ---------- Example 3: Class with std::string_view ----------
class ref_member_view {
    std::string_view str;           // Non-owning view of string data
public:
    ref_member_view(std::string_view str): str(str) {} // Stores view (no ownership)
    void print() { std::cout << str << '\n'; }          // Prints viewed string
};

int main()
{
    // ==============================
    // Example 1: Lifetime extension
    // ==============================
    const std::string& s = func();  // OK: const reference extends lifetime of temporary
    std::cout << s << '\n';         // Safe: string still alive

    // std::string_view sv = func(); // BAD: view refers to destroyed temporary
    // std::cout << sv << '\n';      // Undefined behavior (dangling reference)

    // ==============================
    // Example 2: std::string reference member
    // ==============================
    std::string str{"test"};        // Create actual string object
    ref_member_string rm_ok(str);   // OK: binds to existing variable

    // ref_member_string rm_bad("test"s); // ERROR: temporary cannot bind to non-const reference

    // ==============================
    // Example 3: std::string_view member
    // ==============================
    ref_member_view rm_view{"Long string to initialize the class"s}; // Temporary string used
    rm_view.print();               // Works (but risky if temporary destroyed too early)

    // ==============================
    // Example 4: vector of string_view
    // ==============================
    std::vector<std::string_view> words; // Vector storing string views (non-owning)

    words.push_back("What are words worth?"s); // Temporary std::string created

    // WARNING:
    // After this line, the temporary string is destroyed,
    // so the string_view inside the vector becomes dangling!

    for (auto word : words)        // Iterate through vector
        std::cout << word << '\n'; // Undefined behavior (dangling view)

    return 0;                      // End of program
}
```
