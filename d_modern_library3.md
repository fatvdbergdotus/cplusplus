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
