## other
- use `(uint8_t*)<some datatype>` for byte precision pointer arithmetic
- use `#pragma once` in header files instead of ifdef *header_name*, endif

## struct
- copy by assign: struct s1, s2 -> `s1 = s2`
- if struct has pointer members, s1 = s2 `shallow copy`
    s1.string = strdup(s2.string) `deep copy`
- this is possible -> `union { struct; array }` if struct and array same size
    This way one has the benefits of using struct for readability
    and the array for itteration. `vector.x, vector.data[i++]`.
- arrays decay to pointers to their first element when used in expressions
    array name represents the location of its data in memory, its fixed, meaning
    an array name allways refers to the same block of memory
    arrays have automatic memory allocation
- struct padding shouldnt be a problem for naturally alligned values.
    different size values can have padding between, small values of same size at the end

## cc
- flags `-S -fverbose=asm` to compile inte verbose assembly
- use flag `-fsanitize=address` to detect memory problems when executing binary

## LLDB
- use `memory read <variable>/<address>` print hexdump of memory at var or address
