# Small class example with virtual
This C++ project demonstrates basic inheritance and polymorphism: a base class super_animal defines a virtual function make_sound(), which outputs a generic message, and a derived class animal overrides this function to extend the behavior by first calling the base class version and then printing its own message. In main(), both an animal object and a super_animal object are created, and their respective make_sound() methods are called, showing how the derived class can reuse and enhance functionality from the base class while maintaining a shared interface through virtual functions.

See [Source files](class_example/class_example)
