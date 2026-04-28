# Modern C++

## Types and literals
```cpp
#include <iostream>
#include <string>
#include <cstdint>

using namespace std;
using namespace std::literals;

int main() {

    // ===== numeric.cc =====
    const int one_million = 1'000'000;
    const int one_lakh = 1'00'000;
    double pi = 3.141'593;
    const int meaning_of_life = 0b101010;

    cout << "One million: " << one_million << endl;
    cout << "One lakh: " << one_lakh << endl;
    cout << "Pi: " << pi << endl;
    cout << "The meaning of life: " << meaning_of_life << endl << endl;


    // ===== raw.cc =====
    string url = "<a href=\"file\">C:\\Program Files\\</a>\\n";
    cout << "URL is " << url << endl << endl;

    string raw_url = R"(<a href="file">C:\Program Files\</a>\n)";
    cout << "Raw URL is " << raw_url << endl << endl;

    string delimited_url = R"x(<a href="file">C:\Program Files (x86)\</a>\n)x";
    cout << "Delimited URL is " << delimited_url << endl << endl;


    // ===== string.cc =====
    const char *cca = "Hello, world!";
    cout << "cca is: " << cca << endl;

    string str = "Hello, world!"s;
    cout << "str is: " << str << endl;

    cout << R"(First element of "Goodbye" is: )";
    cout << *("Goodbye"s.begin()) << endl << endl;


    // ===== int_fixed.cc =====
    cout << "int8_t: " << sizeof(int8_t) << endl;
    cout << "int16_t: " << sizeof(int16_t) << endl;
    cout << "int32_t: " << sizeof(int32_t) << endl;
    cout << "int64_t: " << sizeof(int64_t) << endl << endl;

    cout << "uint8_t: " << sizeof(uint8_t) << endl;
    cout << "uint16_t: " << sizeof(uint16_t) << endl;
    cout << "uint32_t: " << sizeof(uint32_t) << endl;
    cout << "uint64_t: " << sizeof(uint64_t) << endl << endl;


    // ===== long_long.cc =====
    cout << "char: " << sizeof(char) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;

    return 0;
}
```

## User defined literals

```cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// -------- string.cc --------
string operator "" _rev(const char *s, size_t l) {
    string retval(s, l);
    reverse(retval.begin(), retval.end());
    return retval;
}

// -------- temperature.cc --------
long double operator "" _F_to_C(long double fahrenheit) {
    return 5.0 / 9.0 * (fahrenheit - 32.0);
}

// -------- celsius.cc --------
class Celsius {
    long double temperature;
public:
    explicit Celsius(long double temperature) : temperature(temperature) {}
    void print() const { cout << temperature << " Celsius\n"; }
};

Celsius operator "" _C(long double celsius) {
    return Celsius(celsius);
}

// -------- raw.cc --------
class Bignum {
public:
    Bignum(const char *str) {
        cout << "Creating bignum with value " << str << endl;
    }
};

Bignum operator "" _Big(const char *str) {
    return Bignum(str);
}

// -------- combined main --------
int main() {
    // string.cc demo
    cout << R"("xyz" reversed is )" << "xyz"_rev << endl;

    // temperature.cc demo
    cout << "212 Fahrenheit is " << 212.0_F_to_C << " Celsius" << endl;

    // builtin.cc demo
    cout << 3.14159f << endl;
    cout << "Hello"s << endl;
    cout << 12'345'678'901'234'567'890ULL << endl;

    // celsius.cc demo
    cout << "100.0_C is ";
    Celsius temp = 100.0_C;
    temp.print();

    // raw.cc demo
    Bignum big = "1234567890123456789012345678901234567890"_Big;

    return 0;
}
```
