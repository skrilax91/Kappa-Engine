cmake_minimum_required(VERSION 3.22)
project (KappaEngine LANGUAGES CXX VERSION 0.6.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file (GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB SOURCE_FILES
        "src/GameManager.cpp"
        "src/Time.cpp"
        "src/Input.cpp"
        "src/EntityManager.cpp"
        "src/SystemManager.cpp"
        "src/Scene.cpp"

        "src/Interfaces/Utils.cpp"
        "src/Interfaces/Canvas.cpp"
        "src/Interfaces/ButtonInterface.cpp"
        "src/Interfaces/TextInterface.cpp"
        "src/Interfaces/ImageInterface.cpp"

        "src/Managers/InterfaceManager.cpp"
        "src/Managers/TextureManager.cpp"

        "src/Systems/RigidBodySystem.cpp"
        "src/Systems/CollideBoxSystem.cpp"
        "src/Systems/SpriteRendererSystem.cpp"
        "src/Systems/NetworkSystem.cpp"
        "src/Systems/TriggerBoxSystem.cpp"
        "src/Systems/AnimationSystem.cpp"

        "src/Console/Console.cpp"
        "src/Console/Command.cpp"

        "src/Network/NetworkConnection.cpp"

        )

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
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

file (GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB TEST_SOURCE_FILES "tests/*.cpp")

message(STATUS "HEADERS: ${HEADERS}")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(asio REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES} ${SOURCE_FILES})

enable_testing()

message(STATUS "GTEST: ${GTest_INCLUDE_DIRS}")

target_include_directories(${PROJECT_NAME} PUBLIC include ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIR} ${GTest_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio asio::asio GTest::GTest GTest::Main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})