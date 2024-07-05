#pragma once

#include <vector>
#include <utility>
#include <optional>
/*
default state is T{}
*/

template<typename T>
class FSM {
private:
	std::vector<std::pair<T, T>> m_data;
	T m_state{};
	T m_def_state{};
public:
	FSM(const T& default_state) : m_state(default_state), m_def_state(default_state) {}

	void add(const T& l, const T& r) {
		m_data.emplace_back(l, r);
	}

	template<typename Cont = std::vector<T>>
	void add(const T& l, Cont&& cont) {
		for (auto&& el : std::forward<Cont>(cont))
			m_data.emplace_back(l, el);
	}

	template<typename Cont = std::vector<T>>
	void add(Cont&& cont, const T& r) {
		for (auto&& el : std::forward<Cont>(cont))
			m_data.emplace_back(el, r);
	}

	std::optional<T> next(const T& v) {
		for (auto& p : m_data) {
			if (p.first == m_state && p.second == v) {
				m_state = p.second;
				return p.second;
			}
		}
		return std::nullopt;
	}

	T& current() { return m_state; }

	void reset() {
		m_state = m_def_state;
	}
};