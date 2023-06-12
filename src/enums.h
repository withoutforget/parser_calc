#pragma once

enum class operator_type : char {
	op_add = '+',
	op_sub = '-',
	op_mul = '*',
	op_div = '/',
	op_exp = '^',
	op_null = '\0'
};

const std::vector<operator_type> usable_operators = {
	operator_type::op_exp,
	operator_type::op_div,
	operator_type::op_mul,
	operator_type::op_add,
	operator_type::op_sub,
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
