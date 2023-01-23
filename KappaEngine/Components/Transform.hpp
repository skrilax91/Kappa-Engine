//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_TRANSFORM_HPP
#define KAPPA_ENGINE_TRANSFORM_HPP

#include <vector>

#include "IComponent.hpp"

struct coord2d {
    float x;
    float y;
};

namespace Component {
    class Transform: public IComponent {
        public:
            Transform(coord2d pos, coord2d scale, coord2d rotation) : position(pos), scale(scale), rotation(rotation) {};
            coord2d position{};
            coord2d scale{};
            coord2d rotation{};
    };
}

#endif //KAPPA_ENGINE_TRANSFORM_HPP
