//
// Created by Sebayl on 02/02/2023.
//

#ifndef KAPPA_ENGINE_TEXT_HPP
#define KAPPA_ENGINE_TEXT_HPP

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class ImageComponent : public IInterface {
        public:
            ImageComponent() = default;

            sf::Vector2f position = {0, 0};
            sf::Vector2f rotation = {0, 0};
            sf::Vector2f scale = {0, 0};

            Anchor anchor = Anchor::TOP_LEFT;

            sf::Sprite sprite = sf::Sprite();
            std::string texturePath = "";
            sf::IntRect textureRect = {0, 0, 50, 100};

            void draw() override;
    };

} // Interface

#endif //KAPPA_ENGINE_TEXT_HPP