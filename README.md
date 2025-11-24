# bigint

Provides a `Bigint<N>` template (N = bit width) and arithmetic / comparison operators. Portable C++ (no compiler 128-bit extensions required).

## Features
- Template: `Bigint<N>` where `N` is bit width (e.g. 128, 256).
- Signed two's‑complement representation.
- Arithmetic: `+`, `-`, `*`, `/`.
- Mixed-size operators: expressions like `Bigint<256> + Bigint<128>` promote operands to `Bigint<max(A,B)>`.
- Bit shifts `<<`, `>>`, increments/decrements.
- Comparison operators `<, <=, >, >=, ==`.
- Decimal I/O: parse decimal strings in constructor and `num()` to obtain full decimal output (portable, no `__int128`).
- Uses only standard headers (`<bitset>`, `<string>`, `<iostream>`, etc.).

## Build

Open a terminal in the project folder (`C:\Users\User\Desktop\bigint`) and run:

- g++ (recommended)
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o bigint bigInt.cpp
```

- MSVC (Developer Command Prompt)
```bat
cl /EHsc /std:c++17 /W4 bigInt.cpp
```

Run:
```powershell
.\bigint    # Windows
```

## Usage (program)
The provided `main()` reads:
1. a decimal number (string)
2. an operator character (`+`, `-`, `*`, `/`)
3. a second decimal number

Example interactive run:
```
> 123456789123456789
> +
> 987654321098765432
# prints the decimal result
```

The program constructs `Bigint<256>` for the first operand and `Bigint<128>` for the second, then performs the requested operation and prints the decimal result via `.num()`.

## API quick reference

- Construct:
  - `Bigint<128> a(42);`
  - `Bigint<256> b("12345678901234567890");`
- Mixed-size add:
  - `auto c = a + b; // returns Bigint<max(A,B)>`
- Decimal output:
  - `std::cout << c.num() << '\n';`
- Other operators behave as usual (`-`, `*`, `/`, comparisons, shifts).

## Notes & Limitations
- Decimal parsing/printing is implemented portably without `__int128`. Very large decimal strings may throw `std::out_of_range`.
- Overflow beyond the template bit width wraps/truncates in current arithmetic implementation; when mixing sizes the result has width `max(A,B)`.
- The implementation is intended as a learning/simple big-int; for production use consider GMP, Boost.Multiprecision, or similar libraries.

## Contributing / Extending
- Add better overflow handling (return wider type or error).
- Implement additional I/O (istream), bitwise ops, and optimizations.
- Add unit tests.

License: MIT (or choose your preferred license)
