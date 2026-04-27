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
```
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
```
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
```
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
```
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
```
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
```
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
```
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
```
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
```
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
```
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

```
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
```
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







