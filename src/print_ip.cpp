#include <cstdlib>

#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>

#include "lib.hpp"

using std::literals::string_literals::operator "" s;

template <typename X>
class proxy { // Non-owning
private:
	X const &x;

public:
	explicit proxy(X const &x) noexcept: x{x} {
	}

	friend std::ostream &operator <<(std::ostream &o, proxy<X> const &p) {
		usr::print_ip(p.x, o);
		return o;
	}
};

int main() try {
	std::cout.exceptions(std::ostream::badbit | std::ostream::failbit | std::ostream::eofbit);

	std::cout << proxy{char{-1}} << std::endl;
	std::cout << proxy{short{}} << std::endl;
	std::cout << proxy{2130706433} << std::endl;
	std::cout << proxy{long{8875824491850138409}} << std::endl;

	std::cout << proxy{"IP address (std::string)"s} << std::endl;
	std::cout << proxy{std::vector{'v', 'e', 'c', 't', 'o', 'r'}} << std::endl;
	std::cout << proxy{std::list{std::numeric_limits<long>::min(), std::numeric_limits<long>::max()}} << std::endl;
	std::cout << proxy{std::tuple<int, int, int, int, int, int>{-1, 0, 15, 255, 65535, 16777215}} << std::endl;

	return EXIT_SUCCESS;
} catch (std::exception const &e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Error: " << "unidentified exception" << std::endl;
	return EXIT_FAILURE;
}
