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
