# Creates std::string with printf style formatting

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
Such implementation relys on programmers to code *smartly*, which contradict to nowadays' C++ style.
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

## Speed test
We have tested our library against libc `snprintf` and {fmt}. A string is produced from the following input:

`"My %llu-yo brithday party will be held on %4u/%02u/%02u %02u:%02u:%02u.%03u"`

which produces the output

`My 40-yo brithday party will be held on 2018/03/31 20:01:01.026`

The process is repeated 5,000,000 times with a simple for-loop compiled with g++ 4.9.2 with flag `-O1 -DNDEBUG` on Ubuntu 16.04 virtual machine equipped with a `i5-3470` CPU.

| API | Elapsed time |   |
|----|-----|----|
| snprintf | 1.927 s | 100%  |
| jpf::jsnprintf | 2.511 s | 130%  |
| fmt:sprintf | 3.020 s | 156%  |

## Summary

✓ 100% Compatibility: create std::string with your beloved printf formatting style

✓ Protability and ease of use: just include header files and you are good to go

✓ Low dependence: depends only on `cstdarg`, `cstdio` & `string` which are included as standard in modern C++

✓ Lightning fast: give low performance hit even compared with standard snprintf

☓ Argument positioning: we suggest to find alternatives if you are working on multilingual support

☓ Custom type: you have to write your own ostream operator

X Fail safe mechanism: we **do not** provides exception throw nor compile time argument checking nor string length auto-correction

## License
Thejpf library is distributed under the [MIT license](https://opensource.org/licenses/mit-license.php).

## Acknowledgments
The jpf library is written and maintained by Joe Chan.
