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





