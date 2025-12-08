*This project has been created as part of the 42 curriculum by amtan.*

# ft_printf

---

## Description

`ft_printf` is a reimplementation of the standard C `printf` function, written in C and packaged as a static library named `libftprintf.a`.

The goal of the project is to:

* Discover and practice **variadic functions** using `va_list`, `va_start`, `va_arg` and `va_end`.
* Understand how formatted output works by re‑creating a subset of `printf`.
* Produce clean, extensible, and **Norm-compliant** C code that can be reused in future 42 projects.

This version of `ft_printf` focuses on the mandatory part of the subject: it does **not** implement buffering or all of the original `printf` features, but it does correctly handle the required conversions and return values.

### Supported conversions

`ft_printf` currently supports the following conversion specifiers from the subject:

* `%c` – print a single character
* `%s` – print a NUL-terminated C string (or `(null)` if the pointer is `NULL`)
* `%p` – print a pointer in lowercase hexadecimal, prefixed with `0x` (or `(nil)` for `NULL`)
* `%d` – print a signed decimal integer
* `%i` – same as `%d`
* `%u` – print an unsigned decimal integer
* `%x` – print an unsigned integer in lowercase hexadecimal
* `%X` – print an unsigned integer in uppercase hexadecimal
* `%%` – print a literal `%` character

The function prototype is:

```c
int ft_printf(const char *format, ...);
```

On success, `ft_printf` returns the number of characters written. On error (write failure, invalid internal state, or if the output size would overflow `INT_MAX`) it returns `-1`.

---

## Algorithm and data-structure choices

This section explains how `ft_printf` is implemented and why the chosen design fits the constraints of the project (Norm, no buffering, no dynamic memory for formatting, limited standard library, etc.).

### High-level flow

At a high level, `ft_printf` works like this:

1. Initialize a `va_list` to access the variable arguments.
2. Iterate over the format string character by character.
3. Keep a running counter `printed` (`size_t`) that tracks how many characters have already been written.
4. For each character:

   * If it is **not** `'%'`, send it directly to `write(1, ...)` through `print_char()` and update `printed`.
   * If it **is** `'%'`, look at the next character to determine the conversion specifier and dispatch to the appropriate helper function.
5. If any helper returns an error (`-1`), stop immediately, clean up the `va_list` and return `-1`.
6. At the end, if `printed` fits in an `int`, cast and return it; otherwise return `-1` to signal overflow.

This design:

* Keeps the main loop simple and readable.
* Avoids building any intermediate buffers in memory.
* Propagates errors cleanly through return values.

### Conversion dispatch

Specifier handling is done in a dedicated function that receives:

* a pointer to the current position in the format string,
* the active `va_list`,
* and the address of `printed`.

It uses a simple chain of `if`/`else if` statements to decide which helper to call:

* `%c` → `print_char()`
* `%s` → `print_str()`
* `%d`, `%i` → `print_signed_base()`
* `%u`, `%x`, `%X` → `print_unsigned_base()`
* `%p` → `print_pointer()`

Unknown specifiers (for example `%q`) are printed literally as `'%q'`: first a `%`, then the unknown character. This is a deliberate design choice to make debugging easier and to avoid silently ignoring mistakes in format strings.

A special case is handled when the format string ends with a single `%` (e.g. `"Hello %"`): the function treats this as an error and returns `-1`, rather than accessing memory past the end of the string.

### Numeric formatting strategy

All integer formatting is implemented without any dynamic memory allocation. The strategy is:

1. Convert any signed value to a **non-negative** `unsigned long` magnitude.
2. Use a **base conversion helper** that recursively prints the number digit by digit.

For unsigned values, `print_unsigned_base()` receives:

* the value as `unsigned long`,
* the target base (10 for `%u`, `%d`, `%i`; 16 for `%x`, `%X`),
* a digits string (e.g. `"0123456789abcdef"` or `"0123456789ABCDEF"`).

The recursive helper:

* Recursively prints `n / base` if `n >= base`.
* Then prints the last digit `n % base`.

This simple recursive approach:

* Avoids temporary buffers and manual index management.
* Prints digits from most significant to least significant in natural order.
* Keeps each function small and within the Norm limits (max 25 lines, max 5 local variables).

### Handling signed integers and edge cases

For `%d` and `%i`, `print_signed_base()` is responsible for:

1. Checking if the number is negative.
2. Printing a `'-'` sign if needed.
3. Converting the signed `long` into an `unsigned long` magnitude.

The conversion is carefully written to avoid undefined behavior on the smallest negative value (like `LONG_MIN`): instead of directly negating `n`, it computes the magnitude using an intermediate expression that stays in range before converting to unsigned.

Once the magnitude is computed, the function delegates the actual digits to `print_unsigned_base()`.

### Pointer representation

Pointers (`%p`) are printed using the following rules:

* `NULL` pointers are printed as `(nil)`.
* Non-`NULL` pointers are printed as `0x` followed by a lowercase hexadecimal representation of the address.

Internally, the pointer is cast to `uintptr_t`, which is an unsigned integer type guaranteed to be able to hold a converted pointer value. A small recursive helper (similar to the unsigned integer one) is used to print the hexadecimal digits.

### Shared counter and error propagation

Every helper function receives a `size_t *printed` pointer, which represents the total number of characters successfully written so far.

* `print_char()` increments this counter by 1 on success.
* Other helpers add their own local counts to it.
* Before writing a character, `print_char()` checks if `printed` is already at or above `INT_MAX`: if so, it returns `-1` to signal that the output would overflow the allowed range.

This design has several advantages:

* The return value of `ft_printf` always matches the total number of bytes written (or `-1` on error).
* All functions consistently propagate errors without using global variables.
* The implementation remains simple enough to comply with the Norm (no big structs, no complex state machine).

### Data structures

The project intentionally avoids complex data structures. The main “state” consists of:

* the `va_list` used to traverse the variadic arguments,
* the `const char *format` pointer used to iterate over the format string,
* the `size_t printed` counter,
* and local scalar variables used in numeric conversions.

This is sufficient for the mandatory part, keeps the code easy to reason about, and leaves room for future extensions (such as handling flags, width, and precision in the bonus part) if desired.

---

## Instructions

### Requirements

* A C compiler compatible with the 42 environment (e.g. `cc`, `gcc`, or `clang`).
* The usual compilation flags required by the subject: `-Wall -Wextra -Werror`.
* A POSIX environment for `write(2)`.

### Building the library

At the root of the repository:

```bash
make        # builds libftprintf.a (mandatory part)
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + make
```

After running `make`, you should see `libftprintf.a` at the root of the project.

### Using ft_printf in another project

Include the header and link the static library:

```c
/* main.c */
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s, answer = %d\n", "world", 42);
    if (count < 0)
        return (1);
    return (0);
}
```

Compile and link:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o ft_printf_demo
./ft_printf_demo
```

If you later integrate `ft_printf` into your `libft` (as allowed once the project is validated), you can add the library to that repository and adjust your main project’s Makefile accordingly.

---

## Usage examples

Here are a few quick examples of how the implemented conversions behave.

### Characters and strings

```c
ft_printf("Char: %c\n", 'A');
// Output: Char: A

ft_printf("String: %s\n", "Hello");
// Output: String: Hello

ft_printf("Null string: %s\n", (char *)NULL);
// Output: Null string: (null)
```

### Signed and unsigned integers

```c
ft_printf("Signed: %d %i\n", -42, 42);
// Output: Signed: -42 42

ft_printf("Unsigned: %u\n", 4294967295u);
// Output on 32-bit: Unsigned: 4294967295
```

### Hexadecimal and pointers

```c
ft_printf("hex: %x\n", 48879);
// Output: hex: beef

ft_printf("HEX: %X\n", 48879);
// Output: HEX: BEEF

int x = 42;
ft_printf("Pointer: %p\n", &x);
// Output: Pointer: 0x<address>

ft_printf("Null pointer: %p\n", (void *)0);
// Output: Null pointer: (nil)
```

### Literal percent sign

```c
ft_printf("Progress: 100%%\n");
// Output: Progress: 100%
```

### Error cases and undefined behavior

* Calling `ft_printf` with a `NULL` format string returns `-1`.
* A trailing `%` at the end of the format string (e.g. `"Hello %"`) is treated as an error and returns `-1`.
* Mismatched format specifiers and arguments (wrong types, not enough arguments, etc.) are undefined behavior, just like in the real `printf`.

---

## Project structure

The repository is organized as follows (mandatory part):

* `ft_printf.h` – public header with the `ft_printf` prototype and helper prototypes.
* `ft_printf.c` – core implementation: main loop, parsing, and dispatch.
* `print_char.c` – write a single character to standard output and update the counter.
* `print_str.c` – print NUL-terminated strings, handling `NULL` as `(null)`.
* `print_unsigned_base.c` – base conversion for unsigned integers (`%u`, `%x`, `%X`).
* `print_signed_base.c` – signed decimal formatting (`%d`, `%i`).
* `print_pointer.c` – pointer formatting for `%p`.
* `Makefile` – builds `libftprintf.a`, with `bonus` rule ready for future extensions.

---

## Testing

To validate `ft_printf`, you can:

* Write small custom test programs that compare `ft_printf` and the system `printf` side-by-side on many inputs.
* Use third-party community testers for the 42 `ft_printf` project (for example, Tripouille's `printfTester`), which check behavior and return values across a wide range of cases, including edge cases and some error conditions.

Manual testing is still important, especially for cases that might be undefined in the original `printf`, since most testers intentionally avoid undefined behavior.

---

## Resources

Some useful references related to this project:

* **42 subject PDF – ft_printf**: official description of the project, constraints, and required conversions.
* **`printf(3)` manual pages**: documentation of the standard `printf` family of functions and their format specifiers.
* **Variadic functions and `stdarg.h`**:

  * Articles and reference pages explaining `va_list`, `va_start`, `va_arg`, and `va_end`.
  * Tutorials on writing custom variadic functions in C.
* **Community testers** (optional): repositories that provide automated tests tailored to the 42 `ft_printf` project.

These resources were used to better understand the behavior of `printf`, the mechanics of variadic functions, and how to design robust tests.

---

## AI usage

In accordance with the 42 AI guidelines, the following describes how AI was used for this project:

* **Planning & clarification**

  * AI was used to help rephrase and clarify parts of the subject (for example, the exact list of required conversions and the expectations for the Makefile and README).
  * It also helped identify tricky edge cases (such as handling `NULL` strings, trailing `%` characters, and large output sizes) so they could be handled explicitly in the implementation.

* **Code review & refactoring suggestions**

  * After writing the code, AI was used as a reviewer to point out potential issues (error propagation, integer overflow, pointer handling) and to suggest small refactors while staying within the Norm.
  * All changes were manually reviewed, adapted, and tested by the author.

* **Documentation**

  * This README was drafted with the help of an AI assistant, then edited and validated by the author to ensure it correctly reflects the actual implementation and design choices.

* **What AI was *not* used for**

  * AI did not provide a complete drop-in implementation of `ft_printf`.
  * The final code was written, debugged, compiled, and tested by the student, who is responsible for understanding every line.

The goal of using AI here is to improve explanations, get an extra pair of eyes for reviews, and structure the documentation—not to bypass the learning process of implementing `ft_printf`.
