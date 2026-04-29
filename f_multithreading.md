# Multithreading

```cpp
#include <thread>      // For std::thread
#include <iostream>    // For std::cout
#include <string>      // For std::string
#include <functional>  // For std::cref

using namespace std;   // Avoid std:: prefix (for simplicity)

// ------------------- Example 1: No arguments -------------------

// Thread function with no parameters
void hello_no_arg() {                         // Define a function to run in a thread
    cout << "Hello, Thread (no arg)!\n";      // Print message
}

// ------------------- Example 2: Pass by value -------------------

// Thread function taking argument by value
void hello_value(string arg) {                // Copy of string is passed
    cout << arg << endl;                     // Print the copied string
}

// ------------------- Example 3: Pass by reference -------------------

// Thread function taking argument by const reference
void hello_ref(const string& arg) {           // Reference avoids copying
    cout << arg << endl;                     // Print referenced string
}

// ------------------- Main -------------------

int main() {

    // ----------- Example 1: No argument -----------
    thread t1{ hello_no_arg };               // Create thread running hello_no_arg
    t1.join();                               // Wait for thread to finish

    // ----------- Example 2: Pass by value -----------
    thread t2{ hello_value, "Hello, Thread (value)!"s }; // Pass temporary string (copied)
    t2.join();                               // Wait for thread to finish

    // ----------- Example 3: Pass by reference -----------
    string str{ "Hello, Thread (reference)!" }; // Create string variable
    thread t3{ hello_ref, cref(str) };        // Pass reference using std::cref
    t3.join();                               // Wait for thread to finish

    // std::cref is a helper function from the C++ standard library (<functional>)
    // that lets you pass an argument by reference to things like std::thread, which normally copy arguments.

    return 0;                                // End program
}
```

## Shared data
The problem is that std::cout is a shared global object, and when multiple threads write to it at the same time without synchronization, their output operations can interleave unpredictably. A single cout << ... statement is actually several smaller write steps, and the CPU may switch between threads in the middle of those steps, causing characters from different threads to mix together. This creates a race condition where the final output becomes garbled and inconsistent, even though the program doesn’t crash. To avoid this, access to cout must be synchronized (e.g., with a mutex) so only one thread writes at a time.

```cpp
#include <iostream>      // For standard input/output (cout)
#include <thread>        // For std::thread
#include <chrono>        // For time utilities like sleep_for

using namespace std;     // Avoid writing std:: repeatedly

// Function that prints a string multiple times
void print(string str) {
    // Loop 5 times
    for (int i = 0; i < 5; ++i) {
        // Print the first three characters of the string
        cout << str[0] << str[1] << str[2] << endl;

        // Pause the thread for 50 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    // Create thread t1 and pass "abc" to print()
    std::thread t1{print, "abc"};

    // Create thread t2 and pass "def" to print()
    std::thread t2{print, "def"};

    // Create thread t3 and pass "xyz" to print()
    std::thread t3{print, "xyz"};

    // Wait for thread t1 to finish before continuing
    t1.join();

    // Wait for thread t2 to finish
    t2.join();

    // Wait for thread t3 to finish
    t3.join();

    // End of program
    return 0;
}
```

## Mutex
```cpp
#include <iostream>      // For std::cout
#include <thread>        // For std::thread
#include <mutex>         // For std::mutex, lock_guard, unique_lock
#include <chrono>        // For sleep durations

using namespace std;     // Avoid std:: prefix (not recommended in large projects)

mutex print_mutex;       // Global mutex shared by all threads

// =======================
// 1. Using raw mutex
// =======================
void print_mutex_func(string str) {                // Function using manual lock/unlock
    for (int i = 0; i < 5; ++i) {                 // Loop 5 times
        print_mutex.lock();                       // Lock the mutex (enter critical section)
        cout << "[mutex] "                        // Identify method
             << str[0] << str[1] << str[2]        // Print first 3 chars
             << endl;                             // New line
        print_mutex.unlock();                     // Unlock the mutex (leave critical section)
        this_thread::sleep_for(chrono::milliseconds(50)); // Simulate work outside critical section
    }
}

// =======================
// 2. Using lock_guard
// =======================
void print_lock_guard_func(string str) {          // Function using lock_guard
    for (int i = 0; i < 5; ++i) {                // Loop 5 times
        lock_guard<mutex> lk(print_mutex);       // Automatically locks mutex
        cout << "[lock_guard] "                  // Identify method
             << str[0] << str[1] << str[2]
             << endl;
        // No manual unlock needed — happens automatically when lk goes out of scope
        this_thread::sleep_for(chrono::milliseconds(50)); // Simulate work
    }
}

// =======================
// 3. Using unique_lock
// =======================
void print_unique_lock_func(string str) {        // Function using unique_lock
    for (int i = 0; i < 5; ++i) {               // Loop 5 times
        unique_lock<mutex> lk(print_mutex);     // Locks mutex (more flexible than lock_guard)
        cout << "[unique_lock] "
             << str[0] << str[1] << str[2]
             << endl;
        lk.unlock();                            // Manually unlock before end of scope
        this_thread::sleep_for(chrono::milliseconds(50)); // Non-critical work
        // lk will not relock automatically unless told to
    }
}

// =======================
// Main function
// =======================
int main() {
    // Threads using raw mutex
    thread t1(print_mutex_func, "abc");          // Start thread 1
    thread t2(print_mutex_func, "def");          // Start thread 2

    // Threads using lock_guard
    thread t3(print_lock_guard_func, "ghi");     // Start thread 3
    thread t4(print_lock_guard_func, "jkl");     // Start thread 4

    // Threads using unique_lock
    thread t5(print_unique_lock_func, "mno");    // Start thread 5
    thread t6(print_unique_lock_func, "pqr");    // Start thread 6

    // Wait for all threads to finish
    t1.join();                                  // Join thread 1
    t2.join();                                  // Join thread 2
    t3.join();                                  // Join thread 3
    t4.join();                                  // Join thread 4
    t5.join();                                  // Join thread 5
    t6.join();                                  // Join thread 6

    return 0;                                   // Exit program
}
```
