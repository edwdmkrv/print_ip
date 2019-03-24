#ifndef __TEST_INCLUDED
#define __TEST_INCLUDED

#include "lib.hpp"

#include <string>
#include <ostream>
#include <sstream>

#include <gtest/gtest.h>

template <typename X>
struct Data {
	X const value;
	std::string const output;
	bool const specialized_print_ip_called;

	Data(X const &value, std::string const &output, bool const &specialized_print_ip_called = true):
	value{value}, output{output}, specialized_print_ip_called{specialized_print_ip_called} {
	}
};

static inline bool specialized_print_ip_called;

namespace usr {

// This "specialization" is called if those specialized print_ip versions are not called because of not meeting their std::enable_if requirements
template <typename X, typename Y = std::ostream, typename = typename std::enable_if<std::is_same<Y, std::ostream>::value>::type>
void print_ip(X const &, Y & = std::cout) {
	specialized_print_ip_called = false;
}

} // namespace usr

template <typename X, std::size_t N>
void test(Data<X> const (&data)[N]) {
	for (auto const &expected: data) {
		std::ostringstream output;
		std::ostream &o{output};

		specialized_print_ip_called = true;

		usr::print_ip(expected.value, o);

		EXPECT_EQ(expected.specialized_print_ip_called, specialized_print_ip_called);

		if (specialized_print_ip_called) {
			EXPECT_EQ(expected.output, output.str());
		}
	}
}

#endif
