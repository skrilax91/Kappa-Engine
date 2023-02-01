//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_BUTTONCOMPONENT_HPP
#define KAPPA_ENGINE_BUTTONCOMPONENT_HPP

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class ButtonComponent: public IInterface {
        public:
            ButtonComponent() = default;

            sf::Vector2f position = {0, 0};
            sf::Vector2f size = {0, 0};
            Anchor anchor = Anchor::TOP_LEFT;

            sf::Color color = sf::Color::White;

            std::string text = "";
            sf::Color textColor = sf::Color::Black;
            sf::Font font = sf::Font();


            std::function<void()> onClick;
            std::function<void()> onRelease;

            std::function<void()> onHover;
            std::function<void()> onUnhover;
    };
}


#endif //KAPPA_ENGINE_BUTTONCOMPONENT_HPP
