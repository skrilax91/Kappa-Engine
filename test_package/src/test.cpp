#include <iostream>

#include "EntityManager.hpp"

int main() {
    KappaEngine::EntityManager entityManager;

    entityManager.createEntity("test", [](KappaEngine::Entity& entity) {});


    std::cout << "Successfully passed tests" << std::endl;
    return 0;
}