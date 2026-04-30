(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++
## C++ Parameter Passing: Value vs Pointer vs Reference
### 1. Pass by Value

```cpp
#include <iostream>
using namespace std;

int func(int y) {
    cout << "Address of y is " << &y << endl;
    return y;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    int z = func(x);
    cout << "Address of z is " << &z << endl;
    cout << "After calling func(), z = " << z << endl;
}
```
### 2. Pass by pointer

```cpp
#include <iostream>
using namespace std;

void func(int *y) {
    cout << "Address of y is " << y << endl;
    *y = 1;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    func(&x);
    cout << "After calling func(), x = " << x << endl;
}
```

### 3. Pass by reference

```cpp
#include <iostream>
using namespace std;

void func(int& y) {
    cout << "Address of y is " << &y << endl;
    y = 1;
}

int main() {
    int x = 2;
    cout << "Address of x is " << &x << endl;
    func(x);
    cout << "After calling func(), x = " << x << endl;
}
```

## String versus Vectors

### String index
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string hello("Hello");  
    // Creates a std::string object and initializes it with "Hello"
    // Memory is allocated dynamically and managed automatically

    cout << hello[0];  
    // Accesses first character → 'H' (index starts at 0)

    cout << hello[4];  
    // Accesses fifth character → 'o'

    hello[3] = 'b';  
    // Modifies the string: "Hello" → "Helbo"
    // Strings in C++ are mutable (can be changed)

    int i;
    for (i = 0; i < hello.size(); ++i) {
        cout << "Element with index " << i 
             << " has value " << hello[i] << "\n";
    }
    // Iterates through the string using .size()
    // Prints each character and its index

} 
// At the end of main(), the string is automatically destroyed
// Memory is freed (RAII — no manual delete needed)
```

### Vector index
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec;  
    // Creates an empty vector of integers
    // No elements initially, size = 0

    vec.push_back(4);  
    vec.push_back(2);  
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(1);
    // Adds elements to the end of the vector
    // After this: vec = {4, 2, 3, 4, 1}

    cout << "Element with index 0 has value " << vec[0] << endl;
    // First element → 4

    cout << "Element with index 2 has value " << vec[2] << endl;
    // Third element → 3

    cout << "Element with index 4 has value " << vec[4] << endl;
    // Fifth element → 1 (note: comment in original code had a small mistake)

    cout << endl << "Modifying element with index 2 to have value 6" << endl;
    vec[2] = 6;
    // Changes vector: {4, 2, 3, 4, 1} → {4, 2, 6, 4, 1}

    cout << endl << "Printing out all elements: " << endl;

    int i;
    for (i = 0; i < vec.size(); ++i) {
        cout << "Element with index " << i 
             << " has value " << vec[i] << endl;
    }
    // Iterates through all elements using .size()
}
```

### String find
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str ("Hello world");
	cout << "The string is \"" << str << "\"" << endl;
	cout << "First occurrence of \'o\' is at index " << str.find('o') << endl;     // Returns 4
	cout << "First occurrence of \"or\" is at index " << str.find("or") << endl;   // Returns 7

	cout << "Does 'O' occur in the string? ";

	// string::npos represents “no position” or “not found”
	if (str.find('O') == string::npos)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
}
```

## Iterators

### String loop
```cpp
#include <iostream>   // Required for input/output (cout)

using namespace std;

int main() {
    // Define a character array (not null-terminated, just 5 characters)
    const char str[] = {'H','e','l','l','o'};

    // Pointer to one past the last element of the array
    // This is a common technique for marking the "end"
    const char *pEnd = str + 5;

    // Pointer to the first element of the array
    const char *p = str;

    // Loop until the pointer reaches the end position
    while (p != pEnd) {
        // Dereference pointer to get current character and print it
        cout << *p << ", ";

        // Move pointer to the next character in the array
        ++p;
    }

    // Program ends successfully
    return 0;
}
```

### String iterators
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str("Hello");
	
	for (string::iterator it = str.begin(); it != str.end(); ++it)
        cout << *it << ", ";
}
```

### String find
```cpp
#include <iostream>    // For input/output (cout, endl)
#include <string>      // For using std::string
#include <algorithm>   // For std::find

using namespace std;

int main() {
    // Initialize a string with some text
    string str("Hello world");

    // Character we want to search for
    char c = 'l';

    // Display the original string
    cout << "The string is " << str << endl;

    // Display the character we are searching for
    cout << "Searching for character " << c << endl;

    // Use std::find to search for the first occurrence of 'l'
    // It returns an iterator pointing to the found element,
    // or str.end() if the element is not found
    string::iterator res = find(str.begin(), str.end(), c);

    // Check if the character was found
    if (res != str.end())
        // If found, calculate the index by subtracting iterators
        cout << "Found a matching element at index: "
             << res - str.begin() << endl;
    else
        // If not found, print a message
        cout << "String does not contain " << c << endl;

    // End of program
    return 0;
}
```

## Sequential containers (e.g., array)

### Deque
```cpp
#include <deque>       // For std::deque container
#include <iostream>    // For input/output (cout)
#include <algorithm>   // For algorithms like sort and find

using namespace std;

// Function to print all elements in the deque
void print(const deque<int>& dq) {
    cout << "dq elements are: ";

    // Const iterator to traverse the deque (read-only)
    deque<int>::const_iterator it;

    // Loop through all elements from beginning to end
    for (it = dq.begin(); it != dq.end(); ++it) {
        cout << *it << ",";   // Dereference iterator to access element
    }
}

int main() {
    deque<int> dq;   // Create an empty deque container

    // Add elements to the deque
    dq.push_back(4);   // Add 4 at the end
    dq.push_back(2);   // Add 2 at the end
    dq.push_front(1);  // Add 1 at the beginning
    dq.push_front(5);  // Add 5 at the beginning
    dq.push_front(3);  // Add 3 at the beginning

    // Display size and whether deque is empty
    cout << "dq contains " << dq.size() << " elements" << endl;
    cout << "dq is" << (dq.empty() ? "" : " not") << " empty" << endl;

    // Print current elements
    print(dq);

    cout << endl << endl << "Sorting deque" << endl;

    // Sort the deque in ascending order
    sort(dq.begin(), dq.end());

    // Print sorted deque
    print(dq);

    cout << endl << endl << "Inserting element in deque" << endl;

    // Find the first occurrence of value 3
    deque<int>::iterator three = find(dq.begin(), dq.end(), 3);

    // Insert value 0 before the element '3'
    dq.insert(three, 0);

    // Print updated deque
    print(dq);

    cout << endl << endl << "Removing first element" << endl;

    // Remove the first element of the deque
    dq.erase(dq.begin());

    // Print updated deque
    print(dq);

    cout << endl << endl << "Clearing deque" << endl;

    // Remove all elements from the deque
    dq.clear();

    // Check deque status after clearing
    cout << "dq contains " << dq.size() << " elements" << endl;
    cout << "dq is" << (dq.empty() ? "" : " not") << " empty" << endl;

    // Attempt to print (will show nothing after label)
    print(dq);

    return 0;   // End of program
}
```

### List
```cpp
#include <list>        // For std::list container
#include <iostream>    // For input/output (cout)
#include <algorithm>   // For algorithms like find

using namespace std;

// Function to print all elements in the list
void print(const list<int>& l) {
    cout << "l elements are: ";

    // Const iterator to traverse the list (read-only)
    list<int>::const_iterator it;

    // Loop through all elements from beginning to end
    for (it = l.begin(); it != l.end(); ++it) {
        cout << *it << ",";   // Access and print each element
    }
}

int main() {
    list<int> l;   // Create an empty list container

    // Add elements to the list
    l.push_back(4);   // Add 4 at the end
    l.push_back(2);   // Add 2 at the end
    l.push_front(1);  // Add 1 at the beginning
    l.push_front(5);  // Add 5 at the beginning
    l.push_front(3);  // Add 3 at the beginning

    // Display size and whether list is empty
    cout << "l contains " << l.size() << " elements" << endl;
    cout << "l is" << (l.empty() ? "" : " not") << " empty" << endl;

    // Print current elements
    print(l);

    cout << endl << endl << "Sorting list" << endl;

    // Sort the list in ascending order
    // Note: std::list has its own member function sort()
    l.sort();

    // Print sorted list
    print(l);

    cout << endl << endl << "Inserting element in list" << endl;

    // Find the first occurrence of value 3
    list<int>::iterator three = find(l.begin(), l.end(), 3);

    // Insert value 0 before the element '3'
    l.insert(three, 0);

    // Print updated list
    print(l);

    cout << endl << endl << "Removing first element" << endl;

    // Remove the first element of the list
    l.erase(l.begin());

    // Print updated list
    print(l);

    cout << endl << endl << "Clearing list" << endl;

    // Remove all elements from the list
    l.clear();

    // Check list status after clearing
    cout << "l contains " << l.size() << " elements" << endl;
    cout << "l is" << (l.empty() ? "" : " not") << " empty" << endl;

    // Attempt to print (will show nothing after label)
    print(l);

    return 0;   // End of program
}
```

## Associative containers with a key (e.g., set and map)

### Set
```cpp
#include <set>
#include <iostream>

using namespace std;

void print(const set<int>& s) {
	cout << "Set values: ";
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); ++it)
	 cout << *it << ",";
	cout << endl;
}

// ret.first iterator to the element in the set
// ret.second boolean result of insertion

int main() {
	set<int> s;                             // Create an instance of std::set
	s.insert(6);                            // Add some elements to it
	s.insert(7);
	s.insert(4);
	s.insert(5);
	s.insert(3);

	print(s);	
	cout <<  endl << "Trying to insert element with value 3" << endl;
	pair<set<int>::iterator, bool> ret = s.insert(3);          // Try to insert an element with value 3
	if (ret.second)                                            // Did it work?
		cout << "Added value 3 to set\n";
	else
		cout << "Set already contains " << *(ret.first) << endl;

	cout << "Erasing element with value 3" << endl;
	s.erase(3);                                                // Erase the element with value 3
	
	print(s);
	
	cout <<  endl << "Trying to insert element with value 3" << endl;
	pair<set<int>::iterator, bool> ret2 = s.insert(3);         // Try to insert the element again
	if (ret2.second)                                           // Did it work?
		cout << "Added value 3 to set\n";
	else
		cout << "Set already contains " << *(ret.first) << endl;
	
	print(s);
}
```

### Multiset (like set but allows duplicate values)
```cpp
#include <set>
#include <iostream>

using namespace std;

void print(const multiset<int>& s) {
	cout << "Set values: ";
	multiset<int>::iterator it;
	for (it = s.begin(); it != s.end(); ++it)
	 cout << *it << ",";
	cout << endl;
}

int main() {
	multiset<int> s;                        // Create an instance of std::set
	s.insert(6);                            // Add some elements to it
	s.insert(7);
	s.insert(4);
	s.insert(6);                            // Add duplicate elements
	s.insert(6);

	print(s);
}
```

### Map

```cpp
#include <map>
#include <string>
#include <iostream>

using namespace std;

void print(const map<string, int>& scores) {
	cout << "Map elements: " << endl;
	map<string, int>::const_iterator it;
	for (it = scores.begin(); it != scores.end(); ++it)
		cout << it->first << " has a score of " << it->second << endl;
	cout << endl;
}

int main() {
	map<string, int> scores;                                           // Create an instance of std::map
	scores.insert(make_pair<string, int>("Maybelline", 86));           // Add some elements to it
	scores.insert(make_pair<string, int>("Graham", 78));

	print(scores);
	
	cout << "Graham has a score of " << scores["Graham"] << endl;      // Fetches the value with key "Graham"
	print(scores);
	
	cout << "Setting Graham's score to 66" << endl;
	scores["Graham"] = 66;          // Changes the value of the element with key "Graham"
	print(scores);
	
	cout << "Adding Grace's score of 66" << endl;
	scores["Grace"] = 66;           // Creates a new element with key "Grace"
	print(scores);
	
	map<string, int>::const_iterator p = scores.find("Graham");
	if (p != scores.end())
		cout << "Found element with key " << p->first << ". It has value " << p->second << endl;
}
```

### Multimap (like map but allows duplicate values)
```cpp
#include <map>
#include <string>
#include <iostream>

using namespace std;

void print(const multimap<string, int>& scores) {
	cout << "Map elements: " << endl;
	multimap<string, int>::const_iterator it;
	for (it = scores.begin(); it != scores.end(); ++it)
		cout << it->first << " has a score of " << it->second << endl;
	cout << endl;
}

int main() {
	multimap<string, int> scores;                              // Create an instance of std::multimap
	scores.insert(make_pair<string, int>("Graham", 78));       // Add some elements to it
	scores.insert(make_pair<string, int>("Grace", 66));
	scores.insert(make_pair<string, int>("Graham", 66));       // Add duplicate elements
	scores.insert(make_pair<string, int>("Graham", 72));
	scores.insert(make_pair<string, int>("Hareesh", 77));

	print(scores);
	
	cout << "Removing all Graham's scores" << endl;
	scores.erase("Graham");                                    // Remove all elements with key "Graham"
	print(scores);
}
```







(c) 2026 Freek van den Berg. All rights reserved.

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

```cpp
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

(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++

## Exceptions

### No try catch
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	cout << v[2] << endl;            // Invalid element - program continues in undefined state
	cout << v.at(2) << endl;        // Invalid element - exception thrown
}
```

### Try catch
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	try {
		cout << v.at(2) << endl;                // Throws an exception
	}
	catch (const std::exception& e) {           // Will handle all subclasses of std::exception
		cout << "Exception caught: " << e.what() << endl;               // Print out a description of the exception
	}
}
```

### Try catch with a throw
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v;
	try {
		if (v.size() < 3)
			throw std::out_of_range("Oops");
		cout << v[2] << endl;
	}
	catch (const std::exception& e) {           // Will handle all subclasses of std::exception
		cout << "Exception caught: " << e.what() << endl;               // Print out a description of the exception
	}
}
```

### Promise to not throw exceptions
If the function does throw an exception, the program terminates immediately.

```cpp
#include <iostream>
using namespace std;

// Function that guarantees it will NOT throw exceptions
void func() noexcept {
    cout << "This function does not throw exceptions" << endl;
}

int main() {
    func();   // Safe to call, no exceptions expected
    return 0;
}
```

## Templates (generics)

```cpp
#include <iostream>
using namespace std;

// Template function (works with any type T)
template <typename T>
T add(T a, T b) {
    return a + b;   // Works as long as + is defined for T
}

int main() {
    // Using template with different data types
    cout << add<int>(2, 3) << endl;        // int version
    cout << add<double>(2.5, 3.5) << endl; // double version

    // Compiler can also deduce the type automatically
    cout << add(10, 20) << endl;           // T = int

    return 0;
}
```

## Namespaces

### Simple namespace
```cpp
#include <iostream>

using namespace std;

int x{23};                          // x defined in the global namespace

namespace A {
	int x{47};                          // x defined in the namespace A - hides global x
	void func() { 
		cout << "x = " << x << endl;        // Will use A's x ==> 47
		cout << "::x = " << ::x << endl;    // Will use global x ==> 23
	}
}

int main() {
	A::func();
}
```

```cpp
#include <iostream>
using namespace std;

// Define a namespace
namespace MyNamespace {
    int value = 10;

    void show() {
        cout << "Inside MyNamespace, value = " << value << endl;
    }
}

int main() {
    // Access namespace members using scope resolution operator ::
    cout << MyNamespace::value << endl;
    MyNamespace::show();

    return 0;
}
```

### Nested namespace
```cpp
#include <iostream>

namespace Outer {
    namespace Inner {
        void greet() {
            std::cout << "Hello from Inner namespace!" << std::endl;
        }
    }
}

int main() {
    Outer::Inner::greet();  // access nested namespace
    return 0;
}
```

### Inline namespace
```cpp
#include <iostream>

// Outer namespace
namespace Library {

    // Inline namespace (automatically used)
    inline namespace v1 {
        void print() {
            std::cout << "Version 1\n";
        }
    }

    // Another version (not inline)
    namespace v2 {
        void print() {
            std::cout << "Version 2\n";
        }
    }
}

int main() {
    Library::print();      // Calls v1::print() (default)
    Library::v2::print();  // Explicitly call version 2

    return 0;
```

## Synthesized functions
The following code demonstrates how C++ handles object creation and copying when no custom constructors or operators are defined: the compiler automatically provides a default constructor, copy constructor, and assignment operator, which are used when creating objects (Test test), copying them (Test test3 = test), and assigning them (test = test2); however, because the member variable i is never initialized, all objects contain undefined (garbage) values, showing the importance of explicitly initializing class members even when relying on compiler-generated behavior.

```cpp
#include <iostream>

using namespace std;

class Test {
    int i;   // Member variable (uninitialized!)

public:
    // Default constructor (currently missing)
    // If you uncomment this, it will initialize i
    // Test() : i(0) {}

    // Parameterized constructor
    // Test(int i) : i(i) {}

    // Copy constructor
    // Test(const Test& other) : i(other.i) {}

    // Assignment operator
    // Test& operator=(const Test& other) {
    //     i = other.i;
    //     return *this;
    // }

    // Destructor
    // ~Test() {}

    // Function to print value of i
    void print() {
        cout << i << endl;   // Undefined value if i is not initialized
    }
};

int main() {
    // Default constructor is called (compiler-generated)
    Test test;

    cout << "test after default constructor: ";
    test.print();   // i is uninitialized, garbage value

    // Another object using default constructor
    Test test2;

    cout << "test2 after default constructor: ";
    test2.print();  // also uninitialized

    // Copy constructor is called here
    Test test3 = test;

    cout << "test3 after copy constructor: ";
    test3.print();  // copies the same (garbage) value

    // Assignment operator is called here
    test = test2;

    cout << "test after assignment operator: ";
    test.print();   // now has same value as test2

    return 0;
}
```

## Casting 
### C-style cast (old, not recommended)
```cpp
#include <iostream>

using namespace std;

int main() {
	int c = 'A';
	cout << c << endl;
	cout << (char)c << endl;
}
```

### static_cast (most common, used for safe, compile-time conversions)
```cpp
#include <iostream>

using namespace std;

int main() {
	int c = 'A';
	cout << c << endl;
	cout << static_cast<char>(c) << endl;
}
```

### dynamic_cast (runtime, polymorphism)
```cpp
class Base { virtual void f() {} };
class Derived : public Base {};

Base* b = new Derived;
Derived* d = dynamic_cast<Derived*>(b);

if (d) {
    // successful cast
}
```

### Const_cast (Used to add or remove const)
Dangerous if you modify something that was originally const
```cpp
#include <iostream>

using namespace std;

void print(char *str) {       // Doesn't mutate str, but not declared const
    cout << str << endl;
}

int main() {
	const char *msg = "Hello, world!";
	//print(msg);               // Error - invalid conversion
	print(const_cast<char *>(msg));
}
```


(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++

## Run-time type information
### Typeid
```cpp
#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {};

int main() {
	Derived derived;
	Base *pBase = &derived;
	
	if (typeid(*pBase) == typeid(derived))
		cout << "pBase points to a Derived object" << endl;
	else
		cout << "pBase does not point to a Derived object" << endl;
}
```

### Type_info
```cpp
#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {};

int main() {
	Derived derived;
	Base *pBase = &derived;
	
	const type_info& tBase = typeid(*pBase);
	const type_info& tDerived = typeid(derived);
	
	cout << "Dynamic type of pBase is " << tBase.name() << endl;
	cout << "Dynamic type of derived is " << tDerived.name() << endl;
}
```

### Dynamic cast
Checks wheter it is possible to convert from the base class to a derived class at run-time.
```cpp
#include <iostream>

using namespace std;

class Base {
	public:
	virtual ~Base() {}
};
class Derived : public Base {
	public:
	void derived_func() { cout << "Calling derived_func()\n"; }
};

int main() {
	Derived d;
	Base *pBase = &d;
	
	Derived *pDerived = dynamic_cast<Derived *>(pBase);
	
	// Dangerous!
	pDerived->derived_func();
}
```

## Miscellaneous features

### Booleans
```cpp
#include <iostream>

using namespace std;

int main() {
	int x = -7;
	bool neg = x < 0;
	cout << "Is x negative?" << endl;
	cout << neg << endl; // 1
	cout << boolalpha << neg << endl; // true (because not zero)
}
```

### Without Explicit (implicit conversion allowed)
```cpp
#include <iostream>
using namespace std;

class Test {
    int value;
public:
    Test(int v) : value(v) {}   // NOT explicit

    void print() {
        cout << value << endl;
    }
};

void show(Test t) {
    t.print();
}

int main() {
    show(5);   // int → Test conversion happens automatically
}
```

### With Explicit (safer)
```cpp
#include <iostream>
using namespace std;

class Test {
    int value;
public:
    explicit Test(int v) : value(v) {}   // explicit constructor

    void print() {
        cout << value << endl;
    }
};

void show(Test t) {
    t.print();
}

int main() {
    // show(5);   ERROR: implicit conversion not allowed

    show(Test(5));   // must be explicit
}
```

(c) 2026 Freek van den Berg. All rights reserved.

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

## Automatic type deduction
All of this is resolved at compile time (statically).

```cpp
int main() {
	int x{42};
	const int cx{42};
	const int& rcx{x};

	// A declaration with auto can be rewritten as a call to a template function.
	// The type of the variable is the same as the type that is deduced in the function

	auto& i1 = x;                                     // auto = int, i1 = int&
	//template <typename Auto> void func(Auto& a);
	//func(x);                                        // Auto = int, a = int&, i1 = int&

	auto& i2 = cx;                                    // auto = const int, i2 = const int&
	//template <typename Auto> void func(Auto& a);   
	//func(cx);                                       // Auto = const int, a = const int&, i2 = const int&
	
	auto& i3 = rcx;                                   // auto = const int&, i3 = const int&
	//template <typename Auto> void func(Auto& a);   
	//func(rcx);                                      // Auto = const int, a = const int&, i3 = const int&
	
	const auto& i4 = x;                               // auto = int, i4 = const int&
	//template <typename Auto> void func(const Auto& a);                     
	//func(x);                                        // Auto = int, a = const int&, i1 = const int&
	
	const auto& i5 = cx;                              // auto = int, i5 = const int&
	//template <typename Auto> void func(const Auto& a);   
	//func(cx);                                       // Auto = int, a = const int&, i5 = const int&
	
	const auto& i6 = rcx;                             // auto = int, i6 = const int&
	//template <typename Auto> void func(const Auto& a);   
	//func(rcx);                                      // Auto = int, a = const int&, i6 = const int&
}
```

## Loops

```cpp
#include <iostream>
using namespace std;

int main() {
    // Initialize a simple array
    int arr[] = {1, 2, 3, 4, 5};
    
    // -----------------------------------------
    // Normal iterator (begin → end)
    // -----------------------------------------
    // begin(arr) points to the first element
    // end(arr) points *past* the last element
    cout << "Iterator: ";
    for (auto it = begin(arr); it != end(arr); ++it)
        cout << *it << ", ";  // dereference iterator to get value
    
    // -----------------------------------------
    // Const iterator (read-only access)
    // -----------------------------------------
    // cbegin/cend ensure elements cannot be modified
    cout << endl << "Const iterator: ";
    for (auto it = cbegin(arr); it != cend(arr); ++it)
        cout << *it << ", ";  // safe: cannot modify *it
    
    // -----------------------------------------
    // Reverse iterator (end → begin)
    // -----------------------------------------
    // rbegin starts from the last element
    // rend goes before the first element
    cout << endl << "Reverse iterator: ";
    for (auto it = rbegin(arr); it != rend(arr); ++it)
        cout << *it << ", ";  // prints in reverse order
    
    // -----------------------------------------
    // Const reverse iterator (read-only reverse)
    // -----------------------------------------
    // crbegin/crend combine reverse + const safety
    cout << endl << "Const reverse iterator: ";
    for (auto it = crbegin(arr); it != crend(arr); ++it)
        cout << *it << ", ";  // cannot modify elements
}
```

### Range for-loops
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> vec = {1, 2, 3, 4};
	
	cout << "Vector elements: " << endl;
	for (auto el : vec)
		cout << el << ", ";                                          // Prints out each element of vec

	cout << endl << "Adding 2 to each element" << endl;
	for (auto& el : vec)
		el += 2;                                                    // Add 2 to each element of vec

	cout << endl << "Modified vector elements: " << endl;
	for (auto el : vec)
		cout << el << ", ";                                         // Prints out each element of vec
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# Modern C++

## Constructors
```cpp
#include <iostream>
using namespace std;

// =====================================================
// Version 1: init.cc style
// Demonstrates: basic constructor with simple setup
// =====================================================
class FridgeInit {
public:
    // Default constructor
    FridgeInit() {
        cout << "[Init] Constructor called\n";
    }
};


// =====================================================
// Version 2: inplace.cc style
// Demonstrates: in-class member initialization (C++11+)
// =====================================================
class FridgeInplace {
    int temperature{2};  // initialized directly where declared

public:
    FridgeInplace() {
        cout << "[Inplace] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 3: constructors.cc style
// Demonstrates: parameterized constructor + initializer list
// =====================================================
class FridgeConstructors {
    int temperature;

public:
    // Constructor using initializer list (best practice)
    FridgeConstructors(int t) : temperature(t) {
        cout << "[Constructors] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 4: default.cc style
// Demonstrates: assigning values inside constructor body
// =====================================================
class FridgeDefault {
    int temperature;

public:
    // Default constructor
    FridgeDefault() {
        temperature = 2;  // assignment (less efficient than init list)
        cout << "[Default] temperature = " << temperature << endl;
    }
};


// =====================================================
// Version 5: delegate.cc style
// Demonstrates: constructor delegation (C++11+)
// =====================================================
class FridgeDelegate {
    int temperature;

public:
    // Default constructor delegates to another constructor
    FridgeDelegate() : FridgeDelegate(2) {}

    // Main constructor
    FridgeDelegate(int t) : temperature(t) {
        cout << "[Delegate] temperature = " << temperature << endl;
    }
};


// =====================================================
// MAIN FUNCTION
// Only ONE main() is allowed in a program
// Creates one object from each version
// =====================================================
int main() {
    cout << "Creating all fridge versions:\n\n";

    // Each object demonstrates a different initialization style
    FridgeInit f1;              // basic constructor
    FridgeInplace f2;           // in-class initialization
    FridgeConstructors f3(5);   // parameterized constructor
    FridgeDefault f4;           // assignment in constructor body
    FridgeDelegate f5;          // constructor delegation

    return 0;
}
```

## Delete and Default keywords for Classes
A default constructor is a special function that creates an object with no arguments (e.g., Test t;), while a copy constructor creates a new object as a copy of an existing one (e.g., Test t2 = t1;), meaning it runs during initialization of a new object from another. In contrast, the copy assignment operator does not create a new object but instead copies data into an already existing object (e.g., t2 = t1;). The key difference is that the default and copy constructors are used when an object is being created, whereas the assignment operator is used after objects already exist; together, they control how objects are initialized and how their data is duplicated or reassigned in C++.

```cpp
#include <iostream>

// ============================================================
// Example 1: Modern C++ way — using =delete
// ============================================================

class TestDeleted {
public:
    // Delete the copy constructor
    // This means objects of this class CANNOT be copied
    TestDeleted(const TestDeleted&) = delete;

    // Delete the copy assignment operator
    // This prevents assigning one object to another
    TestDeleted& operator=(const TestDeleted&) = delete;

    // Default constructor is still allowed
    // So we can create objects normally
    TestDeleted() = default;
};

// Function to demonstrate behavior of TestDeleted
void runDeletedExample() {
    TestDeleted t1, t2;   // OK: default construction works

    // The following lines are intentionally commented out
    // because they would cause compilation errors:

    // TestDeleted t3(t1);
    // Error: copy constructor is deleted

    // t2 = t1;
    // Error: assignment operator is deleted

    // This pattern is useful when you want to explicitly
    // forbid copying (e.g., for resource management classes)
}


// ============================================================
// Example 2: Old C++98 technique — private copy operations
// ============================================================

class TestUncopyable {
private:
    // Copy constructor declared PRIVATE
    // This prevents copying from outside the class
    TestUncopyable(const TestUncopyable&);

    // Copy assignment operator also PRIVATE
    TestUncopyable& operator=(const TestUncopyable&);

public:
    // Public default constructor allows object creation
    TestUncopyable() {}
};

// Function to demonstrate behavior of TestUncopyable
void runUncopyableExample() {
    TestUncopyable t1, t2;   // OK: objects can be created

    // The following lines would cause compilation errors:

    // TestUncopyable t3(t1);
    // Error: copy constructor is private

    // t2 = t1;
    // Error: assignment operator is private

    // Note:
    // In old C++ (before C++11), this was the common way
    // to prevent copying.
    // However, it's less clear and less safe than =delete.
}


// ============================================================
// Main function
// ============================================================

int main() {
    // Run both examples
    runDeletedExample();
    runUncopyableExample();

    // If program reaches here, everything compiled fine
    std::cout << "Examples compiled successfully.\n";

    return 0;
}
```

## Conversion operator
An explicit conversion operator in C++ is a way to define how an object can be converted to another type—but only when you ask for it explicitly. It prevents the compiler from doing automatic (implicit) conversions behind your back.

```cpp
#include <iostream>
using namespace std;

/*
========================================================
1. IMPLICIT CONVERSION OPERATOR
========================================================
*/
namespace implicit_demo {

class Test {
    int i{42};
public:
    operator int() const { return i; }
};

void run() {
    cout << "[Implicit conversion]\n";
    Test t;
    cout << t << endl;
    cout << endl;
}

}


/*
========================================================
2. EXPLICIT CONVERSION OPERATOR
========================================================
*/
namespace explicit_demo {

class Test {
    int i{42};
public:
    explicit operator int() const { return i; }
};

void run() {
    cout << "[Explicit conversion]\n";
    Test t;
    cout << static_cast<int>(t) << endl;
    cout << endl;
}

}


/*
========================================================
3. EXPLICIT BOOL + INT CONVERSION
========================================================
*/
namespace explicit_bool_demo {

class Test {
    int i{42};
public:
    explicit operator int() const { return i; }
    explicit operator bool() const { return i; }
};

void run() {
    cout << "[Explicit bool + int conversion]\n";
    Test t;

    cout << static_cast<int>(t) << endl;

    if (t)
        cout << "OK" << endl;

    cout << endl;
}

}


/*
========================================================
4. FUNCTION CALL OPERATOR (operator())
- Makes objects behave like functions
========================================================
*/
namespace function_call_demo {

class Multiplier {
    int factor;
public:
    Multiplier(int f) : factor(f) {}

    // Function call operator
    int operator()(int value) const {
        return value * factor;
    }
};

void run() {
    cout << "[Function call operator()]\n";

    Multiplier doubleIt(2);
    Multiplier tripleIt(3);

    cout << "doubleIt(5): " << doubleIt(5) << endl;
    cout << "tripleIt(5): " << tripleIt(5) << endl;

    cout << endl;
}

}


/*
========================================================
5. SURPRISING CASE
========================================================
*/
namespace surprise_demo {

void run() {
    cout << "[Surprise example]\n";

    int i = 99;

    // Avoid confusing operator misuse like:
    // cin << i;

    cout << "cin << i compiles in some contexts but is meaningless.\n";
    cout << endl;
}

}


/*
========================================================
MAIN FUNCTION
========================================================
*/
int main() {
    implicit_demo::run();
    explicit_demo::run();
    explicit_bool_demo::run();
    function_call_demo::run();
    surprise_demo::run();

    return 0;
}
```

## Inheritence

```cpp
#include <iostream>
using namespace std;

/*
    =========================
    1. Base Class with Constructor
    =========================
*/
class Refrigerator {
    int temperature;
    bool door_open;
    bool power_on;

public:
    // Constructor using initializer list
    Refrigerator(int temp, bool open, bool power)
        : temperature(temp), door_open(open), power_on(power) {
        cout << "Refrigerator constructor\n";
    }
};

/*
    =========================
    2. Derived Class inheriting constructor
    =========================
*/
class SuperFridge : public Refrigerator {
public:
    // Inherit base class constructor directly
    // A constructor inheritance feature in C++ (introduced in C++11).
    // It tells the derived class to reuse all constructors from the base class without rewriting them.
    using Refrigerator::Refrigerator;
};

/*
    =========================
    3. final class example
    =========================
*/
class NoKids final {
    // This class cannot be inherited
};

// Uncommenting below will cause a compilation error
/*
class Child : public NoKids {
};
*/

/*
    =========================
    4. final function example
    =========================
*/
class Base {
public:
    virtual void f() {
        cout << "Base f()\n";
    }
};

class Derived : public Base {
public:
    void f() final {   // Cannot be overridden further
        cout << "Derived f() (final)\n";
    }
};

// Uncommenting below will cause an error
/*
class Derived2 : public Derived {
public:
    void f() { }  // ERROR: cannot override final function
};
*/

/*
    =========================
    5. override keyword example
    =========================
*/
class Vehicle {
public:
    virtual void accelerate() {
        cout << "Vehicle accelerating\n";
    }
};

class Plane : public Vehicle {
public:
    void accelerate() override {  // Correct override
        cout << "Plane accelerating\n";
    }

    // This would cause an error because it doesn't match base signature
    // void accelerate(int height) override;
};

/*
    =========================
    Main Function
    =========================
*/
int main() {
    // Constructor inheritance demo
    SuperFridge sf(4, false, true);

    // Virtual + override demo
    Plane p;
    p.accelerate();

    // Final function demo
    Derived d;
    d.f();

    return 0;
}
```


(c) 2026 Freek van den Berg. All rights reserved.

# Modern C++

## Noexcept
```cpp
#include <iostream>

using namespace std;

void does_not_throw(int input) noexcept {       // I promise not to throw any exceptions
    // No exceptions thrown here, honest
}

void does_throw(int input) {       // May throw exceptions

}

int main() {
	int i;
	cout << "Is does_not_throw noexcept? ";
	cout << boolalpha << noexcept(does_not_throw(i)) << endl;
	cout << "Is does_throw noexcept? ";
	cout << boolalpha << noexcept(does_throw(i)) << endl;
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# Lambda expressions
In a C++ lambda, the capture clause [], the parameter list (), and the function body {} each play a distinct role: the capture clause specifies which variables from the surrounding scope are accessible inside the lambda (either by value like [x], by reference like [&x], or more broadly with [=] or [&]), the parameter list defines the inputs the lambda accepts just like a normal function (e.g., (int a, int b)), and the body contains the actual logic that runs when the lambda is invoked, optionally returning a value; together, they let you create a compact, inline function that can both use external context and process new inputs at the same time.

## Overview

### Simple lambda function 1
```cpp
#include <iostream>
using namespace std;

int main() {
    // A lambda that takes two ints and returns their sum

    cout << [](int a, int b) { return a + b; } (3, 4); // Output: 7
}
```

### Simple lambda function 2
```cpp
#include <iostream>
using namespace std;

int main() {
    // A lambda that takes two ints and returns their sum
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << add(3, 4); // Output: 7
}
```

### String compare with lambda
```cpp
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// ------------------------------------------------------------
// Version 1: Using STL algorithm + lambda
// This function compares two strings ignoring case differences
// by using std::equal with a custom comparison (lambda).
// ------------------------------------------------------------
bool equal_strings_lambda(const string& lhs, const string& rhs) {
    // If lengths differ, strings cannot be equal
    if (lhs.size() != rhs.size()) return false;

    // std::equal compares elements from lhs and rhs
    // The lambda defines how characters are compared
    return equal(lhs.begin(), lhs.end(), rhs.begin(),
                 [](char lc, char rc) {
                     // Convert both characters to uppercase
                     // before comparing to ignore case differences
                     return toupper(lc) == toupper(rc);
                 });
}

// ------------------------------------------------------------
// Version 2: Manual implementation
// This function does the same comparison but without STL helpers.
// It iterates through both strings character by character.
// ------------------------------------------------------------
bool equal_strings_manual(const string& lhs, const string& rhs) {
    // If lengths differ, strings cannot be equal
    if (lhs.size() != rhs.size())
        return false;

    // Create constant iterators for both strings
    auto lit = lhs.cbegin();
    auto rit = rhs.cbegin();

    // Loop through both strings simultaneously
    while (lit != lhs.cend() && rit != rhs.cend()) {
        // Compare characters ignoring case
        if (toupper(*lit) != toupper(*rit))
            return false; // Stop early if mismatch found

        // Move both iterators forward
        ++lit;
        ++rit;
    }

    // If loop completes, all characters matched
    return true;
}

// ------------------------------------------------------------
// Test helper function
// Runs both implementations on the same input and prints results
// ------------------------------------------------------------
void test(const string& str1, const string& str2) {
    cout << "Comparing: " << str1 << " and " << str2 << endl;

    // Call lambda-based version
    cout << "Lambda version: "
         << (equal_strings_lambda(str1, str2) ? "equal" : "not equal")
         << endl;

    // Call manual version
    cout << "Manual version: "
         << (equal_strings_manual(str1, str2) ? "equal" : "not equal")
         << endl;

    cout << "------------------------" << endl;
}

// ------------------------------------------------------------
// Main function: entry point of the program
// Runs several test cases to demonstrate functionality
// ------------------------------------------------------------
int main() {
    // Same word, different case → should be equal
    test("lambda", "Lambda");

    // Different words → should not be equal
    test("lambda", "lambada");

    // Another case-insensitive match
    test("Hello", "hello");

    return 0;
}
```

## Lambda functions capture
```cpp
#include <iostream>
using namespace std;

/*
====================================================
LAMBDA DEMONSTRATION PROGRAM (Single File Version)
====================================================

This program demonstrates:
1. No-capture lambda
2. Capture by value and reference
3. Mutable lambda
4. Functor vs Lambda

Each example is placed in its own function
and called from main().
*/


/*
====================================================
1. No-capture lambda
====================================================
- A lambda that does NOT use any external variables
- Syntax: []() { ... }
- Equivalent to a simple inline function
*/
void noCaptureExample() {
    cout << "\n--- No Capture Lambda ---\n";

    // Define a lambda with no parameters and no capture
    auto greet = []() {
        cout << "Hello from a no-capture lambda!\n";
    };

    // Call the lambda like a function
    greet();
}


/*
====================================================
2. Capture lambda
====================================================
- Lambdas can "capture" variables from outer scope
- Two common types:
    [x]   -> capture by VALUE (copy)
    [&x]  -> capture by REFERENCE (original variable)

Key difference:
- Value: cannot modify original variable
- Reference: CAN modify original variable
*/
void captureLambdaExample() {
    cout << "\n--- Capture Lambda ---\n";

    int x = 10; // variable in outer scope

    // Capture by VALUE (copy of x is used)
    auto byValue = [x]() {
        // x is read-only here (const by default)
        cout << "Captured by value: x = " << x << endl;
    };

    // Capture by REFERENCE (original x is used)
    auto byRef = [&x]() {
        x += 5; // modifies original variable
        cout << "Captured by reference, modified x = " << x << endl;
    };

    byValue();  // prints 10
    byRef();    // modifies x → now 15

    // Show final value after modification
    cout << "Outside lambda, x = " << x << endl;
}


/*
====================================================
3. Mutable lambda
====================================================
- By default, value-captured variables are CONST
- 'mutable' allows modifying the COPY inside lambda

IMPORTANT:
- This does NOT change the original variable
- Only the internal copy is modified
*/
void mutableLambdaExample() {
    cout << "\n--- Mutable Lambda ---\n";

    int x = 5;

    // Capture by value, but allow modification of the copy
    auto modifyCopy = [x]() mutable {
        x += 10; // modifies ONLY the copy
        cout << "Inside lambda, modified copy x = " << x << endl;
    };

    modifyCopy();

    // Original value remains unchanged
    cout << "Outside lambda, original x = " << x << endl;
}


/*
====================================================
4. Functor vs Lambda
====================================================
Functor:
- A class that overloads operator()
- Can behave like a function

Lambda:
- Short, inline alternative to functors
- Usually preferred for simple use cases
*/

// Define a functor (function object)
class Functor {
    int value; // stored value

public:
    // Constructor initializes value
    Functor(int v) : value(v) {}

    // Overload function call operator
    void operator()() {
        cout << "Functor value = " << value << endl;
    }
};

void functorExample() {
    cout << "\n--- Functor vs Lambda ---\n";

    // Using functor
    Functor f(20);
    f(); // calls operator()

    // Equivalent lambda
    int value = 20;

    auto lambda = [value]() {
        cout << "Lambda value = " << value << endl;
    };

    lambda();
}


/*
====================================================
MAIN FUNCTION
====================================================
- Entry point of the program
- Calls all examples sequentially
*/
int main() {
    cout << "Lambda Demonstration Program\n";

    // Run each example one by one
    noCaptureExample();
    captureLambdaExample();
    mutableLambdaExample();
    functorExample();

    cout << "\nAll examples executed.\n";

    return 0; // indicates successful execution
}
```

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* =========================================================
   SECTION 1: Lambda with capture by reference
   Demonstrates capturing a variable (idx) by reference
   ========================================================= */
void demo_lambda_by_ref() {
    cout << "\n=== Demo: Lambda Capture by Reference ===\n";

    vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

    int max{5}, idx{-1}; // idx tracks position

    auto res = find_if(words.begin(), words.end(),
        // Capture max by value, idx by reference
        [max, &idx](const string& str) mutable {
            ++idx;
            return str.size() > max;
        }
    );

    if (res != words.end()) {
        cout << "The first word longer than " << max << " letters is: " << *res << endl;
        cout << "Index: " << idx << endl;
    }
}


/* =========================================================
   SECTION 2: Functor equivalent of lambda
   Shows how a class can replace a lambda expression
   ========================================================= */
class is_longer_than {
private:
    const int n;
    int& idx;

public:
    is_longer_than(const int n, int& idx) : n(n), idx(idx) {}

    bool operator()(const string& str) const {
        ++idx;
        return str.size() > n;
    }
};

void demo_functor() {
    cout << "\n=== Demo: Functor (Lambda Equivalent) ===\n";

    vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

    int max{5}, idx{-1};

    auto res = find_if(words.cbegin(), words.cend(), is_longer_than(max, idx));

    if (res != words.end()) {
        cout << "The first word longer than " << max << " letters is: " << *res << endl;
        cout << "Index: " << idx << endl;
    }
}


/* =========================================================
   SECTION 3: Capturing `this` in a lambda
   Demonstrates accessing class members inside a lambda
   ========================================================= */
class Test {
    int time{10};

public:
    void countdown() {
        // Capture current object (this pointer)
        [this]() {
            if (time > 0)
                cout << time << endl;
            else if (time == 0)
                cout << "Liftoff!" << endl;

            --time;
        }(); // Immediately invoked lambda
    }
};

void demo_capture_this() {
    cout << "\n=== Demo: Capture this ===\n";

    Test test;

    // Call multiple times to simulate countdown
    for (int i = 0; i < 12; ++i) {
        test.countdown();
    }
}


/* =========================================================
   MAIN FUNCTION
   Runs all demos
   ========================================================= */
int main() {
    demo_lambda_by_ref();
    demo_functor();
    demo_capture_this();

    return 0;
}
```

## Partial evaluation
```cpp
// ==== AUTO-GENERATED MINIMAL COMPILABLE MERGE ====

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


// ==== HEADERS (INLINED) ====


// ==== SOURCES ====

// ===== BEGIN SOURCE: partial_evaluation.cc =====
#include <iostream>
#include <string>

using namespace std;

// Function which returns a lambda function
auto greeter(const string& salutation) {
	return [salutation](const string& name) { return salutation + ", "s + name; };       // The lambda function
}

int main() {
	// Store the lambda function in a variable
	auto greet = greeter("Hello"s);

	// Call the lambda function
	cout << "Greeting: " << greet("James") << endl;
	cout << "Greeting: " << greet("students") << endl;

	auto greet_formal = greeter("Good morning"s);

	// Call the lambda function
	cout << "Formal greeting: " << greet_formal("Dr Stroustrup") << endl;
}
// ===== END SOURCE: partial_evaluation.cc =====

// ===== BEGIN SOURCE: return.cc =====
#include <iostream>
#include <string>

using namespace std;

// Function which returns a lambda function
auto greeter(const string& salutation) {
	return [salutation](const string& name) { return salutation + ", "s + name; };       // The lambda function
}

/* DISABLED EXTRA MAIN
int main() {
	// Store the lambda function in a variable
	auto greet = greeter("Hello"s);

	// Call the lambda function
	cout << "Greeting: " << greet("James") << endl;
	cout << "Greeting: " << greet("students") << endl;
}
*/

// ===== END SOURCE: return.cc =====

// ===== BEGIN SOURCE: stored_lambda.cc =====
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* DISABLED EXTRA MAIN
int main() {
	vector<string> words{"a", "collection", "of", "words", "with", "varying", "lengths"};
	int max{5};

	// Save the lambda expression in a variable
	auto is_longer_than = [max](const string& str) { return str.size() > max; };

	// Pass this variable as the predicate
	auto res = find_if(words.cbegin(), words.cend(), is_longer_than);

	// Display it
	if (res != words.end()) {
		cout << R"(The first word which is more than )" << max << R"( letters long is ")";
		cout << *res << R"(")" << endl;
	}
}
*/

// ===== END SOURCE: stored_lambda.cc =====

```

## C++ 14
```cpp
#include <iostream>
#include <string>

using namespace std;

// ---- From generalized.cc ----
void run_generalized() {
    auto add_two = [y = 2](int x) { return x + y; };

    cout << "[generalized]" << endl;
    cout << "Calling add_two(2) gives " << add_two(2) << endl;
    cout << "Calling add_two(5) gives " << add_two(5) << endl;
    cout << endl;
}

// ---- From generalized_init_capture.cc ----
void run_generalized_init_capture() {
    int z = 1;
    auto add_z_plus1 = [y = z + 1](int x) { return x + y; };

    cout << "[generalized_init_capture]" << endl;
    cout << "Calling add_z_plus1(2) gives " << add_z_plus1(2) << endl;
    cout << "Calling add_z_plus1(5) gives " << add_z_plus1(5) << endl;
    cout << endl;
}

// ---- From generic.cc ----
void run_generic() {
    string str1{"Hello, "};
    string str2{"World!"};

    auto func = [](auto x, auto y) { return x + y; };

    cout << "[generic]" << endl;
    cout << "Calling func(2, 5) gives " << func(2, 5) << endl;
    cout << "Calling func(3.141, 4.2) gives " << func(3.141, 4.2) << endl;
    cout << R"(Calling func(str1, str2) gives ")" 
         << func(str1, str2) << R"(")" << endl;
    cout << endl;
}

// ---- Single main ----
int main() {
    run_generalized();
    run_generalized_init_capture();
    run_generic();

    return 0;
}
```

## Map lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{1, 2, 3, 4};

    std::vector<int> result(v.size());

    std::transform(v.begin(), v.end(), result.begin(),
        [](int x) { return x * 2; }   // lambda
    );

    for (int x : result)
        std::cout << x << " ";  // 2 4 6 8
}
```

## Filter lambda
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::vector<int> result;

    std::copy_if(v.begin(), v.end(), std::back_inserter(result),
        [](int x) { return x % 2 == 0; }   // lambda
    );

    for (int x : result)
        std::cout << x << " ";  // 2 4
}
```

## Reduce lambda
```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> v{1, 2, 3, 4};

    int sum = std::accumulate(v.begin(), v.end(), 0,
        [](int acc, int x) { return acc + x; }  // lambda
    );

    std::cout << sum << std::endl;  // 10
}
```
(c) 2026 Freek van den Berg. All rights reserved.

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
Use insert instead of emplace when you already have a fully constructed object and simply want to add it to the container, because insert clearly expresses “put this existing object here,” while emplace is intended for constructing a new object directly in-place from constructor arguments. In cases where you pass an existing object to emplace, it offers no real performance benefit and can actually reduce readability, whereas insert is also required for certain operations like inserting multiple elements, ranges, or initializer lists.

```cpp
#include <iostream>
#include <vector>

using namespace std;

// A simple class representing a refrigerator
class refrigerator {
    int temperature;   // temperature inside the fridge
    bool door_open;    // whether the door is open
    bool power_on;     // whether the fridge has power

public:
    // Constructor to initialize all fields
    refrigerator(int temp, bool open, bool power)
        : temperature(temp), door_open(open), power_on(power) {}

    // Function to print the state of the refrigerator
    void print() const {
        cout << "Temperature = " << temperature;
        cout << boolalpha; // print bools as true/false instead of 1/0
        cout << ", door_open = " << door_open;
        cout << ", power_on = " << power_on;
    }
};

// Demonstrates insert() vs emplace() with vector
void test_insert_emplace() {
    vector<refrigerator> vec;

    // Create an object first, then insert (copy happens)
    refrigerator fridge(2, false, true);
    vec.insert(vec.begin(), fridge);

    // Insert a temporary object (move may happen)
    vec.insert(vec.end(), refrigerator(3, false, true));

    // Construct object directly in-place (no extra copy)
    vec.emplace(vec.end(), 5, false, false);

    cout << "Insert / emplace test:\n";
    for (const auto& el : vec) {
        el.print();
        cout << "\n";
    }
}

// Demonstrates push_back() vs emplace_back()
void test_push_back_emplace_back() {
    vector<refrigerator> vec;

    // push_back with existing object (copy)
    refrigerator fridge(2, false, true);
    vec.push_back(fridge);

    // push_back with temporary (move may happen)
    vec.push_back(refrigerator(3, false, true));

    // Construct directly inside the vector (most efficient)
    vec.emplace_back(5, false, false);

    cout << "\nPush_back / emplace_back test:\n";
    for (const auto& el : vec) {
        el.print();
        cout << "\n";
    }
}

int main() {
    // Run both demonstrations
    test_insert_emplace();
    test_push_back_emplace_back();
    return 0;
}
```

## Tuple
```cpp
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

// Function that returns a tuple with 3 different types
tuple<double, int, string> func() {
    return {1.0, 2, "Three"s};
}

int main() {

    // --- Creating tuples ---
    // Direct initialization
    tuple<double, int, string> numbers(1.0, 2, "Three"s);

    // Using make_tuple (type is deduced automatically)
    auto numbers2{ make_tuple(1.0, 2, "Three"s) };

    // --- Accessing tuple elements ---
    // Get first element (index-based access)
    auto x = get<0>(numbers);
    cout << "First element is " << x << endl;

    // Modify second element (tuples are mutable)
    cout << "Setting second element to 3" << endl;
    get<1>(numbers) = 3;

    // Access element by type (must be unique type in tuple)
    auto i_val = get<int>(numbers);
    cout << "Value of int element is " << i_val << endl;

    // --- Unpacking tuple using tie ---
    double d;
    int i;
    string str;

    // Assign tuple values to variables
    tie(d, i, str) = numbers;
    cout << "Tuple elements are: " << d << ", " << i
         << R"(, ")" << str << R"(")" << endl;

    // --- Using function that returns a tuple ---
    tie(d, i, str) = func();
    cout << "Elements of returned tuple are: "
         << d << ", " << i
         << R"(, ")" << str << R"(")" << endl;

    // --- Working with pairs ---
    // A pair holds exactly two values
    pair<string, string> wordpair("hello", "there");

    // make_pair automatically deduces types
    auto wordpair2{ make_pair("hello"s, "there"s) };

    cout << "Pair: " << wordpair.first
         << ", " << wordpair.second << endl;

    return 0;
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# Modern C++ Libraries

## Std::array
std::array is preferred over C-style arrays because it keeps the array’s size as part of its type, making code safer and easier to use, especially when passing arrays to functions. Unlike raw arrays, it provides useful features like .size(), .at() for bounds-checked access, and compatibility with standard algorithms such as std::sort, while still having no performance overhead since it’s stored on the stack. It also supports direct copying and assignment, which C-style arrays do not. Overall, std::array gives you the efficiency of traditional arrays with the safety and convenience of modern C++.

You need to provide the 5 in std::array<int, 5> because the size is part of the type itself, not just a runtime value. This means the compiler must know the exact number of elements at compile time so it can allocate the right amount of memory and enable features like .size() and safe copying. In fact, std::array<int, 5> and std::array<int, 10> are completely different types, not just arrays of different lengths. Without specifying the size, the compiler wouldn’t know how much space to reserve or how the object should behave, so the template requires it explicitly.

```cpp
#include <iostream>
#include <array>

using namespace std;

// --------------------------------------------------
// Function for built-in C-style arrays
// - Takes pointer to first element (int*)
// - 'n' is required because size information is lost
// --------------------------------------------------
void somefunc(int *pi, int n) {
    for (int i = 0; i < n; ++i)
        cout << pi[i] << ", ";
    cout << endl;
}

// --------------------------------------------------
// Function for std::array
// - Size is part of the type (array<int, 5>)
// - Can safely use .size() and iterators
// --------------------------------------------------
void somefunc(array<int, 5> arr) {
    // Access via index
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << ", ";

    // Access via iterator
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << ", ";

    cout << endl;
}

int main() {

    // ==================================================
    // SECTION 1: Basic std::array usage
    // ==================================================
    cout << "=== Array Usage ===" << endl;

    // Declare and initialize std::array
    array<int, 5> arr {1, 2, 3, 4, 5};

    // Access element by index (no bounds checking!)
    cout << "arr[3] = " << arr[3] << endl;

    // Modify element
    arr[2] = 6;
    cout << "After assignment, arr[2] = " << arr[2] << endl;

    // Copy array (deep copy)
    array<int, 5> five_els;
    five_els = arr;

    // ==================================================
    // SECTION 2: Different ways to loop over array
    // ==================================================
    cout << "\n=== Array Loops ===" << endl;

    // Iterator-based loop
    cout << "Iterator loop: ";
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << ", ";
    cout << endl;

    // Range-based for loop (modern C++)
    cout << "Range-for loop: ";
    for (auto el : arr)
        cout << el << ", ";
    cout << endl;

    // Classic index-based loop
    cout << "Indexed loop: ";
    for (size_t i = 0; i < arr.size(); ++i)
        cout << arr[i] << ", ";
    cout << endl;

    // Show copied array
    cout << "Elements of five_els: ";
    for (auto el : five_els)
        cout << el << ", ";
    cout << endl;

    // ==================================================
    // SECTION 3: Passing arrays to functions
    // ==================================================
    cout << "\n=== Functions ===" << endl;

    // -------- Built-in array --------
    cout << "Built-in array\n";

    // C-style array
    int raw_arr[] = {1, 2, 3, 4, 5};

    // Calculate number of elements manually
    int n = sizeof(raw_arr) / sizeof(raw_arr[0]);

    // Pass pointer + size
    somefunc(raw_arr, n);

    // -------- std::array --------
    cout << "std::array\n";

    // Size is known at compile time
    array<int, 5> std_arr {1, 2, 3, 4, 5};

    // Pass directly (size is preserved)
    somefunc(std_arr);

    return 0;
}
```

## Miscellaneous Containers
A forward_list in C++ is a lightweight container from the Standard Library that implements a singly linked list, meaning each element stores a value and a pointer to the next element only, allowing traversal in one direction (forward). It is memory-efficient compared to a doubly linked list because it doesn’t store backward links, but this also means it lacks features like reverse traversal and direct access by index. Elements are typically added or removed at the front using push_front() and pop_front(), and other operations like insert_after() and erase_after() are used because you can only modify elements relative to a known position. It’s best used when you need fast insertions/removals at the beginning and don’t require random access or backward navigation.

An unordered_map in C++ is a container from the Standard Library that stores key–value pairs using a hash table, which allows for very fast average-time operations like insertion, deletion, and lookup (typically O(1)). Unlike a regular map, it does not keep elements sorted, so the order of items is unpredictable and may change. Each element is accessed using a unique key, and the container uses a hash function to determine where to store and find values efficiently. It’s ideal when you need quick access to data by key and don’t care about maintaining any specific order of elements.

```cpp
#include <iostream>
#include <forward_list>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

// ---------- forward_list helper function ----------
// Prints all elements of a forward_list
void print(const forward_list<int>& fl) {
    cout << "List elements are: ";
    for (auto node : fl)
        cout << node << ",";
    cout << endl;
}

// ---------- forward_list demo ----------
// Demonstrates basic operations on a forward_list
void demo_forward_list() {
    forward_list<int> fl;

    // Add elements to the front of the list
    // (Note: forward_list only supports push_front)
    fl.push_front(2);
    fl.push_front(4);
    fl.push_front(1);
    fl.push_front(5);
    fl.push_front(3);

    // Check if the list is empty
    cout << "fl is" << (fl.empty() ? "" : " not") << " empty" << endl;
    print(fl);

    // Sort the list (ascending order)
    cout << "\nSorting list\n";
    fl.sort();
    print(fl);

    // Insert an element AFTER a specific value (3)
    cout << "\nInserting element in list\n";
    auto three = find(fl.begin(), fl.end(), 3); // find element 3
    if (three != fl.end()) {
        fl.insert_after(three, 0); // insert 0 after 3
    }
    print(fl);

    // Remove the first element
    // erase_after(before_begin()) removes the first node
    cout << "\nRemoving first element\n";
    fl.erase_after(fl.before_begin());
    print(fl);

    // Clear all elements from the list
    cout << "\nClearing list\n";
    fl.clear();

    // Check again if empty
    cout << "fl is" << (fl.empty() ? "" : " not") << " empty" << endl;
    print(fl);
}

// ---------- map / unordered_map demo ----------
// Demonstrates difference between unordered_map and map
void demo_maps() {
    // unordered_map: NOT sorted, faster average access
    unordered_map<string, int> scores;

    // Insert key-value pairs
    scores.insert({"Graham", 78});
    scores.insert({"Grace", 66});
    scores.insert({"Hareesh", 77});

    // Print unordered_map (order is arbitrary)
    cout << "\nUnordered map\n";
    for (auto score : scores)
        cout << score.first << " has a score of " << score.second << endl;

    // map: sorted by key (alphabetically for strings)
    map<string, int> sorted_scores;

    // Copy elements from unordered_map to map
    copy(scores.begin(), scores.end(),
         inserter(sorted_scores, sorted_scores.end()));

    // Print sorted map
    cout << "\nstd::map (sorted)\n";
    for (auto score : sorted_scores)
        cout << score.first << " has a score of " << score.second << endl;
}

// ---------- main function ----------
// Entry point of the program
int main() {
    cout << "=== Forward List Demo ===\n";
    demo_forward_list(); // run forward_list example

    cout << "\n=== Map Demo ===\n";
    demo_maps(); // run map example

    return 0; // indicate successful execution
}
```

## Bind
std::bind (from the C++ Standard Library) creates a callable wrapper by taking a function and “pre-filling” some of its arguments, producing a new function with fewer parameters. You can think of it as turning a function like f(a, b) into a new function where one argument is fixed (e.g., g(a) = f(a, 42)), which is useful when passing functions into algorithms like std::count_if. It also lets you reorder arguments using placeholders like _1, _2. In modern C++, it’s often replaced by lambdas because they’re clearer, but std::bind

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

// ============================================================
// SHARED UTILITIES
// ============================================================

// Generic match with value
bool match_with_value(const string& text, const string& value) {
    return text == value;
}

// Simple match for "two"
bool match_two_simple(const string& text) {
    return text == "two";
}

// Helper to print result
void print_result(int total) {
    cout << "The vector contains " << total;
    cout << R"( occurrences of the word "two")" << endl;
}

// ============================================================
// SECTION: bind.cc (std::bind example)
// ============================================================

void test_bind() {
    cout << "[bind] Using std::bind\n";

    vector<string> texts = {"one", "two", "three", "two", "four", "two", "three"};

    // Bind second argument to "two"
    auto match_two = bind(match_with_value, _1, "two");

    int total = count_if(texts.begin(), texts.end(), match_two);

    print_result(total);
}

// ============================================================
// SECTION: bound_lambda.cc (lambda capture example)
// ============================================================

void test_bound_lambda() {
    cout << "[lambda] Using lambda with capture\n";

    vector<string> texts = {"one", "two", "three", "two", "four", "two", "three"};

    int total = count_if(
        texts.begin(),
        texts.end(),
        [value = "two"](const string& text) {
            return match_with_value(text, value);
        }
    );

    print_result(total);
}

// ============================================================
// SECTION: match.cc (simple function pointer)
// ============================================================

void test_match() {
    cout << "[match] Using simple function\n";

    vector<string> texts = {"one", "two", "three", "two", "four", "two", "three"};

    int total = count_if(texts.begin(), texts.end(), match_two_simple);

    print_result(total);
}

// ============================================================
// SECTION: match_error.cc (fixed version + explanation)
// ============================================================

void test_match_error_fixed() {
    cout << "[match_error] Demonstrating FIX for incorrect usage\n";

    vector<string> texts = {"one", "two", "three", "two", "four", "two", "three"};

    // ORIGINAL ERROR:
    // count_if(..., match("two"))
    // This CALLS match immediately instead of passing a function

    // FIX: use lambda to bind argument
    int total = count_if(
        texts.begin(),
        texts.end(),
        [](const string& text) {
            return match_with_value(text, "two");
        }
    );

    print_result(total);
}

// ============================================================
// MAIN ENTRY POINT
// ============================================================

int main() {
    cout << "=== Combined Test Program ===\n\n";

    test_bind();
    cout << "-----------------------------\n";

    test_bound_lambda();
    cout << "-----------------------------\n";

    test_match();
    cout << "-----------------------------\n";

    test_match_error_fixed();
    cout << "-----------------------------\n";

    cout << "\n=== Done ===\n";
    return 0;
}
```

## Callable objects
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;

/*
    ============================================================
    SECTION 1: BASIC MATCH FUNCTIONS
    ============================================================

    These are reusable functions that define "matching logic".
    Later, we will pass them into other functions in different ways.
*/

// Simple match function
// Returns true if the string equals "two"
bool match_simple(const string& test) {
    return test == "two";
}

// More flexible match function
// Takes an extra parameter so we can compare against any value
bool match_with_value(const string& text, const string& value) {
    return text == value;
}

/*
    ============================================================
    SECTION 2: COUNT FUNCTIONS
    ============================================================

    These functions loop through a vector of strings and count how
    many elements satisfy a given "match condition".

    The key idea:
    → We don't hardcode the condition
    → We pass it as a FUNCTION
*/


// ------------------------------------------------------------
// 2.1 FUNCTION POINTER VERSION (C-style)
// ------------------------------------------------------------
// Accepts a pointer to a function as a parameter
// Syntax: bool (*match_ptr)(const string&)
//
// Limitations:
// - Can only accept plain functions (no lambdas with captures, etc.)
// - Less flexible than modern approaches
int count_strings_fp(vector<string>& texts, bool (*match_ptr)(const string&)) {
    int tally = 0;

    // Loop through all strings
    for (auto text : texts) {
        // Call the function pointer
        if (match_ptr(text)) {
            ++tally;
        }
    }

    return tally;
}


// ------------------------------------------------------------
// 2.2 std::function VERSION (modern, flexible)
// ------------------------------------------------------------
// std::function is a wrapper that can hold:
// - function pointers
// - lambdas
// - functors
// - bind expressions
//
// Much more flexible than raw function pointers
int count_strings_func(vector<string>& texts, function<bool(const string&)> match_ptr) {
    int tally = 0;

    for (auto text : texts) {
        if (match_ptr(text)) {
            ++tally;
        }
    }

    return tally;
}


/*
    ============================================================
    SECTION 3: MAIN DEMONSTRATION
    ============================================================
*/

int main() {

    // Sample data
    vector<string> texts = {"one", "two", "three", "two", "four", "two", "three"};


    /*
        ------------------------------------------------------------
        3.1 FUNCTION POINTER
        ------------------------------------------------------------

        - Old-school C-style approach
        - We pass a function name → automatically converted to pointer
        - Only works with regular functions (no captures, no objects)
    */
    cout << "[Function Pointer] Count: ";
    cout << count_strings_fp(texts, match_simple) << endl;


    /*
        ------------------------------------------------------------
        3.2 std::function
        ------------------------------------------------------------

        - Same logic as above, but more flexible
        - std::function can wrap many callable types
    */
    cout << "[std::function] Count: ";
    cout << count_strings_func(texts, match_simple) << endl;


    /*
        ------------------------------------------------------------
        3.3 std::bind
        ------------------------------------------------------------

        Problem:
        match_with_value requires TWO parameters:
            (text, value)

        But count_strings_func expects a function that takes ONE parameter:
            (text)

        Solution:
        → Use std::bind to "fix" the second argument

        _1 = placeholder for first argument passed later
    */
    auto match_two_bind = bind(match_with_value, _1, "two");

    cout << "[std::bind] Count: ";
    cout << count_strings_func(texts, match_two_bind) << endl;


    /*
        ------------------------------------------------------------
        3.4 LAMBDA (anonymous function)
        ------------------------------------------------------------

        - Defined inline
        - No need for a separate function
        - Very common in modern C++

        Syntax:
        [] (parameters) { body }
    */
    cout << "[Lambda] Count: ";
    cout << count_strings_func(texts,
        [](const string& text) {
            return text == "two";
        }
    ) << endl;


    /*
        ------------------------------------------------------------
        3.5 LAMBDA WITH CAPTURE
        ------------------------------------------------------------

        Capture allows a lambda to "remember" external variables

        [value] → capture by value
        [&value] → capture by reference

        This is the modern replacement for std::bind in most cases
    */
    string value = "two";

    cout << "[Lambda Capture] Count: ";
    cout << count_strings_func(texts,
        [value](const string& text) {
            return match_with_value(text, value);
        }
    ) << endl;


    /*
        ============================================================
        FINAL NOTES
        ============================================================

        Best practices (modern C++):

        ✔ Prefer lambdas over std::bind
        ✔ Prefer std::function over raw function pointers when flexibility is needed
        ✔ Use function pointers only when simplicity/performance is critical

    */

    return 0;
}
```
(c) 2026 Freek van den Berg. All rights reserved.

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

## Bitsets
```cpp
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	bitset<8> b1{"10101110"};                                // Initialize from string literal - bitset with value 174
	bitset<8> b2{0xae};                                      // Initialize from integer value (decimal or hexadecimal)
	bitset<8> b3{0b1010'1110};                               // Initialize from binary constant (C++14)

	bitset<8> b4{0b010'1010};                                // Bitset with value 42

	cout << "b1 is " << b1 << endl;                          // Displays 10101110
	cout << "b4 is " << b4 << endl;                          // Displays 00101010
	cout << "b2 in decimal is " << b2.to_ulong() << endl;    // Displays 174
	cout << "b2 as a string is " << b2.to_string() << endl;  // Displays 10101110

	cout << "~b1 is " << ~b1 << endl;                        // Displays 01010001

	cout << "b1 & b4 is " <<(b1 & b4) << endl;               // Displays 00101010
	cout << "b1 | b4 is " << (b1 | b4) << endl;              // Displays 10101110
	cout << "b1 ^ b4 is " << (b1 ^ b4) << endl;              // Displays 10000100
}
```

## Various Library Features
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>

using namespace std;
using namespace std::placeholders;

/* =========================================================
   Shared helper function (used in bind/ref examples)
   ========================================================= */
void incr(int& number, int& value) {
    // Assign current value to number, then increment value
    number = value;
    ++value;
}

/* =========================================================
   Demo 1: std::bind WITHOUT std::ref (value is copied)
   ========================================================= */
void demo_bind_copy() {
    cout << "=== Demo: std::bind (copy) ===" << endl;

    int n{2};
    auto incr_n = bind(incr, _1, n); // n is copied

    vector<int> numbers(5);

    for (auto& number : numbers)
        incr_n(number);

    cout << "After call, elements are: ";
    for (auto number : numbers)
        cout << number << ", ";

    cout << "\nn = " << n << " (unchanged because it was copied)\n\n";
}

/* =========================================================
   Demo 2: std::bind WITH std::ref (reference is used)
   ========================================================= */
void demo_bind_ref() {
    cout << "=== Demo: std::bind (reference using std::ref) ===" << endl;

    int n{2};
    auto incr_n = bind(incr, _1, ref(n)); // n passed by reference

    vector<int> numbers(5);

    for (auto& number : numbers)
        incr_n(number);

    cout << "After call, elements are: ";
    for (auto number : numbers)
        cout << number << ", ";

    cout << "\nn = " << n << " (changed because it's a reference)\n\n";
}

/* =========================================================
   Demo 3: vector::data()
   ========================================================= */
void print(int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i)
        cout << arr[i] << ", ";
    cout << endl;
}

void demo_data() {
    cout << "=== Demo: vector::data() ===" << endl;

    vector<int> numbers{1, 2, 3, 4, 5};

    //data() gives you a raw pointer to the underlying contiguous array inside a std::vector.
	//This is useful when you need compatibility with APIs that expect a C-style array (int*, double*, etc.).
    print(numbers.data(), numbers.size());

    cout << endl;
}

/* =========================================================
   Demo 4: fstream usage
   ========================================================= */
void demo_fstream() {
    cout << "=== Demo: fstream ===" << endl;

    string filename = "file.txt";

    // Open file (default: input/output depending on file existence)
    fstream file(filename);

    if (!file) {
        cout << "Failed to open file.\n\n";
        return;
    }

    cout << "File opened successfully.\n\n";

    file.close();
}

/* =========================================================
   Demo 5: to_string, stoi, stod
   ========================================================= */
void demo_to_string() {
    cout << "=== Demo: to_string / stoi / stod ===" << endl;

    string hello{"Hello, "};
    string pi{to_string(3.14159)};

    hello += pi;
    cout << hello << endl;

    cout << "stoi(pi): " << stoi(pi) << endl;   // Converts to int (3)
    cout << "stod(pi): " << stod(pi) << endl;   // Converts to double

    cout << endl;
}

/* =========================================================
   Main function: runs all demos
   ========================================================= */
int main() {
    demo_bind_copy();   // bind with copied value
    demo_bind_ref();    // bind with reference
    demo_data();        // vector::data()
    demo_fstream();     // file stream
    demo_to_string();   // string conversions

    return 0;
}
```

## Random number algorithms
```cpp
// random_number_algorithms_sequential.cpp
// This program demonstrates three random-based algorithms in sequence:
// 1. Bernoulli distribution (true/false randomness)
// 2. Drunkard's walk (random movement simulation)
// 3. Shuffle algorithm (random permutation of a list)

#include <random>      // For random number generation
#include <algorithm>   // For shuffle()
#include <vector>      // For using std::vector
#include <iostream>    // For input/output
#include <string>      // For string manipulation
#include <chrono>      // For timing (delays)
#include <thread>      // For sleep_for()

using namespace std;

// Create a Mersenne Twister random number generator
// Seeded with a non-deterministic random device for better randomness
static mt19937 mt(random_device{}());


// --------------------------------------------------
// 1. Bernoulli Distribution Demo
// --------------------------------------------------
void runBernoulli() {
    cout << "\n--- Bernoulli Demo ---\n";

    // Bernoulli distribution generates true/false outcomes
    // Probability = 0.5 means 50% chance of true, 50% false
    bernoulli_distribution berni(0.5);

    // Run the experiment 5 times
    for (int i = 0; i < 5; ++i) {

        // Generate a random boolean value
        if (berni(mt)) {
            cout << "Your subjects are grateful for your wise and benevolent rule\n";
        } else {
            cout << "The peasants are revolting!\n";
        }
    }
}


// --------------------------------------------------
// 2. Drunkard Walk Demo (FINITE version)
// --------------------------------------------------
void runDrunkard() {
    cout << "\n--- Drunkard Walk Demo ---\n";

    // Random boolean to decide direction (left or right)
    bernoulli_distribution berni;

    int x = 20;            // Starting position (middle of screen)
    const int WIDTH = 40;  // Width of the "world"
    int sign = 1;          // Direction: +1 (right), -1 (left)

    // Run for a fixed number of steps so program doesn't get stuck
    for (int step = 0; step < 60; ++step) {

        // Randomly choose direction
        sign = berni(mt) ? 1 : -1;

        // Prevent moving outside boundaries
        if (x <= 1) sign = 1;
        if (x >= WIDTH) sign = -1;

        // Update position
        x += sign;

        // Print the drunkard as a dot ('.') at position x
        // Spaces are used to shift the dot horizontally
        cout << string(x, ' ') << '.'
             << string(WIDTH - x, ' ')
             << "\r" << flush;  // '\r' returns cursor to start (animation effect)

        // Pause briefly so movement is visible
        this_thread::sleep_for(80ms);
    }

    // Move to next line after animation finishes
    cout << endl;
}


// --------------------------------------------------
// 3. Shuffle Demo
// --------------------------------------------------
void runShuffle() {
    cout << "\n--- Shuffle Demo ---\n";

    // Create a vector with some numbers
    vector<int> vec{3, 1, 4, 1, 5, 9};

    // Shuffle and print the vector multiple times
    for (int i = 0; i < 5; ++i) {

        // Randomly reorder elements using the same RNG
        shuffle(vec.begin(), vec.end(), mt);

        // Print shuffled result
        for (auto v : vec)
            cout << v << " ";

        cout << endl;

        // Pause to make changes visible
        this_thread::sleep_for(500ms);
    }
}


// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main() {

    // Run all demos one after another
    runBernoulli();
    runDrunkard();
    runShuffle();

    cout << "\nAll demos completed.\n";

    return 0;
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# Move semantics

## Swap
```cpp
#include <iostream>   // For input/output (cout, endl)
#include <string>     // For std::string

using namespace std; // Avoid writing std:: everywhere

// ==========================
// Class from overload.cc
// ==========================
class BufferManager {
private:
    int size;        // Size of the buffer
    char* buffer;    // Pointer to dynamically allocated buffer

public:
    // Constructor: allocate memory based on given size
    BufferManager(int size) : size(size), buffer(new char[size]) {}

    // Destructor: free allocated memory
    ~BufferManager() { delete[] buffer; }

    // Declare custom swap as friend so it can access private members
    friend void swap(BufferManager& l, BufferManager& r) noexcept;

    // Function to print object details
    void print() {
        cout << "BufferManager with size = " << size; // Print size
        cout << ": buffer address is " << static_cast<void*>(buffer); // Print memory address
    }
};

// Custom swap function for BufferManager
inline void swap(BufferManager& l, BufferManager& r) noexcept {
    using std::swap;       // Enable std::swap (important for ADL)
    swap(l.size, r.size);  // Swap sizes
    swap(l.buffer, r.buffer); // Swap buffer pointers
}

// ==========================
// Main function (merged)
// ==========================
int main() {

    // ==========================
    // Part 1: string swapping (from member.cc)
    // ==========================
    string s1{"Hello"};    // Initialize first string
    string s2{"Goodbye"};  // Initialize second string

    // Print before swapping
    cout << "Before swapping, s1 = " << s1 << " and s2 = " << s2 << endl;

    s1.swap(s2); // Member function swap

    // Print after member swap
    cout << "After swapping, s1 = " << s1 << " and s2 = " << s2 << endl;

    swap(s1, s2); // Non-member swap (std::swap)

    // Print after another swap
    cout << "After another swap, s1 = " << s1 << " and s2 = " << s2 << endl;


    // Add spacing for clarity
    cout << "\n==========================\n\n";


    // ==========================
    // Part 2: BufferManager swapping (from overload.cc)
    // ==========================
    BufferManager a(5), b(6); // Create two objects with different sizes

    cout << "Before swapping\n";

    cout << "a is ";
    a.print(); // Print object a

    cout << endl << "b is ";
    b.print(); // Print object b

    // Perform custom swap (calls our overloaded version)
    swap(a, b);

    cout << endl << endl << "After swapping\n";

    cout << "a is ";
    a.print(); // Print swapped object a

    cout << endl << "b is ";
    b.print(); // Print swapped object b

    cout << endl;

    return 0; // End program
}
```

# Lvalues and Rvalues
An lvalue is an expression that refers to a persistent object with a specific memory location—you can take its address and it typically appears on the left side of an assignment (like a named variable int x). An rvalue, on the other hand, is a temporary value that does not have a stable memory location and usually appears on the right side of an assignment (like 5 or x + 1). The key difference is that lvalues represent objects you can modify and refer to repeatedly, while rvalues represent temporary results that are used briefly and then discarded.

```cpp
#include <iostream>                         // Provides std::cout, std::endl for console output

using namespace std;                        // Allows us to write cout instead of std::cout

// ==========================================================
// SECTION 1: LVALUE REFERENCE BASICS
// ==========================================================

void lvalue_demo() {                        // Function to demonstrate how lvalue references behave

    // int& x = 3;                          // ERROR:
                                            // 3 is an rvalue (temporary value, no memory address you can modify)
                                            // Non-const lvalue references (int&) can ONLY bind to lvalues

    const int& x = 3;                       // VALID:
                                            // const lvalue references CAN bind to rvalues
                                            // The compiler creates a temporary variable behind the scenes
                                            // and binds 'x' to it safely (read-only)

    cout << "lvalue_demo: x = " << x << endl; // Prints the value stored in the temporary (3)
}

// ==========================================================
// SECTION 2: FUNCTION OVERLOADING WITH LVALUES & RVALUES
// ==========================================================

class Test { };                              // Simple empty class (no members needed for this demo)

// -------- Different overloads depending on value category --------

// 1. Non-const lvalue reference
void func(Test& test) {
    cout << "lvalue argument\n";             // Called when passing a modifiable named object (lvalue)
}

// 2. Const lvalue reference
void func(const Test& test) {
    cout << "const lvalue argument\n";       // Called when passing const objects OR when no better match exists
}

// 3. Rvalue reference
void func(Test&& test) {
    cout << "rvalue argument\n";             // Called when passing temporary objects (rvalues)
}

void overload_demo() {
    Test test;                               // 'test' is an lvalue (it has a name and memory location)
    const Test ctest;                        // 'ctest' is a const lvalue (cannot be modified)

    cout << "Calling func(test): ";
    func(test);                              // Matches Test& (best match: non-const lvalue reference)

    cout << "Calling func(ctest): ";
    func(ctest);                             // Matches const Test&
                                             // Cannot bind to Test& because object is const

    cout << "Calling func(Test()): ";
    func(Test());                            // Test() creates a temporary object → rvalue
                                             // Matches Test&& (rvalue reference)

    // IMPORTANT NOTE:
    // If the rvalue overload (Test&&) didn't exist,
    // the const Test& version would accept the rvalue instead.
}

// ==========================================================
// SECTION 3: RVALUE REFERENCES
// ==========================================================

void rvalue_ref_demo() {
    int y{2};                                // 'y' is an lvalue (named variable)

    // func(y);                              // If func expects int&&, this fails:
                                             // rvalue references (int&&) cannot bind to lvalues directly

    // Lambda function that accepts an rvalue reference
    auto func_int = [](int&& x) {             // 'x' is an rvalue reference parameter
        cout << "rvalue_ref_demo: x = " << x << endl;
    };

    func_int(2);                             // 2 is an rvalue → perfectly matches int&&

    // IMPORTANT CONCEPT:
    // Even though 'x' is declared as int&&,
    // INSIDE the function it becomes an lvalue (because it has a name!)
}

// ==========================================================
// MAIN FUNCTION (PROGRAM ENTRY POINT)
// ==========================================================

int main() {

    cout << "=== Lvalue Demo ===\n";
    lvalue_demo();                           // Demonstrates binding rules for lvalue references

    cout << "\n=== Overload Demo ===\n";
    overload_demo();                         // Shows how C++ chooses function overloads

    cout << "\n=== Rvalue Ref Demo ===\n";
    rvalue_ref_demo();                       // Demonstrates rvalue reference usage

    return 0;                                // Indicates successful execution
}
```

## Move operators (Copy constructor, move constructor, copy assignmen operator, move assignment operator)
In C++, the copy constructor and copy assignment operator create or update objects by duplicating data from another existing object (an lvalue), while the move constructor and move assignment operator improve efficiency by transferring resources from temporary or explicitly moved objects (rvalues) instead of copying them; the copy constructor is used when a new object is initialized from another, whereas the copy assignment operator is used when an already existing object is assigned new values, and similarly, the move constructor initializes a new object by “stealing” resources (like memory) from a temporary object, while the move assignment operator replaces the contents of an existing object by taking over those resources, leaving the source object in a valid but typically empty state—this distinction is crucial for performance, especially when working with large or resource-heavy objects.
```cpp
#include <iostream>              // Include input-output stream library

using namespace std;             // Avoid writing std:: everywhere

class MyClass {};                // Empty helper class (used as a member)

// Class demonstrating copy & move semantics
class Test {
  private:
    int i{0};                   // Integer member initialized to 0
    MyClass m;                  // Object of MyClass

  public:
    Test() = default;           // Default constructor (compiler-generated)

    // Copy constructor
    Test(const Test& other)     // Takes const reference to another Test object
        : i(other.i),           // Copy integer value
          m(other.m)            // Copy MyClass object
    {
        cout << "Copy constructor called" << endl; // Debug message
    }

    // Move constructor
    Test(Test&& other) noexcept // Takes rvalue reference (temporary object)
        : i(other.i),           // BUG FIXED: should copy from other.i (original had i(i))
          m(std::move(other.m)) // Move MyClass object instead of copying
    {
        cout << "Move constructor called" << endl; // Debug message
    }

    // Copy assignment operator
    Test& operator=(const Test& other) {   // Assign from lvalue
        cout << "Copy assignment operator called" << endl;

        if (this != &other) {              // Avoid self-assignment
            i = other.i;                  // Copy integer
            m = other.m;                 // Copy object
        }
        return *this;                     // Return current object
    }

    // Move assignment operator
    Test& operator=(Test&& other) noexcept { // Assign from rvalue
        cout << "Move assignment operator called" << endl;

        if (this != &other) {              // Avoid self-assignment
            i = other.i;                  // Transfer integer value
            m = std::move(other.m);       // Move object instead of copying
        }
        return *this;                     // Return current object
    }
};

int main() {
    Test test;                            // Default constructor

    cout << "Copying: ";
    Test test2 = test;                    // Calls copy constructor

    cout << "Moving temporary: ";
    Test test3 = Test();                  // Temporary → move constructor

    cout << "Moving rvalue ref: ";
    Test test4(std::move(test));          // Explicit move using std::move

    cout << endl;

    Test test5;
    cout << "Assigning: ";
    test5 = test;                         // Copy assignment

    Test test6;
    cout << "Assigning from temporary: ";
    test6 = Test();                       // Move assignment
}
```

## Move-only types and RAII
std::move is a C++ utility that casts an object to an rvalue reference, signaling that its resources can be safely “moved” rather than copied; it doesn’t move anything by itself, but enables move constructors or move assignment operators to transfer ownership of internal data (like dynamically allocated memory) from one object to another, making the operation much faster than copying—after this, the original object remains valid but in an unspecified (often empty) state and shouldn’t be relied on for its previous value.

```cpp
#include <iostream>   // For input/output (std::cout, std::endl)
#include <vector>     // For std::vector container
#include <string>     // For std::string type

using namespace std;  // Avoid writing std:: everywhere (not recommended in large projects)

int main() {  // Entry point of the program

    vector<string> strings(5);  // Create a vector of 5 empty strings

    cout << "Capture by reference" << endl;  // Print header

    // Lambda capturing 'strings' by reference
    [&strings]() {  // Capture 'strings' by reference so we access the original vector
        cout << "Count in lambda = " << strings.size() << endl;  // Print size inside lambda
    }();  // Immediately invoke the lambda

    cout << endl << "After calling lambda, count = " << strings.size() << endl;  
    // Print size again outside lambda (should be unchanged)

    cout << endl << "Capture by move" << endl;  // Print header for move example

    // Lambda capturing 'strings' by move
    [vs = std::move(strings)]() {  // Move 'strings' into 'vs' (lambda owns it now)
        cout << "Count in lambda = " << vs.size() << endl;  // Print size of moved data
    }();  // Immediately invoke the lambda

    cout << endl << "After calling lambda, count = " << strings.size() << endl << endl;  
    // Print size of original vector after move (likely 0 or unspecified but valid)

}  
```

## Forwarding references
This merged C++ program demonstrates how references behave and how template forwarding works: it first shows reference collapsing, where a reference to a reference (int_ref&) ultimately behaves as a single lvalue reference, allowing variables like rr to safely refer to i, and then contrasts this with a template function using a forwarding (universal) reference (T&&), which adapts based on the argument type—deducing T as an lvalue reference when given lvalues and as a non-reference type for rvalues (like when using std::move), illustrating how C++ preserves value categories during template argument deduction.

```cpp
#include <iostream>          // Include input-output stream library
#include <utility>           // Include for std::move

using namespace std;         // Use standard namespace

// ----------- Part 1: Reference behavior -----------

// Function taking an lvalue reference to int
void func_ref(int& x) {      
    cout << "func_ref called with argument int&" << endl; // Print message
}

// ----------- Part 2: Template forwarding reference -----------

// Simple class for demonstration
class Test {};               

// Template function using forwarding (universal) reference
template <class T>
void func_forward(T&& x) {   
    cout << "func_forward called" << endl; // Print message
}

// ----------- Main function -----------

int main() {

    // ----------- Reference collapsing demo -----------

    // int& & x = y;         // INVALID: reference to reference (not allowed directly)

    using int_ref = int&;    // Alias: int_ref is a reference to int

    int i{99};               // Declare integer i with value 99
    int_ref j{i};            // j is a reference to i
    int_ref& rr{j};          // rr is a reference to j (reference collapsing happens)

    func_ref(rr);            // Call function with reference

    // ----------- Forwarding reference demo -----------

    Test test;               // Create Test object
    Test& rtest{test};       // Create reference to Test object

    func_forward(test);      // Pass lvalue → T deduced as Test&
    func_forward(rtest);     // Pass lvalue reference → still lvalue
    func_forward(std::move(test)); // Pass rvalue → T deduced as Test

    return 0;                // End program
}
```

## Perfect forwarding
This single C++ program demonstrates perfect forwarding by defining three overloaded versions of a function g that handle a modifiable lvalue, a const lvalue, and an rvalue, respectively. A template function f takes a forwarding reference (T&&) and passes its argument to g using std::forward, which preserves whether the original argument was an lvalue or rvalue. In main, different kinds of arguments—regular objects, const objects, and moved objects—are passed to f, showing how the correct overload of g is selected each time. Overall, it illustrates how C++ templates can maintain the exact nature of arguments, avoiding unnecessary copies and enabling efficient, flexible code.

```cpp
#include <iostream>              // Include standard input/output library
#include <utility>               // Required for std::forward and std::move

using namespace std;             // Avoid writing std:: repeatedly

class X { };                     // Simple empty class used for demonstration

// Function overload for modifiable lvalue reference
void g(X& x) {
    std::cout << "Modifiable version of g\n"; // Called when argument is non-const lvalue
}

// Function overload for const lvalue reference
void g(const X& x) {
    std::cout << "Immutable version of g\n";  // Called when argument is const lvalue
}

// Function overload for rvalue reference
void g(X&& x) {
    std::cout << "Move version of g\n";       // Called when argument is rvalue (temporary or moved)
}

// Template function using perfect forwarding
template <class T>
void f(T&& x) {                               // T&& is a forwarding (universal) reference
    g(std::forward<T>(x));                    // Forward x preserving its value category (lvalue/rvalue)
}

int main() {
    X x;                                      // Create a normal (modifiable) object
    const X cx;                               // Create a const object

    cout << "Lvalue\n";                       // Label output
    f(x);                                     // Pass lvalue → calls g(X&)

    cout << "Const lvalue\n";                 // Label output
    f(cx);                                    // Pass const lvalue → calls g(const X&)

    cout << "Rvalue\n";                       // Label output
    f(std::move(x));                          // Convert x to rvalue → calls g(X&&)

    return 0;                                 // End of program
}
```
(c) 2026 Freek van den Berg. All rights reserved.

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
(c) 2026 Freek van den Berg. All rights reserved.

# Smart pointers
A smart pointer is an object in languages like C++ that behaves like a regular pointer but also manages the lifetime of dynamically allocated memory automatically, helping prevent leaks and dangling pointers. Instead of requiring the programmer to manually delete memory, smart pointers use techniques like RAII (Resource Acquisition Is Initialization) to ensure resources are released when the pointer goes out of scope. Common types include std::unique_ptr for exclusive ownership, std::shared_ptr for shared ownership with reference counting, and std::weak_ptr for non-owning references that avoid circular dependencies. By encapsulating memory management logic, smart pointers make code safer, cleaner, and less error-prone.

In C++, std::unique_ptr, std::shared_ptr, and std::weak_ptr are smart pointers that differ mainly in how they manage ownership of dynamically allocated objects: std::unique_ptr provides exclusive ownership, meaning only one pointer can own the object at a time and it cannot be copied (only moved), making it lightweight and efficient; std::shared_ptr allows multiple owners of the same object using reference counting, and the object is automatically deleted when the last shared pointer releases it, though this adds some overhead and can lead to memory leaks if circular references occur; std::weak_ptr is a non-owning observer used alongside shared_ptr, meaning it does not contribute to the reference count and is primarily used to safely access shared objects without preventing their deletion, especially useful for breaking cyclic dependencies.

## Unique pointer
```cpp
#include <iostream>     // For input/output (cout, endl)
#include <memory>       // For smart pointers like unique_ptr

using namespace std;    // Avoid writing std:: repeatedly

// ==========================
// Shared data structure
// ==========================

// Data structure representing a point on the screen
struct point {
    int x;              // x-coordinate
    int y;              // y-coordinate
};

// ==========================
// Factory function example
// ==========================

// Function that creates and returns a unique_ptr to a point
unique_ptr<point> point_ptr(int x, int y) { 
    point p{0};                         // Create a local point instance (initialized to 0)
    p.x = x;                            // Assign x value
    p.y = y;                            // Assign y value
    
    // Create a unique_ptr managing a copy of p
    unique_ptr<point> ptr{ make_unique<point>(p) };
    
    return ptr;                         // Return ownership (move happens automatically)
}

// ==========================
// Demo: basic unique_ptr usage
// ==========================
void demo_example() {
    // Create a unique_ptr to a point initialized with {3, 6}
    auto p{ make_unique<point>( point{3, 6} ) };

    // Access members using -> (like a normal pointer)
    cout << "Example: " << p->x << ", " << p->y << endl;
}

// ==========================
// Demo: factory function usage
// ==========================
void demo_factory() {
    // Call factory function to get a unique_ptr
    auto upp { point_ptr(3, 6) };

    // Print values stored in the point
    cout << "Factory: " << upp->x << ", " << upp->y << endl;
}

// ==========================
// Demo: initialization styles
// ==========================
void demo_init() {
    // Allocate a single int with value 42
    unique_ptr<int> p1{ new int(42) };      // C++11 style (manual new)

    // Allocate array of 6 ints
    unique_ptr<int []> p2{ new int[6] };    // Array version of unique_ptr

    // Preferred modern way (C++14+)
    auto p3{ make_unique<int>(42) };        // Safer and cleaner
    auto p4{ make_unique<int []>(6) };      // Array version

    // Access values
    cout << "Init p1: " << *p1 << endl;     // Dereference single object
    cout << "Init p2[0]: " << p2[0] << endl;// Access array element

    // Transfer ownership using move
    unique_ptr<int> p5(std::move(p3));      // p3 becomes nullptr after move

    // NOTE: p4 cannot be moved into unique_ptr<int> (different type)
}

// ==========================
// Main function
// ==========================
int main() {

    demo_example();     // Run first demo
    demo_factory();     // Run factory demo
    demo_init();        // Run initialization demo

    return 0;           // Indicate successful execution
}
```

## Unique pointer appications
```cpp
#include <iostream>      // Provides std::cout for console output
#include <memory>        // Provides smart pointers like std::unique_ptr

/// ===== Simulated C-style Networking API =====
struct destination { /* Represents a remote endpoint (details omitted) */ };

struct connection { /* Represents an active connection (details omitted) */ };

// Opens a connection to a destination and returns it by value
connection connect(destination dest) {
    std::cout << "Connecting\n";   // Log that a connection is being established
    connection conn;               // Create a connection object
    return conn;                   // Return it (copy or move)
}

// Closes a connection
void disconnect(connection conn) {
    std::cout << "Disconnecting\n"; // Log that the connection is closing
}
/// ===== End of C-style API =====


// --- Example 1: Incorrect use of std::unique_ptr ---
void get_data_bad(const destination& dest) {
    connection conn = connect(dest);     // Create a connection on the stack

    // PROBLEM:
    // unique_ptr assumes ownership of a heap-allocated object.
    // Here we pass the address of a stack variable → leads to undefined behavior
    // when unique_ptr tries to delete it.
    std::unique_ptr<connection> ptr(&conn);

    std::cout << "Getting data...\n";    // Simulate work
}   // ptr goes out of scope → tries to delete stack memory →  BUG


// --- Example 2: Custom deleter (still problematic design) ---

// Lambda that defines how to properly "close" a connection
auto end_connection = [](connection* conn) {
    disconnect(*conn);  // Call API cleanup function
};

void get_data_custom_deleter(const destination& d) {
    connection conn = connect(d);   // Stack-allocated connection

    // Uses unique_ptr with a custom deleter
    // This avoids calling delete, but still manages a stack object → risky design
    std::unique_ptr<connection, decltype(end_connection)> p(&conn, end_connection);

    std::cout << "Getting data...\n";  // Simulate work
}   // Calls end_connection, but does NOT delete memory (safe-ish but awkward)


// --- Example 3: Proper use of polymorphism with unique_ptr ---

#include <vector>   // Needed for std::vector

using namespace std;  // Avoids std:: prefix (not recommended in headers, okay in examples)

// Abstract base class
class Shape {
public:
    virtual void draw() = 0;        // Pure virtual function → must be implemented
    virtual ~Shape() = default;     // Virtual destructor for safe polymorphic deletion
};

// Derived class: Circle
class Circle : public Shape {
public:
    void draw() override {          // Override base class method
        cout << "I'm a Circle!\n";  // Print shape type
    }
};

// Derived class: Triangle
class Triangle : public Shape {
public:
    void draw() override {
        cout << "I'm a Triangle!\n";
    }
};

// Derived class: Square
class Square : public Shape {
public:
    void draw() override {
        cout << "I'm a Square!\n";
    }
};


// --- Main demonstrating correct modern C++ usage ---
int main() {
    destination dest;   // Create a destination object

    // Demonstrate problematic patterns (for learning only)
    get_data_bad(dest);               //  Undefined behavior
    get_data_custom_deleter(dest);    //  Works but not ideal design

    // Correct usage of unique_ptr with polymorphism
    vector<unique_ptr<Shape>> shapes;  // Vector of owning smart pointers

    // Create objects safely on heap and transfer ownership into vector
    shapes.emplace_back(make_unique<Circle>());
    shapes.emplace_back(make_unique<Triangle>());
    shapes.emplace_back(make_unique<Square>());

    // Iterate and call virtual function → runtime polymorphism
    for (auto& it : shapes)
        it->draw();

    return 0;  // Indicate successful execution
}
```

## Interface/Implementation Separation
```cpp
#include <iostream>              // for std::cout
#include <memory>                // for std::unique_ptr

// ===================== Date (formerly Date.h) =====================

// Concrete implementation class (hidden in pImpl normally)
class Date {
    int day;                    // stores day
    int month;                  // stores month
    int year;                   // stores year

public:
    // Constructor initializes all members
    Date(int day, int month, int year) : day(day), month(month), year(year) {}

    // Setter for day
    void set_day(int d) { 
        day = d;                // assign new day
    }

    // Print date in DD/MM/YYYY format
    void print() { 
        std::cout << day << "/" << month << "/" << year; // output formatted date
    }
};

// ===================== Handle (formerly Handle.h + Handle.cpp) =====================

// Forward declaration is not needed anymore since Date is above,
// but kept conceptually for pImpl understanding
// class Date;

// Handle class using pImpl idiom
class Handle {
    std::unique_ptr<Date> body; // pointer to implementation (Date)

public:
    // Constructor: creates the hidden implementation
    Handle(int day, int month, int year) {
        body = std::make_unique<Date>(day, month, year); // allocate Date safely
    }

    // Destructor (default is enough because unique_ptr cleans up)
    ~Handle() = default;

    // Move constructor (defaulted for efficiency)
    Handle(Handle&&) noexcept = default;

    // Move assignment operator (defaulted)
    Handle& operator=(Handle&&) noexcept = default;

    // Forward set_day to implementation
    void set_day(int day) {
        body->set_day(day);     // delegate to Date
    }

    // Forward print to implementation
    void print() {
        body->print();          // delegate to Date
    }
};

// ===================== Client (formerly Client.cpp) =====================

int main() {
    // Date date(16, 11, 2019); // direct usage (commented out in original)

    Handle date(16, 11, 2019); // create Handle object (pImpl wrapper)

    date.print();              // print initial date
    std::cout << "\n";         // newline

    date.set_day(17);          // modify day through Handle

    date.print();              // print updated date
    std::cout << "\n";         // newline

    return 0;                  // successful execution
}
```

## Shared pointer
```cpp
#include <iostream>   // Includes input/output stream library for cout
#include <memory>     // Includes smart pointers like shared_ptr

using namespace std;  // Allows using standard library names without std:: prefix

int main() {
    // Create a shared_ptr that manages an int initialized to 36
    auto ptr{make_shared<int>(36)};
    
    // Print the value pointed to by ptr
    cout << "shared_ptr's data is " << *ptr << endl;
    
    // Copy the shared_ptr (both ptr and ptr2 now share ownership)
    auto ptr2 = ptr;
    
    // Print the value again (same underlying data)
    cout << "Copied shared_ptr's data is " << *ptr << endl;
    
    // Declare an empty shared_ptr
    shared_ptr<int> ptr3;
    
    // Assign ptr to ptr3 (now ptr, ptr2, and ptr3 share ownership)
    ptr3 = ptr;
    
    // Print the value again
    cout << "Assigned shared_ptr's data is " << *ptr << endl;
}
```

## Weak pointer
```cpp
#include <iostream>   // for std::cout, std::endl
#include <memory>     // for std::shared_ptr, std::weak_ptr, std::make_shared

using namespace std;  // avoid writing std:: repeatedly (not recommended in large projects)

int main() {

    // Create a shared_ptr that owns an integer with value 36
    auto ptr{make_shared<int>(36)};   // reference count = 1

    // Print the value stored in shared_ptr
    cout << "shared_ptr's data is " << *ptr << endl;

    // Create a weak_ptr that observes ptr (does NOT increase reference count)
    weak_ptr<int> wptr = ptr;         // reference count still = 1

    // Reset ptr, destroying the managed object (since ref count goes to 0)
    ptr = nullptr;                   // object deleted, wptr becomes expired

    // Try to convert weak_ptr back to shared_ptr safely
    shared_ptr<int> sp1 = wptr.lock();  // lock() returns nullptr if object is gone

    // Check if the object is still valid
    if (sp1) {                         // true if object still exists
        cout << "shared_ptr's data is " << *sp1 << endl;
    }
    else {
        cout << "shared_ptr not available" << endl;  // expected path here
    }

    // Attempt to directly construct shared_ptr from weak_ptr
    // This will throw std::bad_weak_ptr if the object is already destroyed
    shared_ptr<int> sp2(wptr);        // unsafe if expired!

    return 0;                         // indicate successful program execution
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# Compile time programming

## Variadic Templates
```cpp
#include <iostream>   // for std::cout, std::ostream
#include <string>     // for std::string
#include <tuple>      // for std::tuple, std::make_tuple

using namespace std;  // avoid writing std:: everywhere (for simplicity)


// =========================
// SECTION 1: EXPAND EXAMPLE
// =========================

// Variadic template function (accepts any number of arguments)
template <typename... Args>                     // Args = parameter pack (types)
void expand_func(Args... args) {                // args = parameter pack (values)
    auto arg_tuple = make_tuple(args...);       // pack all arguments into a tuple
}


// =========================
// SECTION 2: PRINT EXAMPLE
// =========================

// Base case (non-variadic) - stops recursion
template <typename T>
ostream& print(ostream& os, const T& t) {
    return os << t;                             // print last element
}

// Recursive variadic function
template <typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args&... args) {
    os << t << ", ";                            // print current element
    return print(os, args...);                  // recursive call with remaining args
}


// =========================
// SECTION 3: PROCESS EXAMPLE
// =========================

// Base case (single argument)
template <typename T>
void process_func(T t) {
    cout << "Non-variadic template\n";          // indicates recursion end
    cout << "Processing argument " << t << endl;
}

// Variadic version
template <typename T, typename... Args>
void process_func(T t, Args... args) {
    size_t n_args = sizeof...(args) + 1;        // count total arguments
    cout << "Variadic template: compiler deduced "
         << n_args << " argument(s)\n";
    cout << "Processing argument " << t << endl;

    process_func(args...);                      // recursive call with remaining args
}


// =========================
// SECTION 4: SIZEOF EXAMPLE
// =========================

// Variadic template showing sizeof...
template <typename... Args>
void sizeof_func(Args... args) {
    cout << "Compiler deduced call with "
         << sizeof...(args)                    // number of arguments
         << " argument(s)\n";
}


// =========================
// MAIN FUNCTION
// =========================

int main() {

    int i{42};                                 // integer variable
    double d{0.0};                             // double variable
    string s{"text"};                           // string variable


    // ---- EXPAND EXAMPLE ----
    expand_func(s);                             // single argument
    expand_func(i, d, s);                       // multiple arguments


    cout << "\n--- PRINT EXAMPLE ---\n";
    print(cout, 2, 4.6, "Hello") << endl;       // prints all values


    cout << "\n--- PROCESS EXAMPLE ---\n";
    process_func(s);                            // single argument
    process_func(i, d, s);                      // multiple arguments


    cout << "\n--- SIZEOF EXAMPLE ---\n";
    sizeof_func(s);                             // 1 argument
    sizeof_func(i, d, s);                       // 3 arguments


    return 0;                                   // program ends successfully
}
```

## Various Template Functions
In C++, the extern keyword is used to declare a variable or function that is defined in another translation unit (source file), allowing multiple files to share the same entity without creating duplicate definitions; for example, writing extern int x; in a header tells the compiler that x exists elsewhere, while exactly one source file must contain the actual definition int x = 5;, otherwise you’ll get linker errors, and although functions are implicitly extern by default, extern becomes especially useful with global variables and advanced cases like extern template, where it prevents redundant template instantiations across files, reducing compile time and binary size.

Template bloat in C++ refers to the increase in binary size and compile time caused by templates being instantiated multiple times for different types (and sometimes redundantly across translation units), since the compiler generates separate copies of the same template code for each type it’s used with—e.g., vector<int>, vector<double>, etc.—which can lead to large executables and slower builds; this can be mitigated using techniques like extern template to centralize instantiations, reducing unnecessary duplication, or by limiting template usage in widely included headers.

See also: [misc_template_features](./misc_template_features)

```cpp
// ==============================
// Combined single C++ file
// Merged from misc_template_features
// ==============================

#include <iostream>          // for std::cout
#include <typeinfo>          // for typeid
#include <cassert>           // for static_assert alternative

// ==============================
// extern_template.h (merged)
// ==============================

// Template declaration for a generic function
template <typename T>
void func(T value); // declaration only

// Explicit extern template declarations (avoid multiple instantiations)
extern template void func<int>(int);     // tell compiler: defined elsewhere
extern template void func<double>(double);

// ==============================
// extern_template_impls.cc (merged)
// ==============================

// Actual template definition
template <typename T>
void func(T value) {                     // define template
    std::cout << "Value: " << value      // print value
              << " type: "               // print type label
              << typeid(T).name()       // runtime type info
              << std::endl;             // newline
}

// Explicit instantiations (force generation here)
template void func<int>(int);            // generate int version
template void func<double>(double);     // generate double version

// ==============================
// extern_template1.cc (merged)
// ==============================

void use_func_int() {                   // function using int specialization
    func<int>(42);                     // call template with int
}

// ==============================
// extern_template2.cc (merged)
// ==============================

void use_func_double() {               // function using double specialization
    func<double>(3.14);                // call template with double
}

// ==============================
// extern_int1.cc (merged)
// ==============================

// Declare external integer
extern int shared_int;                 // defined elsewhere

void increment_int() {                 // function increments shared int
    shared_int++;                     // increase value
}

// ==============================
// extern_int2.cc (merged)
// ==============================

void print_int() {                     // function prints shared int
    std::cout << "shared_int = "      // label
              << shared_int           // value
              << std::endl;           // newline
}

// ==============================
// extern_int_impls.cc (merged)
// ==============================

// Define the shared integer
int shared_int = 0;                   // initialize global variable

// ==============================
// static_assert.cc (merged)
// ==============================

// Compile-time assertion example
static_assert(sizeof(int) >= 4,       // check int size
              "int must be at least 4 bytes"); // error message

// ==============================
// Main function (added)
// ==============================

int main() {                          // program entry point

    // --- Test extern template ---
    use_func_int();                   // call int version
    use_func_double();                // call double version

    // --- Test extern int ---
    print_int();                      // print initial value
    increment_int();                  // increment
    print_int();                      // print updated value

    return 0;                         // successful exit
}
```

## Constant expression
const and constexpr both create immutable values in C++, but they differ in when the value must be known: const means a variable cannot be changed after initialization, yet its value can be determined at runtime (e.g., from user input), while constexpr requires the value to be fully known and evaluated at compile time, making it suitable for contexts like array sizes, template parameters, and compile-time computations; in short, const is about read-only, whereas constexpr is about compile-time constant with stronger guarantees.

```cpp
#include <iostream>              // Include input/output stream library

using namespace std;             // Use standard namespace to avoid std:: prefix

int main() {                     // Entry point of the program
    int x, y;                   // Declare two integer variables (not constant yet)

    cout << "Enter i: ";        // Prompt user to enter value for i
    cin >> x;                   // Read user input into variable x

    cout << "\nEnter j: ";      // Prompt user to enter value for j
    cin >> y;                   // Read user input into variable y

    const int i{x}, j{y};       // Define constants i and j initialized with x and y
                                // These are now constant expressions

    int arr[i + j];             // Declare array with size (i + j)
                                // Array size must be a constant expression (in standard C++ this is NOT strictly valid unless compiler supports VLAs)

    return 0;                   // End of program
}
```

### Constexpr functions
constexpr in C++ allows computations to be performed at compile time rather than at runtime, which can significantly improve performance by eliminating repeated calculations and enabling better compiler optimizations. It also increases code safety by enforcing that certain values remain constant and valid during compilation, catching errors earlier instead of at runtime. Additionally, constexpr makes code more expressive and self-documenting by clearly indicating which functions and variables are intended to be constant expressions, while still allowing them to fall back to runtime evaluation when necessary, giving developers both efficiency and flexibility.

```cpp
// Define a constexpr function that converts miles to kilometers
constexpr double miles_to_km(double miles) { 
    return miles * 1.602; // Multiply miles by conversion factor to get kilometers
}

// const return value expected - evaluated at compile time
const double dist2 = miles_to_km(40); 
// Since input is a constant literal, this is computed at compile time

// Non-const return value expected - evaluated at runtime
double dist1 = miles_to_km(40); 
// Even though input is constant, result is stored in non-const variable → runtime evaluation allowed

// Declare a non-const variable initialized at runtime
double dist3{40}; 
// This value is NOT a compile-time constant

// constexpr return value but non-const argument - error
constexpr double dist4 = miles_to_km(dist3);  
// ERROR: dist3 is not a constant expression, so this cannot be evaluated at compile time
```

```cpp
    const size_t len = str.size() // ok - value of len cannot be changed after initialization
    constexpr size_t len = str.size() // Error - value not known at compile time
```

## Template type deduction
```cpp
#include <iostream>              // Include input-output stream library for cout, endl

using namespace std;             // Use standard namespace to avoid std:: prefix

// Function template for finding maximum of two values
template <class T>               // Define a template with a generic type T
T Max(const T& t1, const T& t2)  // Function takes two const references of type T and returns T
{
    if (t1 > t2)                 // Compare first value with second
        return t1;               // Return first value if it's greater
    return t2;                   // Otherwise return second value
}

int main() {                     // Entry point of the program

    cout << Max(7.0, 2.6)        // Call Max with double values (template deduced as double)
         << endl;                // Print result and move to new line

    /*
    The compiler generates (instantiates) this function automatically:

    double Max(const double& t1, const double& t2) {   // Specialized version for double
        if (t1 > t2)                                   // Compare values
            return t1;                                 // Return larger value
        return t2;                                     // Return other value if not larger
    }
    */

    return 0;                   // Indicate successful program execution
}
```

## Auto type deduction
decltype in C++ is a keyword that inspects an expression and yields its exact type without evaluating the expression, making it useful when you want precise type deduction rather than the simplified rules used by auto. Unlike auto, which may drop references and const qualifiers, decltype preserves them: for example, if you write int x = 5; decltype(x) a = x; then a is int, but decltype((x)) b = x; makes b an int& because (x) is an lvalue expression. It’s commonly used in templates and generic code, especially when the type depends on an expression (e.g., decltype(a + b)), or when you want to declare a variable or return type that exactly matches another expression’s type.

```cpp
#include <iostream>
#include <vector>

int main() {
    // Basic auto usage
    auto x = 10;        // int
    auto y = 3.14;      // double
    auto z = 'A';       // char

    // Expressions
    auto sum = x + y;   // double

    // Containers
    std::vector<int> nums = {1, 2, 3, 4};

    // Iterator with auto
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Range-based loop
    for (auto n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // References
    auto& ref = x;  // reference to x
    ref = 20;

    // const behavior
    const int a = 42;
    auto normal = a;        // int (const dropped)
    const auto constant = a; // const int

    // decltype
    decltype(x + y) result = x + y;  // double

    // Output everything
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
    std::cout << "sum: " << sum << std::endl;
    std::cout << "result: " << result << std::endl;
    std::cout << "normal: " << normal << std::endl;
    std::cout << "constant: " << constant << std::endl;

    return 0;
}
```
# C++ 17 Highlights

## Constructors and argument deduction
```cpp
#include <iostream>        // for std::cout
#include <tuple>           // for std::tuple
#include <mutex>           // for std::mutex, std::lock_guard
#include <vector>          // for std::vector
#include <array>           // for std::array
#include <string>          // for std::string

using namespace std::literals; // enables "text"s string literal

std::mutex global_mtx;     // global mutex for demonstration

// ---------- TEMPLATE CLASS EXAMPLE (older.cc merged) ----------
template <typename T>      // define a template with type T
class Test {
public:
    Test(T t) {}           // constructor taking a value of type T
    // ... (other members could go here)
};

// ---------- PRINT FUNCTIONS (nested.cc merged) ----------

// print a 1D vector
void print(const std::vector<int>& vec)
{
    std::cout << "1 dimensional vector: "; // label output
    for (auto v : vec)                    // iterate over elements
        std::cout << v << ", ";           // print each element
    std::cout << '\n';                    // newline
}

// print a 2D vector
void print(const std::vector<std::vector<int>>& vec)
{
    std::cout << "2 dimensional vector:\n"; // label output
    int n = 0;                              // row counter
    for (auto vi : vec) {                   // iterate rows
        std::cout << "Row " << ++n << ": "; // print row number
        for (auto v : vi) {                 // iterate columns
            std::cout << v << ", ";         // print element
        }
        std::cout << '\n';                  // newline after each row
    }
}

// ---------- MAIN FUNCTION ----------
int main()
{
    // ----- Class Template Argument Deduction (deduced.cc) -----

    std::pair pr(1, 3.142); // deduced as std::pair<int, double>
    std::cout << "Pair elements: " << pr.first << ", " << pr.second << "\n";

    std::tuple tup{1, 2.0, "three"s}; // deduced tuple types
    std::cout << "Tuple elements: "
              << std::get<0>(tup) << ", "
              << std::get<1>(tup) << ", "
              << std::get<2>(tup) << "\n";

    std::vector vec{1, 2, 3}; // deduced as std::vector<int>
    std::cout << "Vector elements: ";
    for (auto v : vec)        // iterate vector
        std::cout << v << ", ";
    std::cout << "\n";

    std::array arr{"Bart"s, "Lisa"s, "Maggie"s}; // deduced std::array<std::string, 3>
    std::cout << "Array size: " << arr.size() << "\n";
    std::cout << "Array elements: ";
    for (auto a : arr)        // iterate array
        std::cout << a << ", ";
    std::cout << "\n";

    std::lock_guard lk(global_mtx); // lock mutex using CTAD

    // ----- Nested vector examples (nested.cc) -----

    std::vector v1{1, 2, 3};  // vector<int>
    print(v1);                // print 1D

    std::vector v2{4, 5, 6, 7}; // vector<int>
    print(v2);                  // print 1D

    std::vector v3{v1, v2};   // vector<vector<int>>
    print(v3);                // print 2D

    std::vector v4{v1};       // still vector<int>, not nested
    print(v4);                // print 1D

    // ----- Template deduction example (older.cc) -----

    // Test test(3);          // ERROR: no template argument (before C++17 CTAD)
    Test<int> test(3);        // explicit template argument

    return 0;                 // end program
}
```

## Structured bindings
Structured bindings are a C++17 feature that let you unpack multiple values from an object into separate variables in one line. Think of it as a clean way to “destructure” things like pairs, tuples, arrays, or structs.

```cpp
#include <iostream>              // For std::cout
#include <tuple>                 // For std::tuple
#include <string>                // For std::string
#include <utility>               // For std::pair

using namespace std::literals;   // Enables "text"s string literal

// Define a struct for the struct example
struct Numbers {
    int x;                       // Integer member
    double y;                    // Double member
    std::string z;               // String member
};

int main()
{
    // =======================
    // 1. std::pair example
    // =======================

    std::pair pr(1, 3.142);      // Create a pair<int, double> with values (1, 3.142)

    auto [pi, pd] = pr;          // Structured binding: pi = 1, pd = 3.142

    std::cout << "[pair] ";      // Label output
    std::cout << "i = " << pi    // Print integer part
              << ", d = " << pd  // Print double part
              << '\n';           // New line

    // =======================
    // 2. struct example
    // =======================

    Numbers numbers{1, 2.0, "three"s}; // Initialize struct with values

    // Structured binding (C++17)
    auto [si, sd, ss] = numbers; // si=1, sd=2.0, ss="three"

    std::cout << "[struct] ";    // Label output
    std::cout << "i = " << si    // Print int
              << ", d = " << sd  // Print double
              << ", s = " << ss  // Print string
              << '\n';           // New line

    // =======================
    // 3. std::tuple example
    // =======================

    std::tuple t = std::make_tuple(1, 2.0, "three"s); // Create tuple<int, double, string>

    // Structured binding (C++17)
    auto [ti, td, ts] = t;      // ti=1, td=2.0, ts="three"

    std::cout << "[tuple] ";    // Label output
    std::cout << "i = " << ti   // Print int
              << ", d = " << td // Print double
              << ", s = " << ts // Print string
              << '\n';          // New line

    return 0;                   // End program successfully
}
```

## Structured bindings and maps
This C++ program demonstrates how to use std::map to store key–value pairs and compares older C++11/14 techniques with newer C++17 features. It defines two insert functions: one uses the traditional std::pair return from map::insert to check if insertion succeeded, while the other uses structured bindings (a C++17 feature) to unpack the result more cleanly. In main, a map is initialized with a few entries, then printed twice—first using the older loop style with .first and .second, and then using structured bindings for clearer syntax. Finally, both insert functions are tested with duplicate and new keys to show how the map prevents duplicate keys and how each version reports success or failure, illustrating both backward-compatible and modern C++ approaches.

```cpp
#include <iostream>              // For std::cout
#include <map>                   // For std::map container
#include <string>                // For std::string

using namespace std::literals;   // Enables "text"s string literal

// ----------- C++11/14 INSERT FUNCTION -----------
void cpp14_insert(std::map<int, std::string>& m, int new_key, std::string new_val) {
    // Insert returns pair<iterator, bool>
    auto pr = m.insert({new_key, new_val});  // Try inserting key-value pair

    if (pr.second)                           // Check if insertion succeeded
        std::cout << "Inserted a new element\n";  // Success message
    else {
        auto el = pr.first;                  // Iterator to existing element
        std::cout << "Insert failed ";       // Failure message
        std::cout << "due to an element with key: " << el->first
                  << " and value: " << el->second << '\n'; // Show conflicting element
    }
}

// ----------- C++17 INSERT FUNCTION (STRUCTURED BINDINGS) -----------
void cpp17_insert(std::map<int, std::string>& m, int new_key, std::string new_val) {
    auto [iter, success] = m.insert({new_key, new_val}); // Structured binding

    if (success)                                         // Check success
        std::cout << "Inserted a new element\n";          // Success message
    else {
        auto [key, value] = *iter;                       // Unpack iterator result
        std::cout << "Insert failed ";                   // Failure message
        std::cout << "due to an element with key: " << key
                  << " and value: " << value << '\n';    // Show conflicting element
    }
}

// ----------- MAIN FUNCTION -----------
int main() {
    // Create a map with initial elements
    std::map<int, std::string> m = {
        {1, "Hello"s},
        {2, "How are you?"s},
        {3, "Goodbye"s}
    };

    // ----------- LOOP EXAMPLE C++11/14 -----------
    std::cout << "Map elements (C++11/14):\n";  // Header output
    for (auto el : m)                           // Iterate through map
        std::cout << "Key = " << el.first       // Access key
                  << ", Value = " << el.second  // Access value
                  << '\n';                      // New line

    // ----------- LOOP EXAMPLE C++17 -----------
    std::cout << "Map elements (C++17):\n";     // Header output
    for (auto [key, value] : m)                 // Structured binding unpack
        std::cout << "Key = " << key            // Print key
                  << ", Value = " << value      // Print value
                  << '\n';                      // New line

    // ----------- INSERT TESTS -----------
    std::cout << "\nTesting insert (C++11/14):\n"; // Section header
    cpp14_insert(m, 1, "Hello again"s);            // Duplicate key (fail)
    cpp14_insert(m, 4, "New value"s);              // New key (success)

    std::cout << "\nTesting insert (C++17):\n";    // Section header
    cpp17_insert(m, 2, "Duplicate"s);              // Duplicate key (fail)
    cpp17_insert(m, 5, "Another value"s);          // New key (success)

    return 0;                                      // End program
}
```

## If statements
This merged C++17 program demonstrates how modern language features make code more concise and safer by limiting variable scope and improving readability: instead of declaring variables before an if, C++17 allows you to initialize them directly inside the if statement (e.g., iterators or search results), ensuring they only exist where needed; when working with containers like std::map, the program shows how insertion returns both an iterator and a success flag, which can be unpacked using structured bindings (auto [iter, success]) for clearer logic; it also compares older C++14 patterns with newer C++17 approaches for tasks like searching in strings, highlighting that the newer style reduces clutter while keeping checks (like avoiding invalid iterators or missing values) explicit and safe, ultimately leading to cleaner, more maintainable code.

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std::literals;

// ------------------------------------------------------------
// Example 1: Demonstrating C++17 if-initializer with iterators
// ------------------------------------------------------------
void vector_example()
{
    std::vector<int> vec = {1, 2, 3};

    // C++17 feature:
    // Declare and initialize 'iter' inside the if-statement.
    // Scope of 'iter' is limited to this if block.
    if (auto iter = vec.begin(); iter != vec.end()) {
        // We safely dereference because we already checked it's not end()
        std::cout << "First element of vec: " << *iter << '\n';
    }
}


// ------------------------------------------------------------
// Example 2: Inserting into a map and checking success
// ------------------------------------------------------------
void map_insert_example()
{
    std::map<int, std::string> m = { {1, "Hello"s} };

    // insert() returns a pair:
    // - iterator to element
    // - bool indicating success of insertion
    if (auto result = m.insert({2, "How are you?"s}); result.second) {
        std::cout << "Insertion successful\n";
    } else {
        std::cout << "Insertion failed (key already exists)\n";
    }
}


// ------------------------------------------------------------
// Example 3: Structured bindings (C++17)
// ------------------------------------------------------------
void map_insert_binding_example()
{
    std::map<int, std::string> m = { {1, "hello"s} };

    // Structured binding splits the returned pair into:
    // iter  -> iterator to element
    // success -> bool indicating insertion success
    if (auto [iter, success] = m.insert({1, "goodbye"s}); success) {
        std::cout << "Inserted new element\n";
    } else {
        std::cout << "Insert failed (duplicate key)\n";

        // Access existing element via iterator
        auto [key, value] = *iter;
        std::cout << "Existing -> Key: " << key
                  << ", Value: " << value << '\n';
    }

    // Range-based loop with structured bindings
    std::cout << "All map elements:\n";
    for (auto [key, value] : m) {
        std::cout << key << " => " << value << '\n';
    }
}


// ------------------------------------------------------------
// Example 4: Searching characters in a string
// ------------------------------------------------------------

// C++14 style (separate variable + if)
void find_cpp14(const std::string& str, char c)
{
    auto pos = str.find(c);  // find position of character

    if (pos != std::string::npos) {
        std::cout << "Found '" << c << "' at index " << pos << '\n';
    } else {
        std::cout << "Character '" << c << "' not found\n";
    }
}


// C++17 style (if with initializer)
void find_cpp17(const std::string& str, char c)
{
    // 'pos' exists only inside this if statement
    if (auto pos = str.find(c); pos != std::string::npos) {
        std::cout << "Found '" << c << "' at index " << pos << '\n';
    } else {
        std::cout << "Character '" << c << "' not found\n";
    }
}


// ------------------------------------------------------------
// Main function to run all examples
// ------------------------------------------------------------
int main()
{
    std::cout << "=== Vector Example ===\n";
    vector_example();

    std::cout << "\n=== Map Insert Example ===\n";
    map_insert_example();

    std::cout << "\n=== Map Structured Binding Example ===\n";
    map_insert_binding_example();

    std::cout << "\n=== String Search (C++14 vs C++17) ===\n";
    std::string text = "Hello";
    find_cpp14(text, 'l');
    find_cpp17(text, 'o');

    return 0;
}
```
# C++ 17 highlights

## Switch statements
The example shows how a C++17 switch statement with an initializer can be used to process characters in a string while keeping variables scoped neatly. The program loops through each character of a C-style string and, inside the switch, declares a temporary variable c (const char c = arr[i]) that exists only for that switch. It then checks whether c is a whitespace character (space ' ', tab '\t', or newline '\n'); if so, it increments a counter. Each case falls into the same action (incrementing), and break prevents unintended fallthrough. This approach keeps the code clean by avoiding extra variables outside the switch while clearly grouping conditions that share the same behavior.

```cpp
#include <iostream>      // for std::cout
#include <string>        // for std::string
#include <utility>       // for std::pair

using namespace std::literals; // enables "text"s string literal

// -------------------------
// Example 1: Basic switch with initializer
// -------------------------
void example_basic_switch() {
    int ws_count{0}; // counter for whitespace characters

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 1: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // loop until null terminator
        switch (const char c = arr[i]; c) { // C++17 switch initializer
            case ' ':      // if character is space
            case '\t':     // or tab
            case '\n':     // or newline
                ++ws_count; // increment counter
                break;      // exit switch
            default:       // any other character
                break;      // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n\n"; // print result
}

// -------------------------
// Example 2: Structured binding in switch
// -------------------------

// enum to represent result states
enum class Result { SUCCEEDED, TIMED_OUT, FAILED };

// function returning a pair (data + result)
auto fetch() {
    return std::pair{"abcdef"s, Result::SUCCEEDED}; // sample data
}

void example_structured_binding() {
    std::cout << "Example 2:\n"; // header

    // structured binding inside switch (C++17 feature)
    switch (auto [data, result] = fetch(); result) {
        case Result::SUCCEEDED: // success case
            std::cout << "Fetched data: " << data << '\n'; // print data
            break;
        case Result::TIMED_OUT: // timeout case
            std::cout << "The operation timed out\n";
            break;
        case Result::FAILED:    // failure case
            std::cout << "The operation failed\n";
            break;
    }

    std::cout << "\n"; // spacing
}

// -------------------------
// Example 3: Fallthrough attribute
// -------------------------
void example_fallthrough() {
    int ws_count{0}; // counter for whitespace

    const char* arr = "How much whitespace in\t here?"; // input string
    std::cout << "Example 3: \"" << arr << "\"\n"; // print input

    for (int i = 0; arr[i]; ++i) { // iterate characters
        switch (const char c = arr[i]; c) { // switch with initializer
            case ' ':              // space
                [[fallthrough]];  // intentional fallthrough
            case '\t':             // tab
                [[fallthrough]];  // intentional fallthrough
            case '\n':             // newline
                ++ws_count;       // count whitespace
                break;            // exit switch
            default:              // not whitespace
                break;            // do nothing
        }
    }

    std::cout << "Whitespace count: " << ws_count << "\n"; // output result
}

// -------------------------
// Main function
// -------------------------
int main() {
    example_basic_switch();        // run first example
    example_structured_binding();  // run second example
    example_fallthrough();         // run third example

    return 0; // end program
}
```

## Copy elision
```cpp
#include <iostream>                 // Include input-output stream library for std::cout

class Test {                       // Define a class named Test
  public:
    Test() {                       // Default constructor
        std::cout << "Default constructor\n"; // Print when object is created
    }
    
    // Copy constructor with side effect
    Test(const Test& other) {      // Copy constructor (called when copying objects)
        std::cout << "Copying\n";  // Print when a copy happens
    }
};

// Function returning a temporary object
Test func()                        // Function that returns a Test object
{
    return Test{};                 // Return a temporary Test object (prvalue)
}

int main()                         // Entry point of the program
{
    std::cout << "Calling func()\n"; // Print before calling func()
    
    // How many times is "Copying" printed out?
    Test test = func();            // Initialize 'test' with return value of func()
                                   // In C++17, copy elision is guaranteed here
                                   // So NO copy constructor is called
    
    std::cout << "Returned from func()\n"; // Print after func() completes
}
```
(c) 2026 Freek van den Berg. All rights reserved.

# C++ manual

- A. Traditional C++ [1](a_traditional.md) [2](a_traditional2.md) [3](a_traditional3.md) [4](a_traditional4.md)
- B. Modern C++ features [1](b_modern.md) [2](b_modern2.md) [3](b_modern3.md)
- C. Lambda expressions [1](c_lambda.md)
- D. Modern C++ Library features [1](d_modern_library.md) [2](d_modern_library2.md) [3](d_modern_library3.md)
- E. Move semantics [1](e_move.md)
- F. Multithreading [1](f_multithreading.md) [2](f_multithreading2.md)
- G. Smart pointers [1](g_smart_pointers.md)
- H. Compile time programming [1](h_compile_time_programming.md)
- I. C++ 17 highlights [1](i_c17_highlights.md) [2](i_c17_highlights2.md)

See [Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) for guidelines about how to use C++
