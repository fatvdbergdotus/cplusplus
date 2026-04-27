# Traditional C++

## Exceptions

### No try catch
```
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
```
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
```
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
```
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

## 



