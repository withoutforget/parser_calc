#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <format>

#include "token.h"

class Tokenizer {
private:
	std::vector<std::unique_ptr<token>> m_tokens;
	std::vector<std::string> m_error_buffer;

	void append_to_error_buffer(std::string& s) {
		if (s.empty())
			return;
		m_error_buffer.emplace_back(std::format("Undefined token '{}'", s));
		s.clear();
	}

	std::pair<token*, size_t> search_for_tokens(std::string_view s) const {
		size_t c = 0;
		token* token{ nullptr };
		for (auto&& tok : m_tokens) {
			if (tok->is_valid(s)) {
				c++;
				token = tok.get();
			}
		}
		return { token, c };
	}

	void append_token(auto& tokens, token* original_token, std::string_view value) {
		auto tok = original_token->clone();
		tok->set_value(value);
		tokens.emplace_back(std::move(tok));
	}
public:
	std::vector<std::unique_ptr<token>> tokenize(const std::string_view input) {
		/* TODO: refactor it to make more simple */
		std::vector<std::unique_ptr<token>> tokens;
		std::string unparsed_token_string;

		for (size_t i = 0; i < input.size(); i++) {
			bool PARSE_DONE = false;
			token* last_valid_token{ nullptr };
			std::string_view last_valid_string{};

			for (size_t j = i; j < input.size(); j++) {
				std::string_view string = input.substr(i, j - i + 1);
				auto&& [token, counter] = search_for_tokens(string);

				if (counter != 0) {
					append_to_error_buffer(unparsed_token_string);
				}

				switch (counter) {
				case 0:
				{

					if (last_valid_token == nullptr && j == input.size() - 1) {
						unparsed_token_string += string[0];
					}
					if (last_valid_token == nullptr)
						continue;
					// we want to save previous result, because we can't parse anything more valid here
					append_token(tokens, last_valid_token, last_valid_string);
					i = j - 1;
					goto SECOND_LOOP_BREAK; // REPLACE TO FOR-OUT

				} break;
				case 1: {

					last_valid_string = string;
					last_valid_token = token;
					if (j == input.size() - 1) {
						append_token(tokens, last_valid_token, last_valid_string);
						PARSE_DONE = true;
						goto SECOND_LOOP_BREAK; // REPLACE TO FOR-OUT
					}
					else {
						// go next
						continue;
					}

				} break;
				}
			}
		SECOND_LOOP_BREAK:
			if (PARSE_DONE)
				break;
		}
		append_to_error_buffer(unparsed_token_string);
		return tokens;
	}

	template<typename T, typename ... Ts>
	void append_token(Ts&& ... ts) {
		m_tokens.emplace_back(new T{ std::forward<Ts>(ts)... });
	}

	auto& error_buffer() { return m_error_buffer; }

};