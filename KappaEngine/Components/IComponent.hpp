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
     * @brief IComponent is an interface from which every component inherits.
     * 
     * It only contains an "enabled" boolean ffor the systems to know if they must handle the component or not.
     * 
     */
    class IComponent {
        public:
            virtual ~IComponent() = default;
            bool enabled = true;
    };
}

#endif //KAPPA_ENGINE_ICOMPONENT_HPP
