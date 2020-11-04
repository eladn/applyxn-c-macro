`APPLYXn` is a macro extension tool for the C preprocessor. `APPLYXn(..)` is a macro itself.
When applied, it expects to receive (i) a name of another macro `MACRO_NAME`, and (ii) a variable number of items `item_1, ..., item_n`.
Such a call would be expanded (by the C preprocessor) into a sequence of `n` applications of the given `MACRO_NAME(..)`.
In the `i`-th expanded application of `MACRO_NAME(..)`, it receives `item_i` as an argument.
APPLYXn can optionally receive additional common arguments to pass to all of the expanded applications of `MACRO_NAME(..)`.
The expanded application of `MACRO_NAME(..)` also gets the number `i` of this item it is applied on, and the total number `n` of items.

# Synopsis
Macro call:
```C
APPLYXn(MACRO_NAME, (AdditionalArgument(s)[, ...]), item_1, ..., item_n)
```
Expands into:
```C
MACRO_NAME(n, 1, additional_arg_1, [additional_arg_2, [...]] item_1)
MACRO_NAME(n, 2, additional_arg_1, [additional_arg_2, [...]] item_2)
MACRO_NAME(n, 3, additional_arg_1, [additional_arg_2, [...]] item_3)
...
MACRO_NAME(n, n, additional_arg_1, [additional_arg_2, [...]] item_n)
```
Explanation:
In each expanded application of `MACRO_NAME(..)` it gets: `MACRO_NAME(n, i, additional_arg_1, [additional_arg_2, [...]] item_i)`, where:
* `n` is the total number of items that APPLYXn got;
* `i` is the number of the current item;
* `additional_arg_1, ..., additional_arg_k` are passed (if given to `APPLYXn(..)`). 
  You can pass to `APPLYXn` none, single, or more than one additional args.
  In the last case you should wrap them within parentheses; they'll be automatically
  stripped-off when sending the args to the `MACRO_NAME` macro, as will be shown in
  the following example;
* `item_i` is the `i`-th item passed to `APPLYXn` (after the additional arguments).

# Example
```C
#include "applyxn.h"

#define A(T,N,AdditionalArgs,item) \
    C(T,N,AdditionalArgs,item);

APPLYXn(A, (1,2,3), 'a', 'b', 'c', 'd', 'e', 'f')
// Expands to:
// C(6,1,1,2,3,'a'); C(6,2,1,2,3,'b'); C(6,3,1,2,3,'c'); C(6,4,1,2,3,'d'); C(6,5,1,2,3,'e'); C(6,6,1,2,3,'f');
APPLYXn(A, (), 'a', 'b', 'c', 'd', 'e', 'f')
// Expands to:
// C(6,1,,'a'); C(6,2,,'b'); C(6,3,,'c'); C(6,4,,'d'); C(6,5,,'e'); C(6,6,,'f');
APPLYXn(A, 1, 'a', 'b', 'c', 'd', 'e', 'f')
// Expands to:
// C(6,1,1,'a'); C(6,2,1,'b'); C(6,3,1,'c'); C(6,4,1,'d'); C(6,5,1,'e'); C(6,6,1,'f');
APPLYXn(A, , 'a', 'b', 'c', 'd', 'e', 'f')
// Expands to:
// C(6,1,,'a'); C(6,2,,'b'); C(6,3,,'c'); C(6,4,,'d'); C(6,5,,'e'); C(6,6,,'f');
```

# Files
* `applyxn.h` is actually the sole file that should be `#include`d in order to use `APPLYXn()`. It supports up to 64 items per call.
* `applyxn-generator.py` is a python script that generates `applyxn.h`. It can get an integer as an input which is the maximum number of items that `APPLYXn()` can get. If you need to support more than 64 items, you can use this script to re-generate `applyxn.h` accordingly.
* `test.c` consists a demonstraction of a minimalist usage example.
