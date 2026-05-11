# Modern C++ Programming Style guidelines

Please keep the following guidelines in mind when programming in Modern C++:

## Higher level of abstraction
- Use [Smart pointers](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md) instead of new/delete
- Avoid use of explicit pointers and never use explicit new and delete calls.
- Make use of [Algorithms](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/m_algorithms.md) (see also [https://en.cppreference.com/cpp/algorithm](https://en.cppreference.com/cpp/algorithm))

RAII (Resource Acquisition Is Initialization) is a C++ programming idiom where resources such as memory, files, locks, or network connections are acquired in a constructor and automatically released in a destructor.

## More work done at compile-time instead of run-time
- Use [static_assert](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/h_compile_time_programming.md) to perform compile-time checks
- Move from virtual functions to [templates](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)

## More work done by the compiler and library instead of programmer
- [Type deduction](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/h_compile_time_programming.md) and [Smart Pointers](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)

## Initialize variables whne declaring them
- Use the {} form for consistency, e.g., int x{42};
- Use auto for types which are tedious to type or unknowable
- Don't use [auto](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/i_c17_highlights.md) when the type name provides useful information

## Use type aliases to simplify complex types
- E.g., [using](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/e_move.md) IntVector = vector<int>; IntVector nums = {1, 2, 3, 4};

## Use these functions
- [make_unique](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)
- [make_shared](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)
- [make_pair](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/d_modern_library.md)
- [make_tuple](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/d_modern_library.md)

## Class operators
- Single-argument constructors should usually be made [explicit](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/e_move.md)
- Use in-place initializers for members which have a sensible default value
- Use delegating constructors to avoid duplicating code
- If you want a default special member function, use [=default](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)
- If objects of the class should not be copied, [delete](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/b_modern2.md) the copy operators

## Error handling
- [Throw](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/f_multithreading2.md) an exception to indicate when a task cannot be performed, especially when a constructor fails
- If a function does not throw, declare it [noexcept[(https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/b_modern3.md)
- Avoid explicit try/catch blocks by putting resources inside an RAII class

See also [https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) for more guidelines about how to use C++.
