#pragma once

#include <algorithm>
#include <stack>
#include <utility>

#include "lexem.h"

class Lexer {
private:
    void clear_string(std::string& str) {
        auto it = std::remove_if(str.begin(), str.end(),
            [](char c) { return !utils::is_lexem_symbol(c); });
        str.erase(it, str.end());
    }
    // returns lexem and next pos
    std::pair<Lexem, size_t> parse_lexem_from(const std::string& str,
        LexemType type, size_t pos) {
        if (type == LexemType::null)
            throw std::runtime_error{ "Trying to parse null lexem" };
        Lexem ret;
        ret.type = type;
        if (type == LexemType::op) {
            ret.data = utils::cast_operator(str[pos]);
            return std::pair(ret, pos);
        }
        if (type == LexemType::number) {
            for (size_t i = pos; i < str.size(); i++) {
                if (!utils::is_number(str[i])) {
                    ret.data = string_to_number_t(str.substr(pos, i - pos));
                    return std::pair(ret, i - 1);
                }
            }
            ret.data = string_to_number_t(str.substr(pos, str.size() - pos + 1));
            return std::pair(ret, str.size() - 1);
        }
        if (type == LexemType::brace) {
            ret.type = LexemType::expression_string;
            std::stack<int> braces;
            for (size_t i = pos; i < str.size(); i++) {
                if (str[i] == static_cast<char>(brace_t::open_brace)) braces.push(0);
                if (str[i] == static_cast<char>(brace_t::closed_brace)) {
                    if (!braces.empty())
                        braces.pop();
                    else
                        throw std::runtime_error{ "Trying to pop empty stack" };
                }
                if (braces.empty()) {
                    ret.data = str.substr(pos + 1, i - pos - 1);
                    return std::pair(ret, i);
                }
            }
            throw std::runtime_error{ "brace doesn't closed" };
        }
        throw std::runtime_error{ "Unkown error in parse_lexer_from()" };
    }

    lexem_t make_lexical_analysis(const std::string& str) {
        lexem_t ret;
        for (size_t i = 0; i < str.size(); i++) {
            LexemType type{};
            if (utils::is_number(str[i])) {
                type = LexemType::number;
            }
            else if (utils::is_operator(str[i])) {
                type = LexemType::op;
            }
            else if (utils::is_brace(str[i])) {
                type = LexemType::brace;
            }
            auto [lexem, next_pos] = parse_lexem_from(str, type, i);

            if (lexem.type == LexemType::expression_string) {
                if (!std::holds_alternative<expression_t>(lexem.data))
                    throw std::runtime_error{ "Wrong lexial analysis" };
                auto sptr = std::make_shared<lexem_t>(
                    make_lexical_analysis(std::get<expression_t>(lexem.data)));
                lexem.type = LexemType::expression;
                lexem.data = sptr;
            }
            ret.emplace_back(std::move(lexem));
            i = next_pos;
        }
        return ret;
    }

public:
    lexem_t start(std::string str) {
        clear_string(str);
        return make_lexical_analysis(str);
    }
};