//
// Created by leo_b on 02/03/2023.
//

#ifndef KAPPAENGINE_UTILS_HPP
#define KAPPAENGINE_UTILS_HPP

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class Utils {
        public:
            static Interface::IPosition GetAbsolutePosition(Interface::IPosition parent, Interface::IPosition child);
    };
}

#endif //KAPPAENGINE_UTILS_HPP
