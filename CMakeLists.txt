cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

find_package(Boost CONFIG COMPONENTS unit_test_framework REQUIRED)

add_library(ip_filter_lib ip_filter.cpp)
add_executable(ip_filter main.cpp)
add_executable(test_ip_filter test_ip_filter.cpp)

set_target_properties(ip_filter_lib ip_filter test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE ip_filter_lib)

target_compile_definitions(test_ip_filter PRIVATE BOOST_TEST_DYN_LINK)
target_link_libraries(test_ip_filter PRIVATE
    Boost::unit_test_framework
    ip_filter_lib
)

if(MSVC)
    target_compile_options(ip_filter_lib PRIVATE /W4)
    target_compile_options(ip_filter PRIVATE /W4)
    target_compile_options(test_ip_filter PRIVATE /W4)
else()
    target_compile_options(ip_filter_lib PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

enable_testing()
add_test(test_ip_filter test_ip_filter)
