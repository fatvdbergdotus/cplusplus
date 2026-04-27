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

### Operator()
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





