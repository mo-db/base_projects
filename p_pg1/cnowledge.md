# Knowledge
- use `(uint8_t*)<some datatype>` for byte precision pointer arithmetic
- use `#pragma once` in header files instead of ifdef <header name>, endif

# Clang
- flags `-S -fverbose=asm` to compile inte verbose assembly
- use flag `-fsanitize=address` to detect memory problems when executing binary

# LLDB
- use `memory read <variable>/<address>` print hexdump of memory at var or address
