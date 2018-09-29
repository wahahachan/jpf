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

Fully compatible to C99 `printf()` formatting string:
```C++
std::string BobsInfo = jpf::jsnprintf(500, "Name\t: %s\nAge\t: %2d\nIncome\t: $%9.2f",
                                "Bob",      // A friend of Alice
                                30,         // Get older and older 
                                23456.78901 // A long floating number
                                );
std::cout << BobsInfo << endl;
```
