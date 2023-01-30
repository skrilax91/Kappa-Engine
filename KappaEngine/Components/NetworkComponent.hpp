//
// Created by leo_b on 30/01/2023.
//

#ifndef KAPPA_ENGINE_NETWORKCOMPONENT_HPP
#define KAPPA_ENGINE_NETWORKCOMPONENT_HPP

#include "KappaEngine/Components/IComponent.hpp"

namespace Component {
    class NetworkComponent: public IComponent {
        public:
            NetworkComponent() = default;
            bool clientPrediction = false;
            bool ignorePrediction = false;
            bool asAuthority = false;


    };
}

#endif //KAPPA_ENGINE_NETWORKCOMPONENT_HPP
