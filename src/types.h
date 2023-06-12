#pragma once

#include <memory>
#include <string>
#include <vector>

#include "enums.h"

using number_t = long double;

template<typename T>
struct number_traits {};

template<>
struct number_traits<number_t> {
	static const std::vector<char> additional_symbols;

	static bool is_symbol(char c) {
		for (const auto& sym : additional_symbols) {
			if (c == sym)
				return true;
		}
		return false;
	}

	static number_t from_string(const std::string& str) {
		return std::stold(str);
	}
	static bool equal(const number_t& lhs, const number_t& rhs) {
		return (std::abs(lhs - rhs) < 0.1);
	}
};

const std::vector<char> number_traits<number_t>::additional_symbols = { '.' };


using number_trait = number_traits<number_t>;

using operator_t = operator_type;
using brace_t = brace_type;

struct Lexem;
using lexems_t = std::vector<Lexem>;
using shared_lexems_t = std::shared_ptr<lexems_t>;
using expression_t = std::string;