#include <iostream>

#include "KappaEngine/EntityManager.hpp"

int main() {
    KappaEngine::Scene scene("test");

    scene.getEntityManager()->createEntity("test");


    std::cout << "Successfully passed tests" << std::endl;
    return 0;
}