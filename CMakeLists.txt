cmake_minimum_required(VERSION 3.19)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_executable(NetSim main.cpp semiproducts/include/package.hpp semiproducts/include/types.hpp semiproducts/include/storage_types.hpp semiproducts/src/package.cpp factory/include/factory.hpp net_nodes/include/nodes.hpp net_nodes/src/nodes.cpp factory/src/factory.cpp)
