#pragma once
#include "interpret.h"

namespace TEST {

	const std::vector<std::pair<std::string, number_t>> test_data = {
		{"(1+2)*3*4+5/2-5", 33.5},
		{"1+(2+(3+(4+5*2)))/2", 10.5},
	};

	void try_test() {
		for (const auto& el : test_data) {
			try {
				Lexer slexer;
				Interpretator calc(slexer.start(el.first));
				auto result = calc.calculate();
				if (number_trait::equal(result, el.second)) {
					std::cout << "[ PASSED ] \""
						<< el.first << " = "
						<< el.second << "\"\n";
				}
				else {
					std::cout << "[ FAILED ] \""
						<< el.first << " = "
						<< result << "\" [ EXPECTED =\'"
						<< el.second << "\' ]\n";
				}
			}
			catch (const std::exception& e) {
				std::cout << "Exception: " << e.what() << std::endl;
			}
			catch (...) {
				std::cout << "Unknown exception.\n";
			}
		}
	}

} // namespace TEST