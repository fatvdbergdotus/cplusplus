# Complete C++ `<algorithm>` and `<numeric>` Examples

## `all_of()`
Checks if all elements satisfy condition.

```cpp
// Checks if all elements satisfy condition
vector<int> v={2,4,6};
bool r=all_of(v.begin(),v.end(),[](int n){return n%2==0;});

/*
Expected output:
1
*/
```

---

## `any_of()`
Checks if any element satisfies condition.

```cpp
// Checks if any element satisfies condition
vector<int> v={1,3,4};
bool r=any_of(v.begin(),v.end(),[](int n){return n%2==0;});

/*
Expected output:
1
*/
```

---

## `none_of()`
Checks if no elements satisfy condition.

```cpp
// Checks if no elements satisfy condition
vector<int> v={1,3,5};
bool r=none_of(v.begin(),v.end(),[](int n){return n%2==0;});

/*
Expected output:
1
*/
```

---

## `for_each()`
Applies function to each element.

```cpp
// Applies function to each element
vector<int> v={1,2,3};
for_each(v.begin(),v.end(),[](int n){cout<<n<<" ";});

/*
Expected output:
1 2 3
*/
```

---

## `count()`
Counts matching values.

```cpp
// Counts matching values
vector<int> v={1,2,2,3};
cout<<count(v.begin(),v.end(),2);

/*
Expected output:
2
*/
```

---

## `count_if()`
Counts elements satisfying condition.

```cpp
// Counts elements satisfying condition
vector<int> v={1,2,3,4};
cout<<count_if(v.begin(),v.end(),[](int n){return n%2==0;});

/*
Expected output:
2
*/
```

---

## `find()`
Finds value in range.

```cpp
// Finds value in range
vector<int> v={1,2,3};
auto it=find(v.begin(),v.end(),2);
if(it!=v.end()) cout<<*it;

/*
Expected output:
2
*/
```

---

## `find_if()`
Finds first matching condition.

```cpp
// Finds first matching condition
vector<int> v={1,2,3};
auto it=find_if(v.begin(),v.end(),[](int n){return n>1;});
cout<<*it;

/*
Expected output:
2
*/
```

---

## `adjacent_find()`
Finds adjacent equal elements.

```cpp
// Finds adjacent equal elements
vector<int> v={1,2,2,3};
auto it=adjacent_find(v.begin(),v.end());
cout<<*it;

/*
Expected output:
2
*/
```

---

## `search()`
Searches subsequence.

```cpp
// Searches subsequence
vector<int> v={1,2,3,4};
vector<int> sub={2,3};
auto it=search(v.begin(),v.end(),sub.begin(),sub.end());
cout<<*it;

/*
Expected output:
2
*/
```

---

## `copy()`
Copies elements.

```cpp
// Copies elements
vector<int> a={1,2,3}; vector<int> b(3);
copy(a.begin(),a.end(),b.begin());
for(int n:b) cout<<n<<" ";

/*
Expected output:
1 2 3
*/
```

---

## `copy_if()`
Copies matching elements.

```cpp
// Copies matching elements
vector<int> a={1,2,3,4}; vector<int> b;
copy_if(a.begin(),a.end(),back_inserter(b),[](int n){return n%2==0;});

/*
Expected output:
2 4
*/
```

---

## `fill()`
Fills range with value.

```cpp
// Fills range with value
vector<int> v(3);
fill(v.begin(),v.end(),7);

/*
Expected output:
7 7 7
*/
```

---

## `fill_n()`
Fills first n elements.

```cpp
// Fills first n elements
vector<int> v(5);
fill_n(v.begin(),3,9);

/*
Expected output:
9 9 9 0 0
*/
```

---

## `transform()`
Transforms elements.

```cpp
// Transforms elements
vector<int> v={1,2,3};
transform(v.begin(),v.end(),v.begin(),[](int n){return n*2;});

/*
Expected output:
2 4 6
*/
```

---

## `generate()`
Generates values.

```cpp
// Generates values
vector<int> v(3); int n=1;
generate(v.begin(),v.end(),[&](){return n++;});

/*
Expected output:
1 2 3
*/
```

---

## `remove()`
Removes matching values.

```cpp
// Removes matching values
vector<int> v={1,2,2,3};
v.erase(remove(v.begin(),v.end(),2),v.end());

/*
Expected output:
1 3
*/
```

---

## `remove_if()`
Removes matching condition.

```cpp
// Removes matching condition
vector<int> v={1,2,3,4};
v.erase(remove_if(v.begin(),v.end(),[](int n){return n%2==0;}),v.end());

/*
Expected output:
1 3
*/
```

---

## `replace()`
Replaces values.

```cpp
// Replaces values
vector<int> v={1,2,2};
replace(v.begin(),v.end(),2,9);

/*
Expected output:
1 9 9
*/
```

---

## `reverse()`
Reverses range.

```cpp
// Reverses range
vector<int> v={1,2,3};
reverse(v.begin(),v.end());

/*
Expected output:
3 2 1
*/
```

---

## `rotate()`
Rotates elements.

```cpp
// Rotates elements
vector<int> v={1,2,3,4};
rotate(v.begin(),v.begin()+1,v.end());

/*
Expected output:
2 3 4 1
*/
```

---

## `shuffle()`
Randomly shuffles elements.

```cpp
// Randomly shuffles elements
vector<int> v={1,2,3,4};
shuffle(v.begin(),v.end(),mt19937(random_device()()));

/*
Expected output:
Random order
*/
```

---

## `unique()`
Removes consecutive duplicates.

```cpp
// Removes consecutive duplicates
vector<int> v={1,1,2,2,3};
v.erase(unique(v.begin(),v.end()),v.end());

/*
Expected output:
1 2 3
*/
```

---

## `partition()`
Partitions by condition.

```cpp
// Partitions by condition
vector<int> v={1,2,3,4};
partition(v.begin(),v.end(),[](int n){return n%2==0;});

/*
Expected output:
Even numbers first
*/
```

---

## `sort()`
Sorts ascending.

```cpp
// Sorts ascending
vector<int> v={4,1,3,2};
sort(v.begin(),v.end());

/*
Expected output:
1 2 3 4
*/
```

---

## `stable_sort()`
Stable sorting.

```cpp
// Stable sorting
vector<int> v={4,1,3,2};
stable_sort(v.begin(),v.end());

/*
Expected output:
1 2 3 4
*/
```

---

## `partial_sort()`
Sorts partial range.

```cpp
// Sorts partial range
vector<int> v={4,1,3,2};
partial_sort(v.begin(),v.begin()+2,v.end());

/*
Expected output:
1 2 ...
*/
```

---

## `nth_element()`
Places nth element correctly.

```cpp
// Places nth element correctly
vector<int> v={4,1,3,2};
nth_element(v.begin(),v.begin()+2,v.end());

/*
Expected output:
3 at index 2
*/
```

---

## `binary_search()`
Checks if value exists.

```cpp
// Checks if value exists
vector<int> v={1,2,3,4};
cout<<binary_search(v.begin(),v.end(),3);

/*
Expected output:
1
*/
```

---

## `lower_bound()`
First element >= value.

```cpp
// First element >= value
vector<int> v={1,2,3,4};
auto it=lower_bound(v.begin(),v.end(),3);
cout<<*it;

/*
Expected output:
3
*/
```

---

## `upper_bound()`
First element > value.

```cpp
// First element > value
vector<int> v={1,2,3,3,4};
auto it=upper_bound(v.begin(),v.end(),3);
cout<<*it;

/*
Expected output:
4
*/
```

---

## `equal_range()`
Returns lower and upper bound.

```cpp
// Returns lower and upper bound
vector<int> v={1,2,2,3};
auto p=equal_range(v.begin(),v.end(),2);

/*
Expected output:
Range of 2
*/
```

---

## `merge()`
Merges sorted ranges.

```cpp
// Merges sorted ranges
vector<int> a={1,3}; vector<int> b={2,4}; vector<int> c(4);
merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());

/*
Expected output:
1 2 3 4
*/
```

---

## `inplace_merge()`
Merges sorted subranges.

```cpp
// Merges sorted subranges
vector<int> v={1,3,5,2,4,6};
inplace_merge(v.begin(),v.begin()+3,v.end());

/*
Expected output:
1 2 3 4 5 6
*/
```

---

## `set_union()`
Computes union.

```cpp
// Computes union
Union of sorted sets

/*
Expected output:
1 2 3 4 5
*/
```

---

## `set_intersection()`
Computes intersection.

```cpp
// Computes intersection
Intersection of sorted sets

/*
Expected output:
2 3
*/
```

---

## `set_difference()`
Computes difference.

```cpp
// Computes difference
Difference of sorted sets

/*
Expected output:
1
*/
```

---

## `make_heap()`
Creates heap.

```cpp
// Creates heap
vector<int> v={3,1,4,2};
make_heap(v.begin(),v.end());

/*
Expected output:
Max heap
*/
```

---

## `push_heap()`
Adds element to heap.

```cpp
// Adds element to heap
push_heap(v.begin(),v.end());

/*
Expected output:
Heap updated
*/
```

---

## `pop_heap()`
Removes top heap element.

```cpp
// Removes top heap element
pop_heap(v.begin(),v.end());

/*
Expected output:
Largest moved to end
*/
```

---

## `sort_heap()`
Sorts heap.

```cpp
// Sorts heap
sort_heap(v.begin(),v.end());

/*
Expected output:
Sorted order
*/
```

---

## `min()`
Returns smaller value.

```cpp
// Returns smaller value
cout<<min(3,5);

/*
Expected output:
3
*/
```

---

## `max()`
Returns larger value.

```cpp
// Returns larger value
cout<<max(3,5);

/*
Expected output:
5
*/
```

---

## `minmax()`
Returns min and max.

```cpp
// Returns min and max
auto p=minmax(3,5);

/*
Expected output:
3 and 5
*/
```

---

## `min_element()`
Finds smallest element.

```cpp
// Finds smallest element
vector<int> v={3,1,4};
cout<<*min_element(v.begin(),v.end());

/*
Expected output:
1
*/
```

---

## `max_element()`
Finds largest element.

```cpp
// Finds largest element
vector<int> v={3,1,4};
cout<<*max_element(v.begin(),v.end());

/*
Expected output:
4
*/
```

---

## `next_permutation()`
Next lexicographical order.

```cpp
// Next lexicographical order
vector<int> v={1,2,3};
next_permutation(v.begin(),v.end());

/*
Expected output:
1 3 2
*/
```

---

## `prev_permutation()`
Previous lexicographical order.

```cpp
// Previous lexicographical order
vector<int> v={3,2,1};
prev_permutation(v.begin(),v.end());

/*
Expected output:
3 1 2
*/
```

---

## `is_permutation()`
Checks permutations.

```cpp
// Checks permutations
vector<int> a={1,2,3}; vector<int> b={3,2,1};

/*
Expected output:
1
*/
```

---

## `lexicographical_compare()`
Dictionary comparison.

```cpp
// Dictionary comparison
string a="apple", b="banana";
cout<<lexicographical_compare(a.begin(),a.end(),b.begin(),b.end());

/*
Expected output:
1
*/
```

---

## `accumulate()`
Sums values (<numeric>).

```cpp
// Sums values (<numeric>)
vector<int> v={1,2,3};
cout<<accumulate(v.begin(),v.end(),0);

/*
Expected output:
6
*/
```

---

## `reduce()`
Parallel-friendly reduction.

```cpp
// Parallel-friendly reduction
vector<int> v={1,2,3};
cout<<reduce(v.begin(),v.end());

/*
Expected output:
6
*/
```

---

## `iota()`
Fills sequential values.

```cpp
// Fills sequential values
vector<int> v(5);
iota(v.begin(),v.end(),1);

/*
Expected output:
1 2 3 4 5
*/
```

---

## `inner_product()`
Computes dot product.

```cpp
// Computes dot product
vector<int> a={1,2,3}; vector<int> b={4,5,6};
cout<<inner_product(a.begin(),a.end(),b.begin(),0);

/*
Expected output:
32
*/
```

---

## `partial_sum()`
Computes prefix sums.

```cpp
// Computes prefix sums
vector<int> v={1,2,3};

/*
Expected output:
1 3 6
*/
```

---

## `adjacent_difference()`
Computes differences.

```cpp
// Computes differences
vector<int> v={1,3,6};

/*
Expected output:
1 2 3
*/
```

---

