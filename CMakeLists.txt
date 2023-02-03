cmake_minimum_required(VERSION 3.24)
project (KappaEngine LANGUAGES CXX VERSION 0.0.1)
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

        "src/Systems/RigidBodySystem.cpp"
        "src/Systems/CollideBoxSystem.cpp"
        "src/Systems/SpriteRendererSystem.cpp"
        "src/Systems/NetworkSystem.cpp"

        )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Asio REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include )

target_link_libraries(${PROJECT_NAME} sfml::sfml asio::asio)

install(TARGETS ${PROJECT_NAME})