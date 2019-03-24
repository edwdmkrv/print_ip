#include "lib.hpp"
#include "test.hpp"

#include <string>

using std::literals::string_literals::operator "" s;

template <typename X>
struct IntegralTest: testing::Test {
	static Data<X> const data[];
};

TYPED_TEST_CASE_P(IntegralTest);

TYPED_TEST_P(IntegralTest, Test) {
	test(this->data);
}

REGISTER_TYPED_TEST_CASE_P(IntegralTest,
	Test
);

typedef testing::Types<
	bool,
	char,
	short,
	int,
	long
> IntegralTypes;

INSTANTIATE_TYPED_TEST_CASE_P(PrintIP, IntegralTest, IntegralTypes);

// bool
template <>
Data<bool> const IntegralTest<bool>::data[]{
	{false, ""s, false},
	{true,  ""s, false}
};

// char
template <>
Data<char> const IntegralTest<char>::data[]{
	{0,   "0"s},
	{-1,  "255"s},
	{'a', std::to_string(static_cast<unsigned>(static_cast<unsigned char>('a')))}
};

// short
template <>
Data<short> const IntegralTest<short>::data[]{
	{0,   "0.0"s},
	{-1,  "255.255"s},
	{513, "2.1"s}
};

// int
template <>
Data<int> const IntegralTest<int>::data[]{
	{0,   "0.0.0.0"s},
	{-1,  "255.255.255.255"s},
	{513, "0.0.2.1"s}
};

// long
template <>
Data<long> const IntegralTest<long>::data[]{
	{0,   "0.0.0.0.0.0.0.0"s},
	{-1,  "255.255.255.255.255.255.255.255"s},
	{513, "0.0.0.0.0.0.2.1"s}
};
