cmake_minimum_required(VERSION 3.24)
project (KappaEngine LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

file (GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB SOURCE_FILES
        "src/GameManager.cpp"
        "src/Time.cpp"
        "src/Input.cpp"
        "src/EntityManager.cpp"
        "src/SystemManager.cpp"
        "src/Scene.cpp"

        "src/Systems/RigidBodySystem.cpp"
        "src/Systems/CollideBoxSystem.cpp"
        "src/Systems/SpriteRendererSystem.cpp"
        "src/Systems/NetworkSystem.cpp"

        "src/Console/Console.cpp"
        "src/Console/Command.cpp"

        "src/Network/NetworkConnection.cpp"

        )

find_package(SFML 2.5 REQUIRED)
find_package(asio REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} sfml::sfml asio::asio)

install(TARGETS ${PROJECT_NAME})

#############################################################################################################
## TESTS
#############################################################################################################

project(KappaEngineTests LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

file (GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB TEST_SOURCE_FILES "tests/*.cpp")

message(STATUS "HEADERS: ${HEADERS}")

find_package(SFML 2.5 REQUIRED)
find_package(asio REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES})

enable_testing()

target_include_directories(${PROJECT_NAME} PUBLIC include ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIR} ${GTest_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} sfml::sfml asio::asio ${GTest_LIBRARIES})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})