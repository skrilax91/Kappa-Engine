//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_COMPONENT_HPP
#define KAPPA_ENGINE_COMPONENT_HPP

#include <vector>

#include "IComponent.hpp"

namespace Component {
    struct Transform: IComponent {
        float x;
        float y;
    };
}

#endif //KAPPA_ENGINE_COMPONENT_HPP
