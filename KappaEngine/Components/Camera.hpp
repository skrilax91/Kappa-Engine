//
// Created by Sebayl on 23/01/2023.
//

#include <list>
#include <string>
#include "IComponent.hpp"

struct coord2d {
    float x;
    float y;
};

namespace Component {
    class Camera : public IComponent {
        public:
            Camera(struct coord2d position, std::list<std::string> layers)
                : _position(position), _layers(std::move(layers)) {};
            
            struct coord2d _position;
            std::list<std::string> _layers;
    };
}