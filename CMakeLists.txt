cmake_minimum_required(VERSION 3.19)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(semiproducts/include
                    net_nodes/include
                    factory/include)

set(SOURCE_FILES
        semiproducts/src/package.cpp
        semiproducts/src/storage_types.cpp
        net_nodes/src/nodes.cpp
        factory/src/factory.cpp
        )
set(SOURCE_FILES_TESTS
        test/semiproducts_tests.cpp
        )

add_executable(NetSim__test ${SOURCE_FILES} ${SOURCE_FILES_TESTS} test/main_gtest.cpp)


target_include_directories(NetSim__test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(../googletest-master googletest-master)
target_link_libraries(NetSim__test gmock)

add_executable(NetSim__debug ${SOURCE_FILES} main.cpp)# semiproducts/include/package.hpp semiproducts/include/types.hpp semiproducts/include/storage_types.hpp semiproducts/src/package.cpp factory/include/factory.hpp net_nodes/include/nodes.hpp net_nodes/src/nodes.cpp factory/src/factory.cpp semiproducts/src/storage_types.cpp)
