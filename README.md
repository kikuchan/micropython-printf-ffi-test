## What's this?

Example of FFI on esp32 with MicroPython

```
MicroPython v1.17-dirty on 2021-12-01; ESP32 module with ESP32
Type "help()" for more information.
>>> import cexample
>>> cexample.printf("Hello, %s\nThis is %d\nfloat %.10f\n\n", "world", 42, 3.14159265358979)
Hello, world
This is 42
float 3.1415927410

44
>>> 
```

NB; 44 is a return value of printf().

## How to build

First, follow https://docs.micropython.org/en/latest/develop/cmodules.html

Then, build something like this:
```
% make USER_C_MODULES=../micropython-printf-ffi-test/src/micropython.cmake
```
