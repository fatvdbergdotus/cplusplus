(c) 2026 Freek van den Berg. All rights reserved.

# Modern C++ Libraries

## Random Numbers
```cpp
#include <random>
#include <iostream>

using namespace std;

int main() {
	mt19937 mt;                                      // Create engine instance

	cout << "Ten random integers between 0 and 100):" << endl;
	uniform_int_distribution<int> uid(0, 100);       // We want ints in the range 0 to 100

	for (int i = 0; i < 10; ++i) {
		cout << uid(mt) << ", ";                     // Get the next number in the sequence
	}

	cout << endl << endl << "Ten random doubles between 0.0 and 1.0):" << endl;
	uniform_real_distribution<double> did(0, 1);     // Doubles in the range 0 to 1

	for (int i = 0; i < 10; ++i) {                  // Get 10 random numbers
		cout << did(mt) << ", ";
	}
	cout << endl;
}
```

## Time

### Measure duration
```cpp
#include <iostream>     // For input/output (cout)
#include <thread>       // For std::this_thread::sleep_for
#include <chrono>       // For time measurement utilities

using namespace std;
using namespace std::chrono;

// Recursive function to calculate Fibonacci numbers
// Warning: This is very slow for large n (e.g., 45+) due to repeated calculations
long long fibonacci(long long n) {
    // Base case: Fibonacci of 0 or 1 is the number itself
    return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // -------------------------------
    // Part 1: Demonstrate sleep/delay
    // -------------------------------

    cout << "Waiter!" << endl;

    // Pause the program for 2 seconds
    this_thread::sleep_for(2s);

    cout << "You called, sir?" << endl;

    cout << "\n--- Fibonacci Timer ---" << endl;

    // -----------------------------------
    // Part 2: Measure execution time
    // -----------------------------------

    // Record start time using a steady (monotonic) clock
    auto start = steady_clock::now();

    // Compute a Fibonacci number (this is intentionally slow)
    long long n = fibonacci(45);

    // Output the result
    cout << "Fibonacci number is " << n << endl;

    // Record end time
    auto finish = steady_clock::now();

    // Calculate elapsed time in milliseconds
    auto elapsed = duration_cast<milliseconds>(finish - start).count();

    // Print how long the computation took
    cout << "Time taken: " << elapsed << " milliseconds" << endl;

    return 0; // Indicate successful program execution
}
```

### Retrieve day, month, year, hour, minute, second
```cpp
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    // Get current time using chrono
    auto now = chrono::system_clock::now();

    // Convert to time_t
    time_t now_c = chrono::system_clock::to_time_t(now);

    // Convert to local time
    tm* timeInfo = localtime(&now_c);

    // Extract date
    int day   = timeInfo->tm_mday;
    int month = timeInfo->tm_mon + 1;      // tm_mon is 0–11
    int year  = timeInfo->tm_year + 1900;  // years since 1900

    // Extract time
    int hours   = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;
    int seconds = timeInfo->tm_sec;

    // Pretty output
    cout << setfill('0');

    cout << "Date: "
         << setw(2) << day << "-"
         << setw(2) << month << "-"
         << year << endl;

    cout << "Time: "
         << setw(2) << hours << ":"
         << setw(2) << minutes << ":"
         << setw(2) << seconds << endl;

    return 0;
}
```

## Mathematical types

```cpp
#include <iostream>     // For input/output
#include <complex>      // For std::complex
#include <cmath>        // For math functions (optional but good practice)

using namespace std;
using namespace std::literals; // Enables complex literals like 1.0i

int main() {
    // Declare a complex number (will be filled from user input)
    complex<double> p;

    // Initialize another complex number q = 3 + 4i
    complex<double> q{3.0, 4.0};

    /*
    // Alternative manual input method (commented out)
    double real, imag;
    cout << "Enter the real part: ";
    cin >> real;
    cout << "Enter the imaginary part: ";
    cin >> imag;
    complex<double> p{real, imag};
    */

    // Ask user to input a complex number in format (real, imaginary)
    cout << "Enter a complex number, e.g. (1.5, 2.7)\n";
    cin >> p;

    // Display the entered number
    cout << "Number entered is " << p << endl;

    // Access real and imaginary parts
    cout << "Real part: " << p.real()
         << ", imaginary part: " << p.imag() << endl;

    // Compare with q = (3, 4)
    cout << p << " is "
         << ((p == q) ? "" : "not ")
         << "equal to (3.0, 4.0)" << endl;

    // Arithmetic operations
    cout << "Adding (3, 4) gives: " << (p + q) << endl;
    cout << "Multiplying by (3, 4) gives: " << (p * q) << endl;

    // Magnitude (absolute value)
    cout << "Magnitude: " << abs(p) << endl;

    // Phase angle (argument in radians)
    cout << "Phase angle: " << arg(p) << endl;

    // Complex conjugate
    cout << "Conjugate: " << conj(p) << endl;

    // Power (square)
    cout << "Square: " << pow(p, 2.0) << endl;

    // Complex sine
    cout << "Sine: " << sin(p) << endl;

    return 0;
}
```

## Bitsets
```cpp
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	bitset<8> b1{"10101110"};                                // Initialize from string literal - bitset with value 174
	bitset<8> b2{0xae};                                      // Initialize from integer value (decimal or hexadecimal)
	bitset<8> b3{0b1010'1110};                               // Initialize from binary constant (C++14)

	bitset<8> b4{0b010'1010};                                // Bitset with value 42

	cout << "b1 is " << b1 << endl;                          // Displays 10101110
	cout << "b4 is " << b4 << endl;                          // Displays 00101010
	cout << "b2 in decimal is " << b2.to_ulong() << endl;    // Displays 174
	cout << "b2 as a string is " << b2.to_string() << endl;  // Displays 10101110

	cout << "~b1 is " << ~b1 << endl;                        // Displays 01010001

	cout << "b1 & b4 is " <<(b1 & b4) << endl;               // Displays 00101010
	cout << "b1 | b4 is " << (b1 | b4) << endl;              // Displays 10101110
	cout << "b1 ^ b4 is " << (b1 ^ b4) << endl;              // Displays 10000100
}
```

## Various Library Features
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>

using namespace std;
using namespace std::placeholders;

/* =========================================================
   Shared helper function (used in bind/ref examples)
   ========================================================= */
void incr(int& number, int& value) {
    // Assign current value to number, then increment value
    number = value;
    ++value;
}

/* =========================================================
   Demo 1: std::bind WITHOUT std::ref (value is copied)
   ========================================================= */
void demo_bind_copy() {
    cout << "=== Demo: std::bind (copy) ===" << endl;

    int n{2};
    auto incr_n = bind(incr, _1, n); // n is copied

    vector<int> numbers(5);

    for (auto& number : numbers)
        incr_n(number);

    cout << "After call, elements are: ";
    for (auto number : numbers)
        cout << number << ", ";

    cout << "\nn = " << n << " (unchanged because it was copied)\n\n";
}

/* =========================================================
   Demo 2: std::bind WITH std::ref (reference is used)
   ========================================================= */
void demo_bind_ref() {
    cout << "=== Demo: std::bind (reference using std::ref) ===" << endl;

    int n{2};
    auto incr_n = bind(incr, _1, ref(n)); // n passed by reference

    vector<int> numbers(5);

    for (auto& number : numbers)
        incr_n(number);

    cout << "After call, elements are: ";
    for (auto number : numbers)
        cout << number << ", ";

    cout << "\nn = " << n << " (changed because it's a reference)\n\n";
}

/* =========================================================
   Demo 3: vector::data()
   ========================================================= */
void print(int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i)
        cout << arr[i] << ", ";
    cout << endl;
}

void demo_data() {
    cout << "=== Demo: vector::data() ===" << endl;

    vector<int> numbers{1, 2, 3, 4, 5};

    //data() gives you a raw pointer to the underlying contiguous array inside a std::vector.
	//This is useful when you need compatibility with APIs that expect a C-style array (int*, double*, etc.).
    print(numbers.data(), numbers.size());

    cout << endl;
}

/* =========================================================
   Demo 4: fstream usage
   ========================================================= */
void demo_fstream() {
    cout << "=== Demo: fstream ===" << endl;

    string filename = "file.txt";

    // Open file (default: input/output depending on file existence)
    fstream file(filename);

    if (!file) {
        cout << "Failed to open file.\n\n";
        return;
    }

    cout << "File opened successfully.\n\n";

    file.close();
}

/* =========================================================
   Demo 5: to_string, stoi, stod
   ========================================================= */
void demo_to_string() {
    cout << "=== Demo: to_string / stoi / stod ===" << endl;

    string hello{"Hello, "};
    string pi{to_string(3.14159)};

    hello += pi;
    cout << hello << endl;

    cout << "stoi(pi): " << stoi(pi) << endl;   // Converts to int (3)
    cout << "stod(pi): " << stod(pi) << endl;   // Converts to double

    cout << endl;
}

/* =========================================================
   Main function: runs all demos
   ========================================================= */
int main() {
    demo_bind_copy();   // bind with copied value
    demo_bind_ref();    // bind with reference
    demo_data();        // vector::data()
    demo_fstream();     // file stream
    demo_to_string();   // string conversions

    return 0;
}
```

## Random number algorithms
```cpp
// random_number_algorithms_sequential.cpp
// This program demonstrates three random-based algorithms in sequence:
// 1. Bernoulli distribution (true/false randomness)
// 2. Drunkard's walk (random movement simulation)
// 3. Shuffle algorithm (random permutation of a list)

#include <random>      // For random number generation
#include <algorithm>   // For shuffle()
#include <vector>      // For using std::vector
#include <iostream>    // For input/output
#include <string>      // For string manipulation
#include <chrono>      // For timing (delays)
#include <thread>      // For sleep_for()

using namespace std;

// Create a Mersenne Twister random number generator
// Seeded with a non-deterministic random device for better randomness
static mt19937 mt(random_device{}());


// --------------------------------------------------
// 1. Bernoulli Distribution Demo
// --------------------------------------------------
void runBernoulli() {
    cout << "\n--- Bernoulli Demo ---\n";

    // Bernoulli distribution generates true/false outcomes
    // Probability = 0.5 means 50% chance of true, 50% false
    bernoulli_distribution berni(0.5);

    // Run the experiment 5 times
    for (int i = 0; i < 5; ++i) {

        // Generate a random boolean value
        if (berni(mt)) {
            cout << "Your subjects are grateful for your wise and benevolent rule\n";
        } else {
            cout << "The peasants are revolting!\n";
        }
    }
}


// --------------------------------------------------
// 2. Drunkard Walk Demo (FINITE version)
// --------------------------------------------------
void runDrunkard() {
    cout << "\n--- Drunkard Walk Demo ---\n";

    // Random boolean to decide direction (left or right)
    bernoulli_distribution berni;

    int x = 20;            // Starting position (middle of screen)
    const int WIDTH = 40;  // Width of the "world"
    int sign = 1;          // Direction: +1 (right), -1 (left)

    // Run for a fixed number of steps so program doesn't get stuck
    for (int step = 0; step < 60; ++step) {

        // Randomly choose direction
        sign = berni(mt) ? 1 : -1;

        // Prevent moving outside boundaries
        if (x <= 1) sign = 1;
        if (x >= WIDTH) sign = -1;

        // Update position
        x += sign;

        // Print the drunkard as a dot ('.') at position x
        // Spaces are used to shift the dot horizontally
        cout << string(x, ' ') << '.'
             << string(WIDTH - x, ' ')
             << "\r" << flush;  // '\r' returns cursor to start (animation effect)

        // Pause briefly so movement is visible
        this_thread::sleep_for(80ms);
    }

    // Move to next line after animation finishes
    cout << endl;
}


// --------------------------------------------------
// 3. Shuffle Demo
// --------------------------------------------------
void runShuffle() {
    cout << "\n--- Shuffle Demo ---\n";

    // Create a vector with some numbers
    vector<int> vec{3, 1, 4, 1, 5, 9};

    // Shuffle and print the vector multiple times
    for (int i = 0; i < 5; ++i) {

        // Randomly reorder elements using the same RNG
        shuffle(vec.begin(), vec.end(), mt);

        // Print shuffled result
        for (auto v : vec)
            cout << v << " ";

        cout << endl;

        // Pause to make changes visible
        this_thread::sleep_for(500ms);
    }
}


// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main() {

    // Run all demos one after another
    runBernoulli();
    runDrunkard();
    runShuffle();

    cout << "\nAll demos completed.\n";

    return 0;
}
```
