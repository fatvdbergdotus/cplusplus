(c) 2026 Freek van den Berg. All rights reserved.

# Traditional C++
## C++ Parameter Passing: Value vs Pointer vs Reference
In C++, arguments can be passed to functions in three main ways: pass by value, pass by pointer, and pass by reference. In pass by value, the function receives a copy of the variable, so changes made inside the function do not affect the original variable, and the copied parameter has a different memory address. In pass by pointer, the function receives the variable’s memory address using a pointer, allowing it to directly modify the original variable through dereferencing (*), so both addresses match. In pass by reference, the function uses an alias to the original variable, meaning no copy is created and modifications inside the function directly affect the original variable while sharing the same address.

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

/* Possible output:
Address of x is 0x61fe4c
Address of y is 0x61fe20
Address of z is 0x61fe48
After calling func(), z = 2
*/
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

/* Possible output:
Address of x is 0x61fe4c
Address of y is 0x61fe4c
After calling func(), x = 1
*/
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

/* Possible output:
Address of x is 0x61fe4c
Address of y is 0x61fe4c
After calling func(), x = 1
*/
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
This C++ program demonstrates how to use the std::deque container, which allows efficient insertion and removal of elements from both the front and back. The program creates an empty deque, adds elements using push_back() and push_front(), checks its size and whether it is empty, and prints the elements using iterators. It then sorts the deque with sort(), inserts a new element before a specific value using find() and insert(), removes the first element with erase(), and finally clears all elements using clear(). Throughout the program, iterators are used to traverse the deque, showing common operations and features of the STL deque container.

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
This C++ program demonstrates the use of the std::list container, a doubly linked list that allows efficient insertion and deletion of elements. The program creates an empty list, adds elements to both the front and back using push_front() and push_back(), checks the size and whether the list is empty, and prints all elements using iterators. It then sorts the list with the list-specific sort() member function, inserts a new element before a found value using find() and insert(), removes the first element with erase(), and finally clears all elements using clear(). The example highlights common list operations and iterator traversal in the C++ Standard Template Library (STL).

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
This C++ program demonstrates the use of the std::set container, which stores unique elements in sorted order. The program creates a set of integers, inserts several values, and prints them using iterators. It then attempts to insert the value 3 again, showing that sets automatically prevent duplicate elements by returning a pair from insert(), where the boolean value indicates whether the insertion succeeded. Afterward, the program removes the value 3 using erase(), prints the updated set, and tries inserting 3 once more, which now succeeds because the value no longer exists in the set. Overall, the example highlights important set operations such as insertion, duplicate checking, deletion, automatic sorting, and iterator traversal in the C++ STL.

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
This C++ program demonstrates the use of the std::map container, which stores key-value pairs in sorted order by key. The program creates a map that associates student names (string) with scores (int), inserts elements using insert() and make_pair(), and prints all entries using iterators. It accesses values using the key with the [] operator, updates an existing value by assigning a new score, and adds a new key-value pair dynamically. The program also uses the find() function to search for a specific key and checks whether it exists before displaying the corresponding value. Overall, the example highlights common map operations such as insertion, access, modification, searching, and traversal in the C++ STL.

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
This C++ program demonstrates the use of the std::queue container, which follows the First In, First Out (FIFO) principle, meaning the first element added is the first one removed. The program creates a queue of integers, adds elements using push(), and displays the queue size along with the first element using front() and the last element using back(). It then removes the front element with pop() and shows how the front and back values update afterward. The example highlights basic queue operations and how queues are commonly used for sequential processing in the order elements are inserted.

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
This C++ program demonstrates the use of the std::stack container, which follows the Last In, First Out (LIFO) principle, meaning the most recently added element is removed first. The program creates a stack of integers, adds elements using push(), and accesses the top element with top(). It then removes the top element using pop() and displays the new top element afterward. The example illustrates basic stack operations and how stacks are useful for tasks such as undo operations, expression evaluation, and recursive processing.

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
This example demonstrates operator overloading using the function call operator operator(), which allows an object to be used like a function. The evenp class defines operator()(int n) to check whether a number is even by returning true if the number is divisible by 2. In main(), an object named is_even is created and then called like a normal function using is_even(6). Because objects with operator() behave like functions, they are called functors or function objects. Functors are commonly used in algorithms and callbacks because they combine function behavior with object-oriented features such as storing state and customization.

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
This example demonstrates operator overloading in a Point class, allowing objects to behave more naturally with standard operators. The + operator is overloaded to add the coordinates of two points, while the - operator subtracts them. The == operator compares two points to determine whether both their x and y values are equal. The << operator is overloaded as a friend function so Point objects can be printed directly using cout in a readable format like (x, y). In main(), these overloaded operators make expressions such as p1 + p2, p1 - p2, p1 == p2, and cout << p1 work similarly to built-in data types, improving code readability and usability.

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

