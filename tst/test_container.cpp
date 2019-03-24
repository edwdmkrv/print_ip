#include "lib.hpp"
#include "test.hpp"

#include <vector>
#include <list>
#include <tuple>

using std::literals::string_literals::operator "" s;

template <typename X>
struct ContainerTest: testing::Test {
	static Data<X> const data[];
};

TYPED_TEST_CASE_P(ContainerTest);

TYPED_TEST_P(ContainerTest, Test) {
	test(this->data);
}

REGISTER_TYPED_TEST_CASE_P(ContainerTest, Test);

typedef testing::Types<
	std::string,
	std::vector<char>,
	std::vector<int>,
	std::vector<std::string>,
	std::list<char>,
	std::list<int>,
	std::list<std::string>,
	std::tuple<char>,
	std::tuple<char, char>,
	std::tuple<char, int>,
	std::tuple<int, int, int, int, int, int, int, int, int>,
	std::tuple<std::string, std::string, std::string>,
	std::tuple<char, int, std::string, std::vector<std::string>>
> ContainerTypes;

INSTANTIATE_TYPED_TEST_CASE_P(PrintIP, ContainerTest, ContainerTypes);

// std::string
template <>
Data<std::string> const ContainerTest<std::string>::data[]{
	{""s,           ""s},
	{"IP-address"s, "IP-address"s}
};

// std::vector<char>
template <>
Data<std::vector<char>> const ContainerTest<std::vector<char>>::data[]{
	{{'v', 'e', 'c', 't', 'o', 'r', '<', 'c', 'h', 'a', 'r', '>'}, "v.e.c.t.o.r.<.c.h.a.r.>"s},
	{{'0'                                                       }, "0"s}
};

// std::vector<int>
template <>
Data<std::vector<int>> const ContainerTest<std::vector<int>>::data[]{
	{{ -1, 1   }, "-1.1"s},
	{{  0, 0, 0}, "0.0.0"s},
	{{513      }, "513"s}
};

// std::vector<std::string>
template <>
Data<std::vector<std::string>> const ContainerTest<std::vector<std::string>>::data[]{
	{{""s                                }, ""s},
	{{""s,             ""s, ""s, ""s, ""s}, "...."s},
	{{"vector"s, "string"s               }, "vector.string"s}
};

// std::list<char>
template <>
Data<std::list<char>> const ContainerTest<std::list<char>>::data[]{
	{{'l', 'i', 's', 't', '<', 'c', 'h', 'a', 'r', '>'}, "l.i.s.t.<.c.h.a.r.>"s},
	{{'0', '1', '2', '3'                              }, "0.1.2.3"s}
};

// std::list<int>
template <>
Data<std::list<int>> const ContainerTest<std::list<int>>::data[]{
	{{-1},  "-1"s},
	{{0},   "0"s},
	{{513}, "513"s}
};

// std::list<std::string>
template <>
Data<std::list<std::string>> const ContainerTest<std::list<std::string>>::data[]{
	{{"list"s, "string"s}, "list.string"s},
	{{""s               }, ""s}
};

// std::tuple<char>
template <>
Data<std::tuple<char>> const ContainerTest<std::tuple<char>>::data[]{
	{{'a'}, "a"s},
	{{'0'}, "0"s}
};

// std::tuple<char, char>
template <>
Data<std::tuple<char, char>> const ContainerTest<std::tuple<char, char>>::data[]{
	{{'a', 'b'}, "a.b"s},
	{{'0', '1'}, "0.1"s}
};

// std::tuple<char, int>
template <>
Data<std::tuple<char, int>> const ContainerTest<std::tuple<char, int>>::data[]{
	{{'a', 1}, ""s, false},
	{{'0', 0}, ""s, false}
};

// std::tuple<int, int, int, int, int, int, int, int, int>
template <>
Data<std::tuple<int, int, int, int, int, int, int, int, int>> const ContainerTest<std::tuple<int, int, int, int, int, int, int, int, int>>::data[]{
	{{0,  0, 0,   0,    0,    0,    0,     0,     0}, "0.0.0.0.0.0.0.0.0"s},
	{{-1, 0, 1, 513, 1023, 1024, 1025, 65535, 65536}, "-1.0.1.513.1023.1024.1025.65535.65536"s}
};

// std::tuple<std::string, std::string, std::string>
template <>
Data<std::tuple<std::string, std::string, std::string>> const ContainerTest<std::tuple<std::string, std::string, std::string>>::data[]{
	{{""s,            ""s,              ""s}, ".."s},
	{{"tuple"s, "string"s, "string.string"s}, "tuple.string.string.string"s}
};

// std::tuple<char, int, std::string, std::vector<std::string>>
template <>
Data<std::tuple<char, int, std::string, std::vector<std::string>>> const ContainerTest<std::tuple<char, int, std::string, std::vector<std::string>>>::data[]{
	{{'a', 1, "2"s, {"255"s}}, ""s, false},
	{{'0', 0, ""s,        {}}, ""s, false}
};
