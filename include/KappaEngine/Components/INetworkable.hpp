//
// Created by leo_b on 05/02/2023.
//

#ifndef KAPPAENGINE_INETWORKABLE_HPP
#define KAPPAENGINE_INETWORKABLE_HPP

#include "KappaEngine/Network/net_message.h"

namespace Component {
    class INetworkable {
        public:
            sf::Vector2f position{};
    };
}

#endif //KAPPAENGINE_INETWORKABLE_HPP
