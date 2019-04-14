cmake_minimum_required (VERSION 3.12)

# Project stuff
project (print_ip_pkg
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 4 IP-address-like item print implementation package"
	HOMEPAGE_URL "https://github.com/edwdmkrv/print_ip/tree/master/pkg"
	LANGUAGES CXX
)

# CPack stuff
set (CPACK_GENERATOR DEB)

set (CPACK_COMPONENT_PROG_DESCRIPTION
"print_ip
The sample C++ IP-address-like item print program.")

set (CPACK_DEB_COMPONENT_INSTALL ON)
set (CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set (CPACK_PACKAGE_ARCHITECTURE "amd64")
set (CPACK_PACKAGE_CONTACT myname@company.com)
set (CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

include (CPack)
