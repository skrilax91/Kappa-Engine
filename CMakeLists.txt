cmake_minimum_required(VERSION 3.24)
project (KappaEngine VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCE_FILES
        "src/EntityManager.cpp"
        "src/SystemManager.cpp"
        "src/Scene.cpp"

        "src/Systems/RigidBodySystem.cpp"
        "src/Systems/CollideBoxSystem.cpp"

        )

file(GLOB HEADER_FILES
        "KappaEngine/Scene.hpp"
        "KappaEngine/EntityManager.hpp"
        "KappaEngine/SystemManager.hpp"

        "KappaEngine/Systems/ISystem.hpp"
        "KappaEngine/Systems/RigidBodySystem.hpp"
        "KappaEngine/Systems/CollideBoxSystem.hpp"

        "KappaEngine/Entity/Entity.hpp"

        "KappaEngine/Components/IComponent.hpp"
        "KappaEngine/Components/Transform.hpp"
        "KappaEngine/Components/RigidBody.hpp"
        )

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/KappaEngine DESTINATION include)