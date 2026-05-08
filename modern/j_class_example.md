(c) 2026 Freek van den Berg. All rights reserved.

# Small class example with virtual
This C++ project demonstrates basic inheritance and polymorphism using three classes arranged in a hierarchy: super_animal (base class), animal (derived from super_animal), and dog (derived from animal). The base class defines a virtual function make_sound(), which allows derived classes to override it. Each subclass overrides this function and explicitly calls its parent’s version before adding its own output. As a result, when dog::make_sound() is called, it triggers a chain of calls: first super_animal::make_sound(), then animal::make_sound(), and finally dog::make_sound(), producing layered output. This shows how virtual functions enable runtime polymorphism and how inheritance allows behavior to be extended step by step.

The project also contrasts overridden vs non-overridden methods using make_sound_non_override(). These functions are not marked virtual, so they do not participate in polymorphism—each class simply defines its own independent version. In main(), objects of each class are created and their methods are called directly, illustrating how overridden functions follow the inheritance chain while non-virtual ones do not. Overall, the project is a straightforward example of how C++ handles inheritance, method overriding, and the difference between polymorphic and non-polymorphic behavior.

See [Source files](class_example/class_example)
