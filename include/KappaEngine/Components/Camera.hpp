//
// Created by Sebayl on 23/01/2023.
//

#pragma once

#include <list>
#include <string>
#include "IComponent.hpp"

namespace Component {

    /**
     * @brief The Camera class
     * @def This class is used to create a camera, it will render the layers in the list
     * @def The position is the relative position of the camera
     * @def The layers are the layers to render
     * @def The camera will render the layers in the order of the list
     */
    class Camera : public IComponent {
        public:
            /**
             * @brief Construct a new Camera object.
             * @def This constructor will create a camera with a position and a list of layers to render
             *
             * @param position The relative position of the camera
             * @param layers The layers to render
             */
            Camera(struct coord2d position, sf::Vector2<unsigned int> size, std::list<std::string> layers)
                : _position(position), _size(size), _layers(std::move(layers)) {};

            struct coord2d _position;
            sf::Vector2<unsigned int> _size;
            std::list<std::string> _layers;
    };
}
