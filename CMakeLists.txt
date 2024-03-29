cmake_minimum_required(VERSION 3.19)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

include_directories(include
                    include/factory
                    include/net_nodes
                    include/reports
                    include/semiproducts
                    include/simulation)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/factory.cpp
        src/helpers.cpp
        src/reports.cpp
        src/simulation.cpp
        )

add_executable(NetSim__debug ${SOURCE_FILES} main.cpp src/simulation.cpp)

set(SOURCE_FILES_TESTS
        test/mytests.cpp
        test/test_Factory.cpp
        test/test_factory_io.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_reports.cpp
        test/test_simulate.cpp
        test/test_storage_types.cpp)


add_executable(NetSim__semiproducts ${SOURCE_FILES} test/test_package.cpp test/test_storage_types.cpp test/main_gtest.cpp)
#target_compile_definitions(NetSim__semiproducts PUBLIC EXERCISE_ID=EXERCISE_ID_PACKAGES)
target_include_directories(NetSim__semiproducts PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
add_subdirectory(../googletest-master googletest-master)
target_link_libraries(NetSim__semiproducts gmock)

add_executable(NetSim__mytests ${SOURCE_FILES} test/mytests.cpp test/main_gtest.cpp)
target_include_directories(NetSim__mytests PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__mytests gmock)

add_executable(NetSim__nodes ${SOURCE_FILES} test/test_nodes.cpp test/main_gtest.cpp)
target_compile_definitions(NetSim__nodes PUBLIC EXERCISE_ID=EXERCISE_ID_FACTORY)
target_include_directories(NetSim__nodes PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__nodes gmock)

add_executable(NetSim__reports ${SOURCE_FILES} test/test_reports.cpp test/main_gtest.cpp)
#target_compile_definitions(NetSim__reports PUBLIC EXERCISE_ID=EXERCISE_ID_FACTORY)
target_include_directories(NetSim__reports PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__reports gmock)

add_executable(NetSim__factory ${SOURCE_FILES} test/test_Factory.cpp test/main_gtest.cpp)
target_compile_definitions(NetSim__factory PUBLIC EXERCISE_ID=EXERCISE_ID_FACTORY)
target_include_directories(NetSim__factory PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__factory gmock)

add_executable(NetSim__factoryIO ${SOURCE_FILES} test/test_factory_io.cpp test/main_gtest.cpp)
target_compile_definitions(NetSim__factoryIO PUBLIC EXERCISE_ID=EXERCISE_ID_REPORTING)
target_include_directories(NetSim__factoryIO PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__factoryIO gmock)

add_executable(NetSim__simulate ${SOURCE_FILES} test/test_simulate.cpp test/main_gtest.cpp)
target_compile_definitions(NetSim__simulate PUBLIC EXERCISE_ID=EXERCISE_ID_REPORTING)
target_include_directories(NetSim__simulate PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )
target_link_libraries(NetSim__simulate gmock)
