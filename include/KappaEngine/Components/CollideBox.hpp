//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_COLLIDEBOX_HPP
#define R_TYPE_SERVER_COLLIDEBOX_HPP

#include <string>
#include <vector>

#include "IComponent.hpp"

namespace Component {
    class CollideBox : public IComponent {
        public:
            CollideBox(float height, float width, void (*onCollide)(std::shared_ptr<KappaEngine::Entity>))
                : _height(height), _width(width), _onCollide(onCollide) {};

            float _height = 50;
            float _width = 50;
            std::string _tag = "";
            std::vector<std::string> _collidingTags = {};
            void (*_onCollide)(std::shared_ptr<KappaEngine::Entity> other) = nullptr;
    };
}

#endif //R_TYPE_SERVER_COLLIDEBOX_HPP
