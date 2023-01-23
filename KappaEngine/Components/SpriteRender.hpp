//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_SPRITERENDER_HPP
#define R_TYPE_SERVER_SPRITERENDER_HPP

#include <string>
#include "IComponent.hpp"

struct coord2d {
    float x;
    float y;
};

namespace Component {
    struct SpriteRender : IComponent {
        struct coord2d spriteOffset {0};
        struct coord2d spriteSize {50, 50};
    };
}

#endif //R_TYPE_SERVER_SPRITERENDER_HPP
