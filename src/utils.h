#pragma once

#include <stdexcept>

#include "types.h"

namespace utils {
inline bool is_number(char c) { return (c >= '0' && c <= '9'); }

inline bool is_operator(char c) {
  using enum operator_type;
  return (c == static_cast<char>(op_plus)) ||
         (c == static_cast<char>(op_minus)) ||
         (c == static_cast<char>(op_mul)) || (c == static_cast<char>(op_div));
}

inline operator_type cast_operator(char c) {
  using enum operator_type;
  if (!is_operator(c))
    throw std::runtime_error{"Trying cast invalid char to operator_type"};
  switch (c) {
    case '+':
      return op_plus;
    case '-':
      return op_minus;
    case '*':
      return op_mul;
    case '/':
      return op_div;
  }
}

inline bool is_brace(char c) {
  using enum brace_type;
  return (c == static_cast<char>(open_brace)) ||
         (c == static_cast<char>(closed_brace));
}

inline bool is_lexem_symbol(char c) {
  return is_number(c) || is_operator(c) || is_brace(c);
}
}  // namespace utils