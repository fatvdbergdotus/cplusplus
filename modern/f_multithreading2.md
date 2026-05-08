(c) 2026 Freek van den Berg. All rights reserved.

# Multithreading

## Condition Variables
The producer–consumer model is a classic concurrency pattern where one or more producer threads generate data and place it into a shared buffer, while one or more consumer threads remove and process that data. The key challenge is synchronization: producers must wait if the buffer is full, and consumers must wait if it’s empty. In C++, this is typically handled using a std::mutex (to protect shared access) and a std::condition_variable (to signal when the buffer state changes). Producers push items into a queue and call notify_one() (or notify_all()), while consumers call wait(lock, predicate) to sleep until data is available. The predicate ensures correctness by preventing missed notifications and handling spurious wakeups. This pattern is widely used in systems like task queues, streaming pipelines, and multithreaded servers because it cleanly separates data production from data processing while maintaining thread safety and efficiency.

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

## One producer, multiple consumers
```cpp
#include <iostream>              // For cout
#include <thread>                // For threads
#include <mutex>                 // For mutex
#include <condition_variable>    // For condition_variable
#include <queue>                 // For queue (shared buffer)
#include <vector>                // For multiple consumers
#include <chrono>                // For sleep

using namespace std;
using namespace std::chrono;

// ================= SHARED DATA =================

queue<int> buffer;               // Shared buffer
const unsigned int MAX_SIZE = 5; // Max buffer size

mutex mtx;                       // Protects buffer
condition_variable cv;           // Synchronization

bool done = false;               // Signals producer finished

// ================= PRODUCER =================

void producer() {
    for (int i = 1; i <= 20; ++i) {       // Produce 20 items
        unique_lock<mutex> lock(mtx);     // Lock mutex

        // Wait if buffer is full
        cv.wait(lock, [] {
            return buffer.size() < MAX_SIZE;
        });

        buffer.push(i);                   // Add item
        cout << "Produced: " << i << endl;

        lock.unlock();                   // Unlock before notify
        cv.notify_all();                 // Wake up all consumers
        this_thread::sleep_for(300ms);   // Simulate work
    }

    // Signal completion
    {
        lock_guard<mutex> lg(mtx);
        done = true;                     // No more items coming
    }
    cv.notify_all();                     // Wake all consumers to exit
}

// ================= CONSUMER =================

void consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);     // Lock mutex

        // Wait until buffer has data OR producer is done
        cv.wait(lock, [] {
            return !buffer.empty() || done;
        });

        if (buffer.empty() && done) {
            // No more work to do
            cout << "Consumer " << id << " exiting\n";
            return;
        }

        int item = buffer.front();        // Get item
        buffer.pop();                     // Remove item

        cout << "Consumer " << id << " consumed: " << item << endl;

        lock.unlock();                    // Unlock before notify
        cv.notify_all();                  // Wake producer/others

        this_thread::sleep_for(500ms);    // Simulate processing
    }
}

// ================= MAIN =================

int main() {
    thread p(producer);                  // One producer

    vector<thread> consumers;
    for (int i = 1; i <= 3; ++i) {       // Create 3 consumers
        consumers.emplace_back(consumer, i);
    }

    p.join();                            // Wait producer

    for (auto &c : consumers) {
        c.join();                        // Wait all consumers
    }

    return 0;
}
```

## Promises and futures

```cpp
#include <iostream>     // Allows printing to console (cout)
#include <thread>       // Enables use of std::thread
#include <future>       // Provides std::promise and std::future
#include <exception>    // Supports exception handling

using namespace std;    // Avoid writing std:: everywhere

// ---------- SUCCESS CASE ----------
void producer_success(promise<int> p) {   // Function that sends a value
    p.set_value(42);                      // Store value (42) in the promise
}

// ---------- EXCEPTION CASE ----------
void producer_exception(promise<int> p) { // Function that sends an exception
    try {                                 // Start try block
        throw runtime_error("Error from producer"); // Create and throw error
    } catch (...) {                       // Catch any exception
        p.set_exception(current_exception()); // Store exception in promise
    }
}

int main() {                              // Program entry point

    // ===== WITHOUT EXCEPTION =====
    cout << "=== Success case ===" << endl; // Print section header

    promise<int> p1;                      // Create a promise object
    future<int> f1 = p1.get_future();     // Get future linked to promise

    thread t1(producer_success, move(p1)); // Start thread, move promise into it

    try {                                 // Try to get result
        cout << "Result: " << f1.get() << endl; // Wait for value (returns 42)
    } catch (exception& e) {              // Catch if something goes wrong
        cout << "Exception: " << e.what() << endl; // Print error message
    }

    t1.join();                            // Wait for thread to finish

    // ===== WITH EXCEPTION =====
    cout << "\n=== Exception case ===" << endl; // Print section header

    promise<int> p2;                      // Create another promise
    future<int> f2 = p2.get_future();     // Get its future

    thread t2(producer_exception, move(p2)); // Start thread that throws

    try {                                 // Try to get result
        cout << "Result: " << f2.get() << endl; // This will throw exception
    } catch (exception& e) {              // Catch exception from future
        cout << "Caught exception: " << e.what() << endl; // Print error
    }

    t2.join();                            // Wait for thread to finish

    return 0;                             // End program successfully
}
```

## Asynchronous threads
```cpp
#include <iostream>      // Provides std::cout for console output
#include <thread>        // Provides std::thread for multithreading
#include <future>        // Provides std::async, std::future, std::packaged_task

// ===== FROM async.cc =====

// Simple function that returns a value
int compute() {                     // Function definition
    return 42;                     // Returns constant value 42
}

// Wrapper function (replaces original main)
void run_async_example() {          // Function to demonstrate std::async
    std::cout << "[async example]\n"; // Print section header

    // Launch compute() asynchronously
    std::future<int> result = std::async(compute); 
    // std::async starts compute() possibly on another thread
    // result is a future that will hold the return value

    std::cout << result.get() << std::endl; 
    // get() blocks until result is ready, then returns 42
}



// ===== FROM async_launch_policy.cc =====

// Function used for async execution
int work() {                       // Function definition
    return 10;                     // Returns constant value 10
}

// Wrapper function for launch policy demo
void run_launch_policy_example() { // Demonstrates async launch policies
    std::cout << "[launch policy example]\n"; // Print section header

    // Force execution in a new thread
    auto f1 = std::async(std::launch::async, work); 
    // std::launch::async guarantees immediate execution on a new thread

    // Defer execution until result is requested
    auto f2 = std::async(std::launch::deferred, work); 
    // std::launch::deferred delays execution until get() is called

    std::cout << f1.get() << std::endl; 
    // Waits for thread to finish and prints 10

    std::cout << f2.get() << std::endl; 
    // Executes work() here (no thread) and prints 10
}



// ===== FROM packaged_task.cc =====

// Function that adds two integers
int add(int a, int b) {            // Function takes two ints
    return a + b;                 // Returns their sum
}

// Wrapper function for packaged_task demo
void run_packaged_task_example() { // Demonstrates manual async control
    std::cout << "[packaged_task example]\n"; // Print section header

    // Wrap function into a packaged_task
    std::packaged_task<int(int,int)> task(add); 
    // task now holds the function add()

    // Get future linked to this task
    std::future<int> result = task.get_future(); 
    // result will receive the return value of add()

    // Run task on a separate thread
    std::thread t(std::move(task), 2, 3); 
    // std::move transfers ownership of task to the thread
    // Executes add(2, 3) inside the thread

    t.join(); 
    // Wait for thread to finish before continuing

    std::cout << result.get() << std::endl; 
    // Retrieve result (5) from future and print it
}



// ===== SINGLE ENTRY POINT =====

// Program starts here
int main() {                       // Main function (entry point)

    run_async_example();           // Run first example
    std::cout << "-----------------\n"; // Separator

    run_launch_policy_example();   // Run second example
    std::cout << "-----------------\n"; // Separator

    run_packaged_task_example();   // Run third example
    std::cout << "-----------------\n"; // Separator

    return 0;                      // Indicate successful execution
}
```
