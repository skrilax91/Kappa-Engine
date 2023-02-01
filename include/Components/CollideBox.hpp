//
// Created by sebay on 23/01/2023.
//

#ifndef R_TYPE_SERVER_COLLIDEBOX_HPP
#define R_TYPE_SERVER_COLLIDEBOX_HPP

#include "IComponent.hpp"

namespace Component {
    struct CollideBox : IComponent {
        float height = 50;
        float width = 50;
    };
}

#endif //R_TYPE_SERVER_COLLIDEBOX_HPP
