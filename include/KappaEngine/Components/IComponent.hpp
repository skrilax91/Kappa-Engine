//
// Created by leo_b on 23/01/2023.
//

#ifndef KAPPA_ENGINE_ICOMPONENT_HPP
#define KAPPA_ENGINE_ICOMPONENT_HPP

struct coord2d {
    float x;
    float y;
};

namespace Component {

    /**
     * @brief Base class for all components
     */
    class IComponent {
        public:
            virtual ~IComponent() = default;
            bool enabled = true;
    };
}

#endif //KAPPA_ENGINE_ICOMPONENT_HPP
