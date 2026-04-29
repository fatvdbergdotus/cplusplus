# Multithreading

## Condition Variables
This program demonstrates how threads coordinate using a std::condition_variable to safely share data between a writer and a reader. A global mutex protects shared variables (sdata and condition_flag), while the condition variable lets one thread sleep until another signals it. In the first example, the reader simply calls cv.wait(lock) and resumes when notified, but this approach can miss signals or wake spuriously. In the second example, the reader uses cv.wait(lock, predicate), which repeatedly checks a condition (condition_flag) and only proceeds when it becomes true—making it reliable even if notifications happen early or spuriously. The writer thread simulates work with a delay, updates the shared data under a lock, sets the condition flag (in the second case), and then calls notify_one() to wake the reader. Together, both examples show why predicate-based waiting is the safer and recommended pattern for thread

```cpp
#include <iostream>              // For input/output (cout)
#include <thread>                // For std::thread
#include <condition_variable>   // For std::condition_variable
#include <string>                // For std::string
#include <chrono>                // For time utilities (sleep_for, durations)

using namespace std;             // Avoid std:: prefix
using namespace std::chrono;     // Allow use of 2s, 500ms literals

// ================= GLOBAL SHARED STATE =================

mutex mut;                      // Mutex to protect shared data
condition_variable cv;          // Condition variable for thread synchronization
string sdata{"Empty"};          // Shared data initialized to "Empty"

// Flag used in predicate-based waiting (second example)
bool condition_flag{false};

// ================= READER (NO PREDICATE) =================

void reader_simple() {
    unique_lock<std::mutex> guard(mut);    // Lock mutex (required for condition_variable)
    cv.wait(guard);                        // Wait until notified (no condition check!)
    cout << "[Simple] Data is " << sdata << endl;  // Print updated data
}

// ================= WRITER (USED BY BOTH) =================

void writer_simple() {
    cout << "[Simple] Writing data..." << endl;    // Indicate work starting
    std::this_thread::sleep_for(2s);               // Simulate work delay

    {
        lock_guard<std::mutex> lg(mut);            // Lock mutex safely
        sdata = "Populated (Simple)";              // Modify shared data
    }                                              // Mutex unlocked here automatically

    cv.notify_one();                               // Notify one waiting thread
}

// ================= READER (WITH PREDICATE) =================

void reader_predicate() {
    unique_lock<std::mutex> lk(mut);               // Lock mutex

    // Wait until condition_flag == true
    // This prevents missed notifications and handles spurious wakeups
    cv.wait(lk, [] { return condition_flag; });

    cout << "[Predicate] Data is \"" << sdata << "\"" << endl; // Print data
}

// ================= WRITER (PREDICATE VERSION) =================

void writer_predicate() {
    cout << "[Predicate] Writing data..." << endl; // Indicate work starting
    std::this_thread::sleep_for(2s);               // Simulate work delay

    {
        lock_guard<std::mutex> lg(mut);            // Lock mutex
        sdata = "Populated (Predicate)";           // Modify shared data
        condition_flag = true;                     // Set condition flag
    }                                              // Unlock happens here

    cv.notify_one();                               // Notify waiting thread
}

// ================= MAIN FUNCTION =================

int main() {

    // ---------- EXAMPLE 1: NO PREDICATE ----------
    cout << "Initial Data (Simple): " << sdata << endl;

    thread reader1{reader_simple};   // Start reader thread
    thread writer1{writer_simple};   // Start writer thread

    writer1.join();                  // Wait for writer to finish
    reader1.join();                  // Wait for reader to finish

    cout << "----------------------------------" << endl;

    // Reset shared data for second example
    sdata = "Empty";
    condition_flag = false;

    // ---------- EXAMPLE 2: WITH PREDICATE ----------
    cout << "Initial Data (Predicate): " << sdata << endl;

    thread writer2{writer_predicate};        // Start writer first

    std::this_thread::sleep_for(500ms);      // Delay to simulate race condition

    thread reader2{reader_predicate};        // Start reader after

    writer2.join();                          // Wait for writer
    reader2.join();                          // Wait for reader

    return 0;                                // Program finished
}
```
