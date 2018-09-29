# Just a printf wrapper

## Features
Provides an extension to use `snprintf()` on `std::string`

## Use cases
To create some formatted content in `std::string`:
```C++
std::string welcome = jpf::jsnprintf(50, "Hello %s\n", "World");
```

To pump some formatted content to a stream, say `std::cout`:
```C++
cout << jpf::jsnprintf(62, "%60s\n", "Use whatever formating string that you get used to!");
```

Fully compatible with C99 `printf()` formatting string:
```C++
std::string BobsInfo = jpf::jsnprintf(500, "Name\t: %s\nAge\t: %2d\nIncome\t: $%9.2f",
                                "Bob",      // A friend of Alice
                                30,         // Get older and older 
                                23456.78901 // A long floating number
                                );
std::cout << BobsInfo << endl;
```

## Explanation
It is convenient to create a `std::string` variable and pass it around instead of creating a `char` array and working with pointer.
However, the formating of `std::string` has long been an issue:
```C++
std::cout << std::setprecision(3) << std::fixed << 1.23456 << endl;
printf("%.3f\n", 1.23455);
```
which is far too bulky than its printf version.

Don't even mention about the difficulties to write a `std::string` vesion of padding zero at begining:
```C++
double pi = 22.0/7.0;
printf("%08.2f\n", pi);   // This prints 00003.14
```
The standard IOStreams formatting style simply cannot scale up. There is a strong reason to rework the `printf` style API in `std::string`.

---
In the old days, people create C-style strings in this way:
```C++
char sBuffer[100];
memset(sBuffer, 0, sizeof(char)*100);
snprintf(sBuffer, 100, "Hello World");
```
In the above example, the `snprintf(...)` call is safe only when the length variable `n` is input correctly (100 in this case).
Such implementation relys on the programer to code *smartly*, which contradict to nowadays' C++ style.
```C++
string sBuffer = "Hello" + "W" + "orld";
```
Programmers concentrate on the content and let the language taking care of memory allocation and initialization.

---
Our solution is to make use of `snprintf(...)` and redirects the result into a `std::string`.
Programmers have to take note of the content being print and give an estimated length as hint.
```C++
int steps = 20;
cout << jpf::jsnprintf(80, "Counter: %d\n", steps);   // (1) >> Counter: 20
cout << jpf::jsnprintf(5, "Counter: %d\n", steps);    // (2) Not a logical statement, gives unkown result
```
In the above example, statement (1) is *safe* since it is unlikely that the finally string would exceed 80 bytes. In statement (2), you will never be able to squeeze the output into a 5 byte long `char` array. In this case, the program halts at (2).

Our solution is memory efficient at the end:
```C++
std::string S = jpf::jsnprintf(100, "Happy %dth anniversary!", 30);
printf("S length: %lu, capacity: %lu\n", S.length(), S.capacity());
// >> S length: 23, capacity: 23
```
