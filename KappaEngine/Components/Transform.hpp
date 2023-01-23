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

struct coord3d {
    float x;
    float y;
    float z;
};

namespace Component {
    struct Transform: IComponent {
        coord2d position;
        coord3d scale;
        coord3d rotation;
    };
}

#endif //KAPPA_ENGINE_COMPONENT_HPP
