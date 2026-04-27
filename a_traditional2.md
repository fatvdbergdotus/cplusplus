# Traditional C++

## Container adapter (containers built on other containers)

### Queue (FIFO)
```cpp
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
```cpp
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
```cpp
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
```cpp
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
```cpp
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
```cpp
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

### Output from parent class
```cpp
#include <iostream>
#include <vector>

using namespace std;

class Drawable {
	public:
	void draw() { cout << "What am I supposed to do here?\n"; }
};

class Circle : public Drawable {
	public:
	void draw() { cout << "I'm a circle!\n"; }
};

class Triangle : public Drawable {
	public:
	void draw() { cout << "I'm a triangle!\n"; }
};

int main() {
	vector<Drawable*> shapes;      // Vector of pointers to Drawable instances

	// Create a pointer to a Drawable instance and append it to the vector 
	shapes.push_back(new Circle());
	shapes.push_back(new Triangle());
	for (vector<Drawable*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
		(*it)->draw();
}
```

### Output from child class (virtual)
Added virtual keyword in the drawable

```cpo
#include <iostream>
#include <vector>

using namespace std;

class Drawable {
	public:
	virtual void draw() { cout << "What am I supposed to do here?\n"; }
};

class Circle : public Drawable {
	public:
	void draw() { cout << "I'm a circle!\n"; }
};

class Triangle : public Drawable {
	public:
	void draw() { cout << "I'm a triangle!\n"; }
};

int main() {
	vector<Drawable*> shapes;      // Vector of pointers to Drawable instances

	// Create a pointer to a Drawable instance and append it to the vector 
	shapes.push_back(new Circle());
	shapes.push_back(new Triangle());
	for (vector<Drawable*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
		(*it)->draw();
}
```
### Pure virtual function
Makes the base class an abstract class which cannot be instantiated. Similar to an interface in other languages.
```cpp
#include <iostream>
#include <vector>

using namespace std;

class Drawable {
	public:
	virtual void draw() const = 0;
};

class Circle : public Drawable {
	public:
	void draw() const { cout << "I'm a circle!\n"; }
};

class Triangle : public Drawable {
	public:
	void draw() const { cout << "I'm a triangle!\n"; }
};

void draw_shape(const Drawable& d) {
    d.draw();                                            // Calls draw member function of Circle etc
}

int main() {
	Circle circle;
	draw_shape(circle);
	//Drawable shape;          // Error!
}
```

**Function overloading** in C++ means defining multiple functions with the same name but different parameter lists (different types, number, or order of arguments), allowing the compiler to choose the correct version at compile time, while **overriding** happens when a derived class provides a new implementation of a base class function with the exact same signature, typically using the virtual and override keywords, and the decision of which function to call is made at runtime through polymorphism (e.g., via base class pointers or references); in short, overloading is about flexibility within the same scope, whereas overriding is about changing inherited behavior.

## Friend keyword

### Friend Function
```cpp
#include <iostream>
#include <string>

using namespace std;

class Test {
	int i{42};
	string s{"Hello"};
public:
	friend void print(const Test&);
};

void print(const Test& test) {
	cout << "i = " << test.i << ", s = " << test.s << endl;
}

int main() {
	Test test;
	print(test);
}
```

### Friend Class
```cpp
#include <iostream>
#include <string>

using namespace std;

// Class with private members
class Test {
    int i{42};            // Private integer member (default is private)
    string s{"Hello"};    // Private string member

public:
    // Declare Example as a friend class
    // This allows Example to access private members of Test
    friend class Example;
};

// Class that can access Test's private members
class Example {
public:
    // Function that takes a Test object (by const reference)
    void print(const Test& test) {
        // Accessing private members of Test (allowed because of friendship)
        cout << "i = " << test.i << ", s = " << test.s << endl;
    }
};

int main() {
    Test test;     // Create Test object
    Example ex;    // Create Example object

    // Call print function to display private data of Test
    ex.print(test);

    return 0;      // End of program
}
```

