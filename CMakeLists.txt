cmake_minimum_required(VERSION 3.12)

project(task03 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_PREFIX_PATH_EXT "" CACHE PATH "pathes for find_package")
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH_EXT})
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

execute_process(
    COMMAND conan install -if ${CMAKE_BINARY_DIR} .
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(range "range.cpp")

add_library(range_lib "lib.cpp")

add_executable(test_range "test_range.cpp")

set_target_properties(
	range range_lib test_range PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(
	test_range PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    range_lib
    CONAN_PKG::range-v3
)

target_link_libraries(
    range
    range_lib
)

target_link_libraries(
	test_range
    ${Boost_LIBRARIES}
    range_lib
)

install(TARGETS range RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cheshirskiy-kot-courses@yandex.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(range_tests test_range)