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
std::mutex with manual lock()/unlock() gives you the most basic, low-level control but is error-prone because you must remember to unlock it in all cases (including exceptions), otherwise you risk deadlocks; std::lock_guard is a lightweight, scope-based wrapper that automatically locks on creation and unlocks on destruction, making it the safest and simplest choice for straightforward critical sections; std::unique_lock is also RAII-based like lock_guard but more flexible, allowing you to manually unlock/relock, defer locking, or use advanced features like try_lock, making it ideal for more complex synchronization scenarios where you need control without sacrificing safety.

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

## Deadlock and livelock

```cpp
#include <thread>      // For std::thread
#include <mutex>       // For std::mutex, std::timed_mutex
#include <iostream>    // For std::cout
#include <chrono>      // For sleep durations

using namespace std;
using namespace std::literals; // Enables 10ms, 1s, etc.

// ====================== GLOBAL MUTEXES ======================
mutex m1, m2;                 // Normal mutexes (for deadlock demos)
timed_mutex tm1, tm2;         // Timed mutexes (for livelock demos)

// ====================== DEADLOCK EXAMPLE ======================
void deadlock_func1() {
    cout << "[Deadlock] Thread 1 locking m1...\n";       // Log action
    unique_lock<mutex> lk1(m1);                          // Lock m1

    this_thread::sleep_for(50ms);                        // Simulate work

    cout << "[Deadlock] Thread 1 locking m2...\n";       // Try second lock
    unique_lock<mutex> lk2(m2);                          // Wait for m2 (deadlock risk)
}

void deadlock_func2() {
    cout << "[Deadlock] Thread 2 locking m2...\n";       // Log action
    unique_lock<mutex> lk1(m2);                          // Lock m2

    this_thread::sleep_for(50ms);                        // Simulate work

    cout << "[Deadlock] Thread 2 locking m1...\n";       // Try second lock
    unique_lock<mutex> lk2(m1);                          // Wait for m1 (deadlock risk)
}

void run_deadlock() {
    thread t1(deadlock_func1);                           // Start thread 1
    thread t2(deadlock_func2);                           // Start thread 2

    t1.join();                                           // Wait for t1
    t2.join();                                           // Wait for t2
}

// ====================== LIVELOCK EXAMPLE ======================
void livelock_func1() {
    this_thread::sleep_for(10ms);                        // Small delay
    bool locked = false;                                 // Track success

    while (!locked) {                                    // Keep trying
        lock_guard<timed_mutex> lk(tm1);                 // Lock tm1
        this_thread::sleep_for(1s);                      // Simulate work

        cout << "[Livelock] After you!\n";               // Polite conflict

        locked = tm2.try_lock_for(5ms);                  // Try locking tm2
    }
}

void livelock_func2() {
    bool locked = false;                                 // Track success

    while (!locked) {                                    // Keep trying
        lock_guard<timed_mutex> lk(tm2);                 // Lock tm2
        this_thread::sleep_for(1s);                      // Simulate work

        cout << "[Livelock] No, after you!\n";           // Polite conflict

        locked = tm1.try_lock_for(5ms);                  // Try locking tm1
    }
}

void run_livelock() {
    thread t1(livelock_func1);                           // Start thread 1
    thread t2(livelock_func2);                           // Start thread 2

    t1.join();                                           // Wait for t1
    t2.join();                                           // Wait for t2
}

// ====================== NO DEADLOCK (ADOPT LOCK) ======================
void no_deadlock_adopt_func() {
    lock(m1, m2);                                        // Lock both safely

    unique_lock<mutex> lk1(m1, adopt_lock);              // Take ownership
    unique_lock<mutex> lk2(m2, adopt_lock);              // Take ownership

    cout << "[Fix] No deadlock using adopt_lock\n";       // Log result
}

void run_no_deadlock_adopt() {
    thread t1(no_deadlock_adopt_func);                   // Start thread 1
    thread t2(no_deadlock_adopt_func);                   // Start thread 2

    t1.join();                                           // Wait
    t2.join();                                           // Wait
}

// ====================== NO DEADLOCK (DEFER LOCK) ======================
void no_deadlock_defer_func() {
    unique_lock<mutex> lk1(m1, defer_lock);              // Don't lock yet
    unique_lock<mutex> lk2(m2, defer_lock);              // Don't lock yet

    lock(lk1, lk2);                                      // Lock both safely

    cout << "[Fix] No deadlock using defer_lock\n";       // Log result
}

void run_no_deadlock_defer() {
    thread t1(no_deadlock_defer_func);                   // Start thread
    thread t2(no_deadlock_defer_func);                   // Start thread

    t1.join();                                           // Wait
    t2.join();                                           // Wait
}

// ====================== NO LIVELOCK ======================
void no_livelock_func() {
    lock(tm1, tm2);                                      // Lock both safely

    unique_lock<timed_mutex> lk1(tm1, adopt_lock);       // Own tm1
    unique_lock<timed_mutex> lk2(tm2, adopt_lock);       // Own tm2

    this_thread::sleep_for(1s);                          // Simulate work

    cout << "[Fix] No livelock\n";                        // Log result
}

void run_no_livelock() {
    thread t1(no_livelock_func);                         // Start thread
    thread t2(no_livelock_func);                         // Start thread

    t1.join();                                           // Wait
    t2.join();                                           // Wait
}

// ====================== MAIN ======================
int main() {
    cout << "\n--- Deadlock Demo (may hang) ---\n";
    // run_deadlock();   // Uncomment carefully (will deadlock)

    cout << "\n--- Livelock Demo ---\n";
    // run_livelock();   // Uncomment carefully (may loop)

    cout << "\n--- Fix Deadlock (adopt_lock) ---\n";
    run_no_deadlock_adopt();                             // Safe execution

    cout << "\n--- Fix Deadlock (defer_lock) ---\n";
    run_no_deadlock_defer();                             // Safe execution

    cout << "\n--- Fix Livelock ---\n";
    run_no_livelock();                                   // Safe execution

    return 0;                                            // Exit program
}
```

## Atomic types
```cpp
#include <thread>      // For std::thread (multithreading support)
#include <iostream>    // For std::cout (console output)
#include <vector>      // For std::vector (dynamic array of threads)
#include <atomic>      // For std::atomic (thread-safe variables)

using namespace std;   // Avoids writing std:: everywhere (not always recommended in large projects)

// ----------------------
// NON-ATOMIC VERSION
// ----------------------

int counter_non_atomic{0};  // Shared counter (NOT thread-safe)

// Function executed by each thread (non-atomic version)
void task_non_atomic() {
    for (int i = 0; i < 100'000; ++i)  // Loop 100,000 times
        ++counter_non_atomic;          // Increment shared counter (data race!)
}

// ----------------------
// ATOMIC VERSION
// ----------------------

atomic<int> counter_atomic{0};  // Thread-safe counter using atomic

// Function executed by each thread (atomic version)
void task_atomic() {
    for (int i = 0; i < 100'000; ++i)  // Loop 100,000 times
        ++counter_atomic;              // Atomic increment (safe)
}

// ----------------------
// MAIN FUNCTION
// ----------------------

int main() {

    // -------- NON-ATOMIC TEST --------
    {
        vector<thread> tasks;  // Container to store threads

        for (int i = 0; i < 10; ++i)               // Create 10 threads
            tasks.push_back(thread{task_non_atomic}); // Start each thread

        for (auto& t : tasks)  // Wait for all threads to finish
            t.join();

        cout << "Non-atomic counter result: "
             << counter_non_atomic << endl;  // Likely incorrect due to race conditions
    }

    // -------- ATOMIC TEST --------
    {
        vector<thread> tasks;  // Container to store threads

        for (int i = 0; i < 10; ++i)           // Create 10 threads
            tasks.push_back(thread{task_atomic}); // Start each thread

        for (auto& t : tasks)  // Wait for all threads to finish
            t.join();

        cout << "Atomic counter result: "
             << counter_atomic << endl;  // Correct result (should be 1,000,000)
    }

    return 0;  // Program ends successfully
}
```

