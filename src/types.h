#pragma once

#include <memory>
#include <string>
#include <vector>

#include "enums.h"

using number_t = long double;
inline number_t string_to_number_t(const std::string& str) {
	return std::stold(str);
}

using operator_t = operator_type;
using brace_t = brace_type;

struct Lexem;
using lexem_t = std::vector<Lexem>;
using shared_lexem_t = std::shared_ptr<lexem_t>;
using expression_t = std::string;