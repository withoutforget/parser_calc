#pragma once

#include "lexer.h"


class Interpretator {
private:
    lexems_t f_lexems; // field_lexems
    number_t use_bin_op(const Lexem& lhs, const Lexem& op, const Lexem& rhs) {
        auto lhs_v = std::get<number_t>(lhs.data);
        auto rhs_v = std::get<number_t>(rhs.data);
        switch (std::get<operator_t>(op.data)) {
        case operator_t::op_add:
            return lhs_v + rhs_v;
        case operator_t::op_sub:
            return lhs_v - rhs_v;
        case operator_t::op_mul:
            return lhs_v * rhs_v;
        case operator_t::op_div:
            return lhs_v / rhs_v;
        case operator_t::op_exp:
            return std::pow(lhs_v, rhs_v);
        }
        throw 0;
    }

    number_t calculate_op(lexems_t& lexems, operator_t op = operator_t::op_mul) {
        auto has_op_pred = [op](const auto& lex) -> bool {
            if (lex.type != LexemType::op) return false;
            return std::get<operator_t>(lex.data) == op;
        };
        while (true) {  // handle all multiply
            auto it = std::find_if(lexems.begin(), lexems.end(), has_op_pred);
            if (it == lexems.end()) break;
            auto& op = *it;
            // UB if iterator equals to begin or end-1
            auto& lhs = *(it - 1);
            auto& rhs = *(it + 1);
            if (lhs.type != LexemType::number || lhs.type != LexemType::number)
                throw std::runtime_error{ "Wrong lexems near operator" };
            Lexem result;
            result.type = LexemType::number;
            result.data = use_bin_op(lhs, op, rhs);
            std::swap(lhs, result);
            lexems.erase(it + 1);
            lexems.erase(it);
        }
        if (lexems.size() == 1 && lexems[0].type == LexemType::number)
            return std::get<number_t>(lexems[0].data);
        return 0;
    }

    number_t calculate_recursion(lexems_t& lexems) {
        for (auto& el : lexems) { // calculate next expressions
            if (el.type == LexemType::expression) {
                shared_lexems_t lexems_ptr = std::get<shared_lexems_t>(el.data);
                auto result = calculate_recursion(*lexems_ptr);
                // if lexems_ptr has expression in there then we got maybe deep recursion in previous line
                el.type = LexemType::number;
                el.data = result;
            }
        }

        number_t result{};

        for (auto op : usable_operators) {
            result = calculate_op(lexems, op);
            if (result != 0)
                return result;
        }
    }

public:
    Interpretator(const lexems_t& lexems) : f_lexems(lexems) {}
    Interpretator(lexems_t&& lexems) : f_lexems(std::move(lexems)) {}
    number_t calculate() {
        lexems_t& lexems = f_lexems;

        return calculate_recursion(lexems);

        /*
        for (auto& el : lexems) { // calculate next expressions
            if (el.type == LexemType::expression) {
                shared_lexem_t lexems_ptr = std::get<shared_lexem_t>(el.data);
                auto result = calculate_recursion(*lexems_ptr);
                // if lexems_ptr has expression in there then we got maybe deep recursion in previous line
                el.type = LexemType::number;
                el.data = result;
            }
        }

        if (auto r1 = calculate_op(lexems, operator_t::op_mul); r1 != 0) return r1;
        if (auto r2 = calculate_op(lexems, operator_t::op_div); r2 != 0) return r2;
        if (auto r3 = calculate_op(lexems, operator_t::op_add); r3 != 0) return r3;
        return calculate_op(lexems, operator_t::op_sub);*/
    }
};