# Traditional C++

## Container adapter (containers built on other containers)

### Queue (FIFO)
```
#include <queue>                        
#include <iostream>

using namespace std;

int main() {
	queue<int> q;                                  // Create a queue instance
	q.push(4);                                     // Add some elements to it
	q.push(3);
	q.push(5);
	q.push(1);

	cout << "The queue contains " << q.size() << " elements\n";
	cout << "The first element is "<< q.front() << endl;
	cout << "The last element is "<< q.back() << endl;

	// Remove the first element
	cout << "Removing first element\n";
	q.pop();
	cout << "The first element is now "<< q.front() << endl;
	cout << "The last element is now "<< q.back() << endl;
}
```

### Stack (LIFO)
```
#include <stack>                        
#include <iostream>

using namespace std;

int main() {
	stack<int> s;                               // Create a stack instance
	s.push(1);                                   // Add some elements to it
	s.push(2);
	s.push(5);
	s.push(3);

	cout << "Top element is "<< s.top() << endl;
	cout << "Removing top element\n";
	s.pop();                                        // Remove the top element
	cout << "Top element is now "<< s.top() << endl;
}
```

## Operator overloading

### Operator() is also known as Functor
```
#include <iostream>

using namespace std;

class evenp {                                       // Class with function call operator
  public:
    bool operator() (int n) {                       // Our function call operator
      return (n % 2 == 0);                          // Return true if exactly divisible by 2
    }
};

int main() {
    evenp is_even;                                  // Create an instance of the functor
    if (is_even(6))                                 // Call its function call operator with argument 6
        cout << "6 is an even number\n";
}
```

### Operators +, -, == and <<
```
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    // Constructor
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Overload + operator (add two points)
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    // Overload - operator (subtract two points)
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    // Overload == operator (compare two points)
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    // Overload << operator (for output)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p1(2, 3);
    Point p2(4, 1);

    Point p3 = p1 + p2;   // uses operator+
    Point p4 = p1 - p2;   // uses operator-

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 + p2 = " << p3 << endl;
    cout << "p1 - p2 = " << p4 << endl;

    // Comparison using overloaded ==
    if (p1 == p2)
        cout << "Points are equal" << endl;
    else
        cout << "Points are different" << endl;

    return 0;
}
```

## Algorithms with predicates

### Sort (==)
```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<string> words;
	string s;
	
	cout << "Please type in some words, separated by spaces" << endl;
	
	while (cin >> s && s != "stop") {
		words.push_back(s);
	}
	
	sort(words.begin(), words.end());                          // Sort the words in alphabetical order
	
	cout << "Your words in alphabetical order: " << endl;
	
	vector<string>::iterator it;
	for (it = words.begin(); it != words.end(); ++it)
		cout << *it << ", ";
}
```

### Sort by length using a Functor
```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a predicate as a functor
class is_shorter {
public:
	// Overloaded () operator
	// Takes two strings as arguments
	// Returns true/false depending on relative string length
   bool operator () (const string& lhs, const string& rhs) {
        return lhs.size() < rhs.size();
    }
};

int main() {
	vector<string> words;
	words.push_back("a");
	words.push_back("collection");
	words.push_back("of");
	words.push_back("words");
	words.push_back("with");
	words.push_back("varying");
	words.push_back("lengths");
	
	// Sort the data in alphabetical order
	sort(words.begin(), words.end());
	
	cout << "Sorted alphabetically:" << endl;
	vector<string>::iterator it;
	for (it = words.begin(); it != words.end(); ++it)
		cout << *it << ", ";
	cout << endl;
	
	// Use is_shorter to sort the data
	sort(words.begin(), words.end(), is_shorter());
	
	cout << endl << "Sorted by length:" << endl;
	for (it = words.begin(); it != words.end(); ++it)
		cout << *it << ", ";
	cout << endl;
}
```

## Classes and inheritence

```
#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
protected:
    string name;   // Protected so derived classes can access it

public:
    // Constructor to initialize name
    Animal(string n) : name(n) {}

    // Virtual function (can be overridden in derived class)
    virtual void speak() {
        cout << name << " makes a sound" << endl;
    }

    // Function overloading (same name, different parameter list)
    void speak(int times) {
        for (int i = 0; i < times; i++) {
            cout << name << " makes a sound" << endl;
        }
    }
};

// Derived class
class Dog : public Animal {
public:
    // Constructor calls base class constructor
    Dog(string n) : Animal(n) {}

    // Function overriding
    // This replaces the base class version of speak()
    void speak() override {
        cout << name << " says Woof!" << endl;
    }

    void bark(int times) {
        for (int i = 0; i < times; i++) {
            cout << name << " barks" << endl;
        }
    }
};

int main() {
    Dog d("Buddy");   // Create Dog object

    // Overriding example
    Animal* a = &d;   // Base class pointer pointing to Dog object
    a->speak();       // Calls Dog's version due to virtual function (runtime polymorphism)

    // Overloading example (same function name, different parameters)
    d.speak(2);       // Calls Animal::speak(int)

    // Calling derived class function
    d.bark(3);        // Calls Dog-specific function

    return 0;         // End of program
}
```

**Function overloading** in C++ means defining multiple functions with the same name but different parameter lists (different types, number, or order of arguments), allowing the compiler to choose the correct version at compile time, while **overriding** happens when a derived class provides a new implementation of a base class function with the exact same signature, typically using the virtual and override keywords, and the decision of which function to call is made at runtime through polymorphism (e.g., via base class pointers or references); in short, overloading is about flexibility within the same scope, whereas overriding is about changing inherited behavior.



