//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_COLLIDEBOX_HPP
#define R_TYPE_SERVER_COLLIDEBOX_HPP

#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/Entity/Entity.hpp"
#include "IComponent.hpp"

namespace Component {
    class CollideBox : public IComponent {
        public:
            CollideBox(sf::Vector2f dimensions, std::string tag, std::vector<std::string> collidingTags = {})
                    : _dimensions(dimensions), _tag(tag), _notCollidingTags(collidingTags) {};

            sf::Vector2f _dimensions;
            std::list<CollideBox *> _collided = {};
            std::string _tag;
            std::vector<std::string> _notCollidingTags;

            std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideEnter =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return false; };
            std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideExit =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return true; };
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideStay =
                [](std::shared_ptr<KappaEngine::Entity> entity, std::shared_ptr<KappaEngine::Entity> other){ return; };
    };
}

#endif //R_TYPE_SERVER_COLLIDEBOX_HPP
