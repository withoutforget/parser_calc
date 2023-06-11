#pragma once

enum class operator_type : char {
	op_plus = '+',
	op_minus = '-',
	op_mul = '*',
	op_div = '/'
};

enum class brace_type : char { open_brace = '(', closed_brace = ')' };

enum class LexemType : size_t {
	null,
	number,
	op,
	brace,
	expression,
	expression_string
};
