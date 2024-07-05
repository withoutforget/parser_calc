#pragma once
#include <string>
#include <string_view>
#include <memory>
#include <functional>
#include <utility>

class token {
public:
	virtual ~token() = default;

	virtual std::string_view get_value() const = 0;
	virtual void set_value(std::string_view) = 0;

	virtual bool is_valid(std::string_view) const = 0;

	virtual std::string_view type() const = 0;
	virtual std::unique_ptr<token> clone() const = 0;
};

/* token which has always the same value  */
class static_token : virtual public token {
protected:
	std::string m_type;
	std::string m_value;
public:
	static_token(std::string_view value, std::string_view type) : m_value(value), m_type(type) {}
	virtual ~static_token() = default;

	virtual std::string_view get_value() const override { return m_value; }
	virtual void set_value(std::string_view) override {}

	virtual bool is_valid(std::string_view sv) const override { return sv == m_value; }

	virtual std::string_view type() const override { return m_type; }
	virtual std::unique_ptr<token> clone() const override { return std::unique_ptr<token>(new static_token(m_value, m_type)); }
};

/* token which you can validate via lambda */
class functional_token : virtual public static_token {
protected:
	std::function<bool(std::string_view)> m_predicate;
public:
	template<typename F>
	functional_token(F&& validator, std::string_view type) : static_token("", type), m_predicate(std::forward<F>(validator)) {}

	virtual ~functional_token() = default;

	virtual void set_value(std::string_view value) override { m_value = value; }
	virtual bool is_valid(std::string_view value) const override { return m_predicate(value); }
	virtual std::unique_ptr<token> clone() const override { return std::unique_ptr<token>(new functional_token(m_predicate, m_type)); }
};
