# BigInt Library

## Overview
The BigInt library provides a way to handle large integers in C++. It supports various operations such as addition, subtraction, multiplication, and division on integers larger than those typically supported by standard data types.

## Features
- **Arbitrary Precision**: Handle integers of any size limited only by memory.
- **Performance**: Optimized for speed and efficiency.
- **Easy to Use**: Simple interface for common operations.

## Installation
To use the BigInt library, include the header file in your project:
```cpp
#include "bigInt.h"
```

## Usage
Here is a simple example of how to use the BigInt library:
```cpp
#include "bigInt.h"

int main() {
    BigInt<100> a = "123456789012345678901234567890";
    BigInt<100> b = "987654321098765432109876543210";
    BigInt<100> c = a + b;
    std::cout << c << std::endl;
    return 0;
}
```

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any suggestions or improvements.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
