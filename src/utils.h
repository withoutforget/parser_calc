#pragma once

#include <stdexcept>

#include "types.h"

namespace utils {
inline bool is_number(char c) { 
    return (c >= '0' && c <= '9') || number_trait::is_symbol(c);
}

inline bool is_operator(char c) {
    for (auto el : usable_operators) {
        if (c == static_cast<char>(el))
            return true;
    }
    return false;
}

inline operator_type cast_operator(char c) {
  using enum operator_type;
  if (!is_operator(c))
    throw std::runtime_error{"Trying cast invalid char to operator_type"};
  return static_cast<operator_type>(c);
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