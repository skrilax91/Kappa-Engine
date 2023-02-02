//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_IINTERFACE_HPP
#define KAPPA_ENGINE_IINTERFACE_HPP

namespace Interface {

    enum Anchor {
        TOP_LEFT,
        TOP_RIGHT,
        TOP_CENTER,

        CENTER_LEFT,
        CENTER_RIGHT,
        CENTER_CENTER,

        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        BOTTOM_CENTER,
    };


    class IInterface {
        public:
            virtual ~IInterface() = default;

            virtual void draw() {};

            enabled = true;
    };
}



#endif //KAPPA_ENGINE_IINTERFACE_HPP
