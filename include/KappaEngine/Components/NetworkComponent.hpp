//
// Created by leo_b on 30/01/2023.
//

#ifndef KAPPA_ENGINE_NETWORKCOMPONENT_HPP
#define KAPPA_ENGINE_NETWORKCOMPONENT_HPP

#include "IComponent.hpp"

namespace Component {

    /**
     * @brief Network component
     * @details This component is used to define if the entity is networked or not
     * @details If the entity is networked, it will be replicated on the network
     * @details If the entity is not networked, it will be only on the local machine
     *
     * @param clientPrediction If the entity is predicted by the client
     * @param ignorePrediction If the entity is predicted by the server
     * @param asAuthority If the entity is the authority of the prediction
     */
    class NetworkComponent: public IComponent {
        public:
            NetworkComponent() = default;
            NetworkComponent(uint32_t ownerId) : ownerId(ownerId) {};

            uint32_t uniqueId = 0;
            uint32_t ownerId = 0;
            bool clientPrediction = false;
            bool ignorePrediction = false;
            bool asAuthority = false;
    };
}

#endif //KAPPA_ENGINE_NETWORKCOMPONENT_HPP
