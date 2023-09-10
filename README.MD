##Usage

```cpp
#pragma once

#include "interpret.h"
#include "tests.hpp"

constexpr bool test = false;

int main() {

	if constexpr (test) {
		TEST::try_test();
		return (std::cin.get(), 0);
	}

	while (true) {
		try {
			std::string str;
			std::cin >> str;
			Lexer lexer;
			Interpretator calc(lexer.start(str));
			std::cout << str << " = " << calc.calculate() << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
		catch (...) {
			std::cout << "Unknown exception.\n";
		}
	}
	std::cin.get();
}
```
Examples:
```
2+0.2*(1/3+1/2^4) = 2.07917
1+(2+(3+(4+(5+(6+(7+(8+(9+10)))))))) = 55
```
