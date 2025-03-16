# String Formatter Writer

This header-only library implement `std::print` with options to write to console, debug, file and syslog. This is the console example.

```Cpp
#include "values_writer.h"

using namespace writer;

Console w;

w.WriteLine("My name is {} and my age is {}", "Harry", 24);
```

This is the debug output example. On Windows, it calls `OutputDebugStringA`. On Apple MacOS, it calls `os_log` but you cannot use it on DriverKit because this library makes use of `std::vector` and DriverKit does not have `std::vector`.

```Cpp
#include "values_writer.h"

using namespace writer;

Debug w;

w.WriteLine("My name is {} and my age is {}", "Harry", 24);
```

The example to write to file.

```Cpp
#include "values_writer.h"

using namespace writer;

FileWriter w("d:\\temp2\\file.txt");

w.WriteLine("My name is {} and my age is {}", "Harry", 24);
```

The syslog example is below.

```Cpp
#include "syslog_writer.h"

using namespace writer;

SyslogWriter w("Logs", LOG_PERROR|LOG_PID, LOG_USER);

w.Write(LOG_INFO, "My name is {} and my age is {}", "Harry", 24);
```

The string output is 

```
My name is Harry and my age is 24
```

Two format specifier are supported.

* `{}` : to format basic type value into string.
* `{h}` : to format `int` value to hexidecimal string with no `0x` prefix.
