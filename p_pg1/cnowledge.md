## other
- use `(uint8_t*)<some datatype>` for byte precision pointer arithmetic
- use `#pragma once` in header files instead of ifdef *header_name*, endif

## dynamic memory management
- `void* malloc(size_t size)`
- `void* calloc(size_t num, size_t size)` -> storage initialized to 0
- `void* realloc(void *ptr, size_t new_size)`
- `void free(void* ptr)` -> all mem managed by *lloc must be freed (else leak)
  - good practice: `ptr = NULL` after free()

## struct *s1, s2*
- copy by assign: `s1 = s2`
- if struct has pointer members:
  - s1 = s2 `shallow copy`
  - s1.string = strdup(s2.string) `deep copy`
- `union { struct; array }` if struct and array same size
  - struct for readability, array to itterate -> `vector.x, vector.data[i++]`

## array *a1, a2*
- arrays name decays to pointers to first element in memory 
  - meaning its fixed -> array name allways refers to the same block of memory
    arrays have automatic memory allocation
- struct padding shouldnt be a problem for natural alligned values.
- C++ `vector` is a dynamic array

## cc
- `cc -S -fverbose=asm` to compile inte verbose assembly
- `cc -S -fsanitize=address`

## LLDB
- use `memory read <variable>/<address>` print hexdump

## character processing

## string processing
- `strdup` 

## file I/O
