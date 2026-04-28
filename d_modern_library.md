# Modern C++ Library features

## Initializer list
An initializer_list in C++ is a lightweight object that lets you pass a list of values written in curly braces {} to a function or constructor.

```cpp
#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>

using namespace std;

// ===== Class demonstrating initializer_list in a constructor =====
class Test {
    vector<int> vec;  // Container to store integers

public:
    // Constructor accepts an initializer_list and uses it to initialize the vector
    Test(initializer_list<int> il) : vec(il) {}

    // Prints all elements in the vector
    void print() {
        for (auto i : vec)
            cout << i << ", ";
        cout << endl;
    }
};

// Runs the constructor demo
void run_constructor_demo() {
    // Create object using initializer_list syntax
    Test test{3, 4, 5};

    // Print stored values
    test.print();
}

// ===== Function demonstrating initializer_list in function parameters =====

// Prints a list of station names
void announce(initializer_list<string> stations) {
    cout << "This train will stop at: ";

    // Loop through each station and print it
    for (auto station : stations)
        cout << station << ", ";

    cout << endl;
}

// Runs the loop demo
void run_loop_demo() {
    // Example: fast train (only one stop)
    cout << "This is a fast train to London Waterloo.\n";
    announce({"London Waterloo only"});
    cout << "\n";

    // Example: stopping service (multiple stops)
    cout << "This is a stopping service to London Waterloo.\n";
    announce({"Clapham Junction", "Vauxhall", "London Waterloo"});
}

// ===== Entry point of the program =====
int main() {
    // Run constructor example
    cout << "=== Constructor Demo ===\n";
    run_constructor_demo();

    // Run initializer_list loop example
    cout << "\n=== Loop Demo ===\n";
    run_loop_demo();

    return 0; // Indicate successful execution
}
```

## Containers and Insert()
```cpp
using namespace std;


// ===============================
// ORIGINAL FILE: containers_insert/insert.cc =====
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
	for (auto i : vec)
		cout << i << ", ";
	cout << endl;
}

// Entry point from original file
int main_1() {
	vector<int> vec{1, 2, 3, 4, 5};

	cout << "Original vector: ";
	print(vec);

	cout << "\nCalling insert with arguments begin(), 0\n";
	vec.insert(vec.begin(), 0);    // Insert element with value 0 before first element
	print(vec);

	cout << "Calling insert with arguments end(), 3, 6\n";
	vec.insert(vec.end(), 3, 6);      // Insert 3 elements with value 6 after last element
	print(vec);

	vector<int> vec2{3, 1, 4, 1, 5, 9};
	cout << "\nvec2: ";
	print(vec2);

	cout << "\nCalling insert on vec with arguments vec.begin(), vec2.begin(), vec2.end()\n";
	vec.insert(vec.begin(), vec2.begin(), vec2.end());      // Insert all elements from vec2 before first element
	print(vec);

	cout << "\nCalling insert on vec2 with arguments vec2.end(), {2, 6, 5}\n";
	vec2.insert(vec2.end(), {2, 6, 5});
	print(vec2);
}

// ===============================
// ORIGINAL FILE: containers_insert/insert_loop.cc =====
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
	for (auto i : vec)
		cout << i << ", ";
	cout << endl;
}

// Entry point from original file
int main_2() {
	vector<int> vec;
	auto it = vec.begin();           // First element will be added at start of list
	int i;

	while (cin >> i)
		it = vec.insert(it, i);      // Add element. Next element will be added before this one
	
	print(vec);
}

// ===============================
// ORIGINAL FILE: containers_insert/map_insert.cc =====
#include <iostream>
#include <map>

using namespace std;

// Entry point from original file
int main_3() {
	map<string, int> scores;                                           
	scores.insert(make_pair("Maybelline", 86));          // C++03 requires make_pair()
	scores.insert( {"Graham", 78} );                     // C++11 allows initializer_list

	cout << "Map elements:" << endl;
	for (auto it: scores) {                                                     // Use a range-for loop 
		cout << it.first << " has a score of " << it.second << endl;
	}
}

// Unified main function calling all sub-programs
int main() {
    main_1();
    main_2();
    main_3();
    return 0;
}
```

## Containers and emplace
```cpp
#include <iostream>
#include <vector>

using namespace std;

class refrigerator {
    int temperature;
    bool door_open;
    bool power_on;
public:
    refrigerator(int temp, bool open, bool power)
        : temperature(temp), door_open(open), power_on(power) {}

    void print() const {
        cout << "Temperature = " << temperature;
        cout << boolalpha;
        cout << ", door_open = " << door_open;
        cout << ", power_on = " << power_on;
    }
};

void test_insert_emplace() {
    vector<refrigerator> vec;

    refrigerator fridge(2, false, true);
    vec.insert(vec.begin(), fridge);

    vec.insert(vec.end(), refrigerator(3, false, true));
    vec.emplace(vec.end(), 5, false, false);

    cout << "Insert / emplace test:\n";
    for (const auto& el : vec) {
        el.print();
        cout << "\n";
    }
}

void test_push_back_emplace_back() {
    vector<refrigerator> vec;

    refrigerator fridge(2, false, true);
    vec.push_back(fridge);

    vec.push_back(refrigerator(3, false, true));
    vec.emplace_back(5, false, false);

    cout << "\nPush_back / emplace_back test:\n";
    for (const auto& el : vec) {
        el.print();
        cout << "\n";
    }
}

int main() {
    test_insert_emplace();
    test_push_back_emplace_back();
    return 0;
}
```
