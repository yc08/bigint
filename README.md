# Bigint Calculator

A portable C++ big integer library and calculator supporting arithmetic and bitwise operations on arbitrarily large signed integers.  
Implements a template `Bigint<N>` (where `N` is the bit width) and a command-line calculator for interactive use.

## Features

- **Bigint Template:** `Bigint<N>` for signed integers of any bit width (e.g. 128, 256, 512).
- **Arithmetic:** Addition, subtraction, multiplication, division, modulo.
- **Bitwise:** AND, OR, XOR, NOT, bit shifts.
- **Mixed-size:** Operators promote operands to the larger bit width.
- **Decimal I/O:** Parse decimal strings and print results as decimal.
- **Calculator:** Interactive command-line calculator supporting expressions with `+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`, parentheses.
- **No external dependencies:** Uses only standard C++ headers.

## Build

Open a terminal in the project folder and compile:

**g++ (recommended):**
```bash
g++ calculator.cpp -o calculator
```

**MSVC (Developer Command Prompt):**
```bat
cl /EHsc /std:c++17 /W4 calculator.cpp
```

## Usage

Run the calculator:

```powershell
.\calculator
```

Enter an expression (all on one line), e.g.:
```
123456789123456789 + 987654321098765432
```
or
```
(123456789123456789 * 2) ^ 42
```
The result will be printed in decimal.

## Example

```
> 1000000000000000000000000000000 * 123456789
123456789000000000000000000000000
------------
```

## API Reference

- **Constructors:**
  - `Bigint<256> a(42);`
  - `Bigint<128> b("12345678901234567890");`
- **Operators:** `+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`, `<<`, `>>`, comparisons.
- **Decimal output:** `std::cout << a.num() << '\n';`
- **Bitwise:** `a & b`, `a | b`, `a ^ b`, `~a`
- **Mixed-size:** `Bigint<256> + Bigint<128>` returns `Bigint<256>`

## Limitations

- Overflow wraps/truncates at the template bit width.
- Decimal parsing/printing is portable, but very large numbers may be slow.
- For production use, consider GMP or Boost.Multiprecision.
