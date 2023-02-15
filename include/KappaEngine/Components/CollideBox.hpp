//
// Created by Sebayl on 23/01/2023.
//

#ifndef R_TYPE_SERVER_COLLIDEBOX_HPP
#define R_TYPE_SERVER_COLLIDEBOX_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "IComponent.hpp"

namespace Component {
    class CollideBox : public IComponent {
        public:
            CollideBox(sf::FloatRect &collideBox, std::string &tag,
                std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onCollideEnter =  nullptr,
                std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onCollideExit = nullptr,
                std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> onCollideStay = nullptr,
                std::vector<std::string> collidingTags = {})
                    : _collideBox(collideBox), _tag(tag), _collidingTags(collidingTags),
                    _onCollideEnter(onCollideEnter), _onCollideExit(onCollideExit), _onCollideStay(onCollideStay) {};

            sf::FloatRect _collideBox;
            std::list<CollideBox &> _collided = {};
            std::string _tag;
            std::vector<std::string> _collidingTags;

            std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideEnter;
            std::function<void(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideExit;
            std::function<bool(std::shared_ptr<KappaEngine::Entity>, std::shared_ptr<KappaEngine::Entity>)> _onCollideStay;
    };
}

#endif //R_TYPE_SERVER_COLLIDEBOX_HPP
