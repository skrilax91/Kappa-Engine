//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_COMPONENT_HPP
#define KAPPA_ENGINE_COMPONENT_HPP

#include <vector>

#include "IComponent.hpp"

struct coord2d {
    float x;
    float y;
};

namespace Component {
    struct Transform: IComponent {
        coord2d position{};
        coord2d scale{};
        coord2d rotation{};
    };
}

#endif //KAPPA_ENGINE_COMPONENT_HPP
