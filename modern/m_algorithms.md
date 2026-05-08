# Complete C++ `<algorithm>` and `<numeric>` Reference

This document provides a comprehensive reference for the most commonly used algorithms in the C++ Standard Library, mainly from the <algorithm> and <numeric> headers. Each section explains the purpose of a specific algorithm, includes a complete runnable C++ example, demonstrates the required input data such as vectors or ranges, and shows the expected output in comments. The examples cover a wide variety of operations including searching, sorting, counting, transforming, replacing, removing, partitioning, merging, heap manipulation, permutations, minimum and maximum operations, and numeric computations. By using short and practical code snippets, the document makes it easier to understand how each algorithm works and when it should be used.

The reference also highlights important concepts of modern C++ programming such as iterators, lambda expressions, ranges, and container manipulation. Algorithms like all_of(), find(), sort(), transform(), binary_search(), accumulate(), and iota() demonstrate how STL algorithms can simplify common programming tasks while improving readability and efficiency. Each example follows a consistent structure with explanatory comments and output verification, making the document useful as both a learning guide for beginners and a quick revision reference for intermediate programmers studying the C++ Standard Template Library (STL).

See also [https://en.cppreference.com/cpp/algorithm](https://en.cppreference.com/cpp/algorithm)

## `all_of()`
Checks if all elements satisfy a condition.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {2,4,6};
    bool r = all_of(v.begin(), v.end(), [](int n){ return n % 2 == 0; });
    cout << r << endl;
}

/*
Expected output:
1
*/
```

---

## `any_of()`
Checks if at least one element satisfies a condition.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,3,4};
    bool r = any_of(v.begin(), v.end(), [](int n){ return n % 2 == 0; });
    cout << r << endl;
}

/*
Expected output:
1
*/
```

---

## `none_of()`
Checks if no elements satisfy a condition.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,3,5};
    bool r = none_of(v.begin(), v.end(), [](int n){ return n % 2 == 0; });
    cout << r << endl;
}

/*
Expected output:
1
*/
```

---

## `for_each()`
Applies a function to every element.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    for_each(v.begin(), v.end(), [](int n){ cout << n << ' '; });
}

/*
Expected output:
1 2 3
*/
```

---

## `count()`
Counts occurrences of a value.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,2,3};
    cout << count(v.begin(), v.end(), 2) << endl;
}

/*
Expected output:
2
*/
```

---

## `count_if()`
Counts elements matching condition.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    cout << count_if(v.begin(), v.end(), [](int n){ return n % 2 == 0; }) << endl;
}

/*
Expected output:
2
*/
```

---

## `find()`
Finds a value in a range.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    auto it = find(v.begin(), v.end(), 2);
    if(it != v.end()) cout << *it << endl;
}

/*
Expected output:
2
*/
```

---

## `find_if()`
Finds first matching element.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    auto it = find_if(v.begin(), v.end(), [](int n){ return n > 1; });
    cout << *it << endl;
}

/*
Expected output:
2
*/
```

---

## `sort()`
Sorts elements ascending.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {4,1,3,2};
    sort(v.begin(), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 2 3 4
*/
```

---

## `stable_sort()`
Stable sorting.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {4,1,3,2};
    stable_sort(v.begin(), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 2 3 4
*/
```

---

## `partial_sort()`
Sorts only part of the range.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {4,1,3,2};
    partial_sort(v.begin(), v.begin()+2, v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 2 4 3
*/
```

---

## `binary_search()`
Checks if value exists in sorted range.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    cout << binary_search(v.begin(), v.end(), 3) << endl;
}

/*
Expected output:
1
*/
```

---

## `lower_bound()`
Returns first element >= value.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    auto it = lower_bound(v.begin(), v.end(), 3);
    cout << *it << endl;
}

/*
Expected output:
3
*/
```

---

## `upper_bound()`
Returns first element > value.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,3,4};
    auto it = upper_bound(v.begin(), v.end(), 3);
    cout << *it << endl;
}

/*
Expected output:
4
*/
```

---

## `reverse()`
Reverses a range.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    reverse(v.begin(), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
3 2 1
*/
```

---

## `rotate()`
Rotates elements.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    rotate(v.begin(), v.begin()+1, v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
2 3 4 1
*/
```

---

## `replace()`
Replaces matching values.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,2,3};
    replace(v.begin(), v.end(), 2, 9);
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 9 9 3
*/
```

---

## `remove()`
Removes matching values.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,2,3};
    v.erase(remove(v.begin(), v.end(), 2), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 3
*/
```

---

## `unique()`
Removes consecutive duplicates.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,1,2,2,3};
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 2 3
*/
```

---

## `partition()`
Partitions based on condition.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    partition(v.begin(), v.end(), [](int n){ return n % 2 == 0; });
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
2 4 3 1
*/
```

---

## `merge()`
Merges sorted ranges.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {1,3};
    vector<int> b = {2,4};
    vector<int> c(4);
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    for(int n : c) cout << n << ' ';
}

/*
Expected output:
1 2 3 4
*/
```

---

## `make_heap()`
Creates heap.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {3,1,4,2};
    make_heap(v.begin(), v.end());
    cout << v.front() << endl;
}

/*
Expected output:
4
*/
```

---

## `next_permutation()`
Generates next permutation.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    next_permutation(v.begin(), v.end());
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 3 2
*/
```

---

## `min_element()`
Finds smallest element.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {3,1,4};
    cout << *min_element(v.begin(), v.end()) << endl;
}

/*
Expected output:
1
*/
```

---

## `max_element()`
Finds largest element.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {3,1,4};
    cout << *max_element(v.begin(), v.end()) << endl;
}

/*
Expected output:
4
*/
```

---

## `accumulate()`
Computes sum of elements.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    #include <numeric>
    vector<int> v = {1,2,3};
    cout << accumulate(v.begin(), v.end(), 0) << endl;
}

/*
Expected output:
6
*/
```

---

## `iota()`
Fills with sequential values.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    #include <numeric>
    vector<int> v(5);
    iota(v.begin(), v.end(), 1);
    for(int n : v) cout << n << ' ';
}

/*
Expected output:
1 2 3 4 5
*/
```

---

## `inner_product()`
Computes dot product.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    #include <numeric>
    vector<int> a = {1,2,3};
    vector<int> b = {4,5,6};
    cout << inner_product(a.begin(), a.end(), b.begin(), 0) << endl;
}

/*
Expected output:
32
*/
```

---

