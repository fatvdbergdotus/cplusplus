# C++ 17 highlights

## Map instertion
```cpp
#include <iostream>   // For input/output (std::cout)
#include <map>        // For std::map container
#include <string>     // For std::string

int main() {
    std::map<std::string, int> scores;  // Create a map storing (name -> score)

    // ============================================================
    // 1. Using insert (classic approach, pre-C++17)
    // ============================================================

    auto res_insert = scores.insert(std::make_pair("Graham", 66)); 
    // Try to insert ("Graham", 66) into the map
    // Returns pair<iterator, bool>
    // - iterator: points to element with key "Graham"
    // - bool: true if inserted, false if key already existed

    auto iter_insert = res_insert.first;  // Extract iterator to element

    if (res_insert.second) {  // If insertion succeeded
        std::cout << "[insert] Inserted new element: "
                  << iter_insert->first << " -> " << iter_insert->second << '\n';
    } else {  // If key already existed
        std::cout << "[insert] Key exists, updating value manually\n";
        iter_insert->second = 66;  // Manually update value
    }

    // ============================================================
    // 2. Using insert_or_assign (C++17)
    // ============================================================

    auto res_assign = scores.insert_or_assign("Graham", 77);
    // If key does NOT exist → insert
    // If key exists → overwrite value
    // Returns pair<iterator, bool> (same structure as insert)

    auto iter_assign = res_assign.first;  // Get iterator

    if (res_assign.second) {  // True if inserted
        std::cout << "[insert_or_assign] Inserted: "
                  << iter_assign->first << " -> " << iter_assign->second << '\n';
    } else {  // False if assigned (updated)
        std::cout << "[insert_or_assign] Modified: "
                  << iter_assign->first << " -> " << iter_assign->second << '\n';
    }

    // ============================================================
    // 3. Using structured bindings (C++17 modern syntax)
    // ============================================================

    if (auto [element, inserted] = scores.insert_or_assign("Graham", 88); inserted) {
        // element = iterator
        // inserted = bool
        std::cout << "[structured binding] Inserted: "
                  << element->first << " -> " << element->second << '\n';
    } else {
        std::cout << "[structured binding] Modified: "
                  << element->first << " -> " << element->second << '\n';
    }

    return 0;  // Program finished successfully
}
```

## Map emplace
```cpp
```

## Constexpr if statement
```cpp
```
