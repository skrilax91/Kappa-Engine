cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(KappaEngine CONFIG REQUIRED)

add_executable(test src/test.cpp)
target_link_libraries(test KappaEngine::KappaEngine)
message(STATUS "KappaEngine_INCLUDE_DIRS: ${KappaEngine_INCLUDE_DIRS}")
target_include_directories(test PRIVATE ${KappaEngine_INCLUDE_DIRS})