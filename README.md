# String Formatter Writer

C++11 header-only library implement `std::print` with options to write to console, debug, file and syslog. Only ASCII string and basic types are supported. This is the console example.

```Cpp
#include "print.h"

using namespace printer;

print("My name is {} and my age is {}", "Harry", 24);
```

This is the debug output example using `dprint`.. On Windows, it calls `OutputDebugStringA`. On Apple MacOS, it calls `os_log` but you cannot use it on DriverKit because this library makes use of `std::vector` and DriverKit does not have `std::vector`.

```Cpp
dprint("My name is {} and my age is {}", "Harry", 24);
```

The example to write to file using `fprint`.

```Cpp
std::string filePath = "d:\\temp2\\file.txt";

FILE* fp = fopen(filePath.c_str(), "wt");

fprint(fp, "My name is {} and my age is {}\n", "Harry", 24);

fclose(fp);
fp = nullptr;
```

The syslog example using `sysprint` is below.

```Cpp
openlog("Logs", LOG_PERROR|LOG_PID, LOG_USER);

sysprint(LOG_INFO, "My name is {} and my age is {}", "Harry", 24);

closelog();
```

The string output is 

```
My name is Harry and my age is 24
```

Two format specifier are supported.

* `{}` : to format basic type value into string.
* `{h}` : to format `int` value to hexidecimal string with no `0x` prefix.
* `{t}` : to trim input string.
