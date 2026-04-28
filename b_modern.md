# Modern C++

## Types and literals
```cpp
#include <iostream>
#include <string>
#include <cstdint>

using namespace std;
using namespace std::literals;

int main() {

    // ===== numeric.cc =====
    const int one_million = 1'000'000;
    const int one_lakh = 1'00'000;
    double pi = 3.141'593;
    const int meaning_of_life = 0b101010;

    cout << "One million: " << one_million << endl;
    cout << "One lakh: " << one_lakh << endl;
    cout << "Pi: " << pi << endl;
    cout << "The meaning of life: " << meaning_of_life << endl << endl;


    // ===== raw.cc =====
    string url = "<a href=\"file\">C:\\Program Files\\</a>\\n";
    cout << "URL is " << url << endl << endl;

    string raw_url = R"(<a href="file">C:\Program Files\</a>\n)";
    cout << "Raw URL is " << raw_url << endl << endl;

    string delimited_url = R"x(<a href="file">C:\Program Files (x86)\</a>\n)x";
    cout << "Delimited URL is " << delimited_url << endl << endl;


    // ===== string.cc =====
    const char *cca = "Hello, world!";
    cout << "cca is: " << cca << endl;

    string str = "Hello, world!"s;
    cout << "str is: " << str << endl;

    cout << R"(First element of "Goodbye" is: )";
    cout << *("Goodbye"s.begin()) << endl << endl;


    // ===== int_fixed.cc =====
    cout << "int8_t: " << sizeof(int8_t) << endl;
    cout << "int16_t: " << sizeof(int16_t) << endl;
    cout << "int32_t: " << sizeof(int32_t) << endl;
    cout << "int64_t: " << sizeof(int64_t) << endl << endl;

    cout << "uint8_t: " << sizeof(uint8_t) << endl;
    cout << "uint16_t: " << sizeof(uint16_t) << endl;
    cout << "uint32_t: " << sizeof(uint32_t) << endl;
    cout << "uint64_t: " << sizeof(uint64_t) << endl << endl;


    // ===== long_long.cc =====
    cout << "char: " << sizeof(char) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;

    return 0;
}
```

## User defined literals

### Different suffices
```cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// -------- string.cc --------
string operator "" _rev(const char *s, size_t l) {
    string retval(s, l);
    reverse(retval.begin(), retval.end());
    return retval;
}

// -------- temperature.cc --------
long double operator "" _F_to_C(long double fahrenheit) {
    return 5.0 / 9.0 * (fahrenheit - 32.0);
}

// -------- celsius.cc --------
class Celsius {
    long double temperature;
public:
    explicit Celsius(long double temperature) : temperature(temperature) {}
    void print() const { cout << temperature << " Celsius\n"; }
};

Celsius operator "" _C(long double celsius) {
    return Celsius(celsius);
}

// -------- raw.cc --------
class Bignum {
public:
    Bignum(const char *str) {
        cout << "Creating bignum with value " << str << endl;
    }
};

Bignum operator "" _Big(const char *str) {
    return Bignum(str);
}

// -------- combined main --------
int main() {
    // string.cc demo
    cout << R"("xyz" reversed is )" << "xyz"_rev << endl;

    // temperature.cc demo
    cout << "212 Fahrenheit is " << 212.0_F_to_C << " Celsius" << endl;

    // builtin.cc demo
    cout << 3.14159f << endl;
    cout << "Hello"s << endl;
    cout << 12'345'678'901'234'567'890ULL << endl;

    // celsius.cc demo
    cout << "100.0_C is ";
    Celsius temp = 100.0_C;
    temp.print();

    // raw.cc demo
    Bignum big = "1234567890123456789012345678901234567890"_Big;

    return 0;
}
```

### Suffix for Celcius
operator "" in C++ defines a user-defined literal (UDL)—it lets you attach meaning to suffixes like 100.0_C or "abc"_rev.

```cpp
#include <iostream>
using namespace std;

// -------- celsius + fahrenheit --------
class Celsius {
    long double temperature;
public:
    explicit Celsius(long double temperature) : temperature(temperature) {}

    long double toFahrenheit() const {
        return (temperature * 9.0 / 5.0) + 32.0;
    }

    void print() const {
        cout << temperature << " Celsius\n";
    }

    void printFahrenheit() const {
        cout << toFahrenheit() << " Fahrenheit\n";
    }
};

// Celsius literal
Celsius operator "" _C(long double celsius) {
    return Celsius(celsius);
}

// Fahrenheit literal (converts to Celsius internally)
Celsius operator "" _F(long double fahrenheit) {
    return Celsius((fahrenheit - 32.0) * 5.0 / 9.0);
}

int main() {
    auto tempC = 100.0_C;
    tempC.print();             // 100 Celsius
    tempC.printFahrenheit();   // 212 Fahrenheit

    auto tempFromF = 212.0_F;
    tempFromF.print();         // 100 Celsius

    return 0;
}
```

## Declaration and initialization
auto in for (auto v : old_one) tells the compiler to automatically deduce the type of v from the elements of old_one; since old_one is a vector<int>, v becomes an int for each iteration, making the code shorter and easier to maintain without explicitly writing the type. In this form, v is a copy of each element, so changes to v don’t affect the vector; if you want to avoid copying or modify elements directly, you would use auto& v, and for read-only access without copying, const auto& v is typically preferred.

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -------- alias.cc --------
// Type alias: IntVec is another name for vector<int>
using IntVec = vector<int>;

// -------- nullptr.cc --------
// Function overloading: one takes int, the other takes pointer to int
void func(int i) {
    cout << "func(int) called\n";
}

void func(int* i) {
    cout << "func(int *) called\n";
}

// -------- initialization_contd helper --------
// Empty class used to demonstrate "most vexing parse"
class Test {};

int main() {

    // -------- alias.cc demo --------
    // Vector of vectors using alias
    vector<IntVec> vec_of_vec;
    cout << "Created vector of vector<int>\n";


    // -------- initialization.cc demo --------
    // Uniform initialization using {}
    int x{7};
    string s{"Let us begin"};

    cout << "x = " << x << endl;
    cout << "s = \"" << s << "\"" << endl;

    // Initializing vector and string with list initialization
    vector<int> vec{4, 2, 3, 5, 1};
    string hello{'H', 'e', 'l', 'l', 'o'};

    cout << "vec = ";
    // Range-based for loop with auto (v is int)
    for (auto v : vec)
        cout << v << ", ";

    cout << endl << "hello = \"" << hello << "\"" << endl;


    // -------- initialization_contd.cc demo --------
    // Traditional initialization allows narrowing (double -> int)
    int y = 7.7;

    cout << "y = " << y << endl;

    // Different vector initializations
    vector<int> old_one(4);      // 4 elements, all 0
    vector<int> old_two(4, 2);   // 4 elements, all 2
    vector<int> uni_one{4};      // 1 element: 4
    vector<int> uni_two{4, 2};   // elements: 4, 2

    cout << "old_one = ";
    for (auto v : old_one) cout << v << ", ";

    cout << endl << "old_two = ";
    for (auto v : old_two) cout << v << ", ";

    cout << endl << "uni_one = ";
    for (auto v : uni_one) cout << v << ", ";

    cout << endl << "uni_two = ";
    for (auto v : uni_two) cout << v << ", ";
    cout << endl;

    // Most vexing parse:
    // This looks like object creation, but actually declares a function
    Test test(); 


    // -------- nullptr.cc demo --------
    // NULL is typically 0 → may call func(int)
    func(NULL);

    // nullptr is a true pointer literal → calls func(int*)
    func(nullptr);


    // -------- vector_vector.cc demo --------
    // Nested vector (vector of vector<int>)
    vector<vector<int>> nested_vec;
    cout << "Nested vector created\n";

    return 0;
}
}
```

## Enums

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Enum for task status
enum class Status {
    TODO,
    IN_PROGRESS,
    DONE
};

// Enum for task priority
enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

// Enum for user actions
enum class Action {
    ADD,
    COMPLETE,
    LIST,
    EXIT
};

// Convert enums to string
string toString(Status s) {
    switch (s) {
        case Status::TODO: return "TODO";
        case Status::IN_PROGRESS: return "IN_PROGRESS";
        case Status::DONE: return "DONE";
    }
    return "UNKNOWN";
}

string toString(Priority p) {
    switch (p) {
        case Priority::LOW: return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH: return "HIGH";
    }
    return "UNKNOWN";
}

// Task structure
struct Task {
    int id;
    string name;
    Status status;
    Priority priority;
};

// Print a task
void printTask(const Task& task) {
    cout << "[" << task.id << "] "
         << task.name
         << " | Status: " << toString(task.status)
         << " | Priority: " << toString(task.priority)
         << endl;
}

// List all tasks
void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    for (const auto& task : tasks) {
        printTask(task);
    }
}

// Add a new task
void addTask(vector<Task>& tasks, int& nextId) {
    string name;
    int priorityInput;

    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Priority (0=LOW, 1=MEDIUM, 2=HIGH): ";
    cin >> priorityInput;

    Priority p = Priority::LOW;
    if (priorityInput == 1) p = Priority::MEDIUM;
    else if (priorityInput == 2) p = Priority::HIGH;

    Task t { nextId++, name, Status::TODO, p };
    tasks.push_back(t);

    cout << "Task added.\n";
}

// Mark task as complete
void completeTask(vector<Task>& tasks) {
    int id;
    cout << "Enter task ID to complete: ";
    cin >> id;

    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = Status::DONE;
            cout << "Task marked as DONE.\n";
            return;
        }
    }

    cout << "Task not found.\n";
}

// Convert user input to Action enum
Action getAction(int input) {
    switch (input) {
        case 1: return Action::ADD;
        case 2: return Action::COMPLETE;
        case 3: return Action::LIST;
        default: return Action::EXIT;
    }
}

// Main program
int main() {
    vector<Task> tasks;
    int nextId = 1;

    while (true) {
        cout << "\n--- Task Manager ---\n";
        cout << "1. Add Task\n";
        cout << "2. Complete Task\n";
        cout << "3. List Tasks\n";
        cout << "4. Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        Action action = getAction(choice);

        switch (action) {
            case Action::ADD:
                addTask(tasks, nextId);
                break;

            case Action::COMPLETE:
                completeTask(tasks);
                break;

            case Action::LIST:
                listTasks(tasks);
                break;

            case Action::EXIT:
                cout << "Goodbye!\n";
                return 0;
        }
    }
}
```
