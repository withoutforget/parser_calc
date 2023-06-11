#pragma once

#include "interpret.h"



int main() {
	try {
		const std::string expr = "(1+2)*3*4+5/2-5";
		Lexer slexer;
		auto lexems = slexer.start(expr);
		Interpretator calc(lexems);
		std::cout << expr << " = " << calc.calculate() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception.\n";
	}
	std::cin.get();
}
