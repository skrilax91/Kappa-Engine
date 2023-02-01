//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_TRANSFORM_HPP
#define KAPPA_ENGINE_TRANSFORM_HPP

#include <vector>

#include "IComponent.hpp"

namespace Component {

    /**
     * @brief The Transform component contains:
     *  - The absolute position of an Entity in the scene
     *  - The scale of an Entity
     *  - The rotation of an Entity
     */
    class Transform: public IComponent {
        public:
            Transform(sf::Vector2f pos, coord2d scale, coord2d rotation) : position(pos), scale(scale), rotation(rotation) {};
            sf::Vector2f position{};
            coord2d scale{};
            coord2d rotation{};
    };
}

#endif //KAPPA_ENGINE_TRANSFORM_HPP
