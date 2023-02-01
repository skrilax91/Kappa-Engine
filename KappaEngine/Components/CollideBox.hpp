//
// Created by sebay on 23/01/2023.
//

#ifndef R_TYPE_SERVER_COLLIDEBOX_HPP
#define R_TYPE_SERVER_COLLIDEBOX_HPP

#include "IComponent.hpp"

namespace Component {

    /**
     * @brief the CollideBox component contains the height and width of the box used for collisions on the Entity it's attached to.
     * 
     */
    class CollideBox : IComponent {
        float height = 50;
        float width = 50;
    };
}

#endif //R_TYPE_SERVER_COLLIDEBOX_HPP
