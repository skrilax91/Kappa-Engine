//
// Created by Sebayl on 23/01/2023.
//

#include <list>
#include <string>
#include "IComponent.hpp"

namespace Component {
    class Camera : public IComponent {
        public:
            /**
             * @brief Construct a new Camera object.
             * @def This constructor will create a camera with a position and a list of layers to render
             *
             * @param position The relative position of the camera
             * @param layers The layers to render
             */
            Camera(struct coord2d position, std::list<std::string> layers)
                : _position(position), _layers(std::move(layers)) {};
            
            struct coord2d _position;
            std::list<std::string> _layers;
    };
}