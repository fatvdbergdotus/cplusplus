# Modern C++ Programming Style gio

Please keep the following guidelines in mind when programming in Modern C++:

Higher level of abstraction
- Use [Smart pointers](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md) instead of new/delete
- Make use of [Algorithms](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/m_algorithms.md) (see also [https://en.cppreference.com/cpp/algorithm](https://en.cppreference.com/cpp/algorithm))

More work done at compile-time instead of run-time
- Use [static_assert](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/h_compile_time_programming.md) to perform compile-time checks
- Move from virtual functions to [templates](https://github.com/fatvdbergdotus/cplusplus/blob/main/modern/g_smart_pointers.md)

See also [https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) for more guidelines about how to use C++.
