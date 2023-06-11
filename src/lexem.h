#pragma once

#include <iostream>
#include <variant>

#include "utils.h"

struct Lexem {
    std::variant<number_t, operator_t, brace_t, shared_lexem_t, expression_t>
        data;
    LexemType type;
    friend std::ostream& operator<<(std::ostream& os, const Lexem& rhs);
};

inline std::ostream& operator<<(std::ostream& os, const Lexem& rhs) {
    using enum LexemType;
    switch (rhs.type) {
    case null:
        break;
    case number:
        os << std::get<number_t>(rhs.data);
        break;
    case op:
        os << static_cast<char>(std::get<operator_t>(rhs.data));
        break;
    case brace:
        os << static_cast<char>(std::get<brace_t>(rhs.data));
        break;
    case expression: {
        auto is_expr = std::holds_alternative<expression_t>(rhs.data);
        if (is_expr)
            os << std::get<expression_t>(rhs.data);
        else {
            decltype(auto) ptr = std::get<shared_lexem_t>(rhs.data);
            for (auto& el : *ptr) {
                os << el << ' ';
            }
        }
        break;
    }
    }
    return os;
}