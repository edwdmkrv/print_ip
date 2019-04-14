#ifndef __LIB_INCLUDED
#define __LIB_INCLUDED

#include <cstdint>

#include <limits>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>

#include <version.hpp>

/* Version stuff
 */

namespace ver {

static inline std::string full() {
	return PROJECT_VERSION;
}

static inline unsigned major() {
	return PROJECT_VERSION_MAJOR;
}

static inline unsigned minor() {
	return PROJECT_VERSION_MINOR;
}

static inline unsigned patch() {
	return PROJECT_VERSION_PATCH;
}

} // namespace ver

namespace usr {

namespace internal {

enum: std::size_t {octet_digits = std::numeric_limits<uint8_t>::digits};

template <typename X, typename... Y>
struct types {
	using first_type = X;

	static inline constexpr bool are_same{
		std::is_same<X, typename types<Y...>::first_type>::value &&
		types<Y...>::are_same
	};
};

template <typename X>
struct types<X> {
	using first_type = X;

	static inline constexpr bool are_same{true};
};

template <typename X>
constexpr void print_integral(std::ostream &o, X const &x, std::size_t const n, bool const period) {
        if (n) {
                print_integral<X>(o, x >> octet_digits, n - 1, true);
                o << x % (1 << octet_digits);

                if (period) {
                        o << '.';
                }
        }
}

template <std::size_t N = 0, typename... Y>
constexpr void print_tuple(std::ostream &o, std::tuple<Y...> const &tuple) {
	o << std::get<N>(tuple);

        if constexpr (N + 1 < sizeof...(Y)) {
                o << '.';
                print_tuple<N + 1, Y...>(o, tuple);
        }
}

} // namespace internal

template <
	typename X,
	typename Y =
		typename std::make_unsigned<
			typename std::enable_if<
				std::is_integral<X>::value
				&& !std::is_same<X, bool>::value,
				X
			>::type
		>::type
>
void print_ip(X const &x, std::ostream &o = std::cout) {
	internal::print_integral(
		o,
		static_cast<Y const &>(x),
		std::numeric_limits<Y>::digits / internal::octet_digits,
		false);
}

template <
	template <typename...> typename X,
	typename... Y,
	typename =
		typename std::enable_if<
			std::is_same<std::basic_string<char>, X<char>>::value
			|| std::is_same<std::vector<char>, X<char>>::value
			|| std::is_same<std::list<char>, X<char>>::value
			|| (std::is_same<std::tuple<char>, X<char>>::value
			    && internal::types<Y...>::are_same)
		>::type
>
void print_ip(X<Y...> const &x, std::ostream &o = std::cout) {
	if constexpr (std::is_same<std::basic_string<char>, X<char>>::value) {
		o << x;
	} else if constexpr (std::is_same<std::tuple<char>, X<char>>::value) {
		internal::print_tuple(o, x);
	} else { // std::vector or std::list
		bool period{false};

		for (auto const &item: x) {
			if (period) {
				o << '.';
			} else {
				period = true;
			}

			o << item;
		}
	}
}

} // namespace usr

#endif
