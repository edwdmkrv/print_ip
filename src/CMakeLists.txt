cmake_minimum_required (VERSION 3.12)

# Project stuff
project (print_ip_src
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 4 IP-address-like item print implementation program"
	HOMEPAGE_URL "https://github.com/edwdmkrv/print_ip/tree/master/src"
	LANGUAGES CXX
)

# Program stuff
add_executable (print_ip print_ip.cpp)

set_target_properties (print_ip PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
	LINK_LIBRARIES "lib;${CMAKE_THREAD_LIBS_INIT}"
)

install (TARGETS print_ip RUNTIME DESTINATION Debug/bin CONFIGURATIONS Debug)
install (TARGETS print_ip RUNTIME DESTINATION bin CONFIGURATIONS Release)
