//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_HEALTH_HPP
#define R_TYPE_SERVER_HEALTH_HPP

#include "IComponent.hpp"

namespace Component {
    struct Health : IComponent {
        int health = 100;
    };
}

#endif //R_TYPE_SERVER_HEALTH_HPP
