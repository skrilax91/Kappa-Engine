//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_BUTTONINTERFACE_HPP
#define KAPPA_ENGINE_BUTTONINTERFACE_HPP

#include <array>
#include <functional>
#include <SFML/Graphics.hpp>

#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Interfaces/Utils.hpp"
#include "KappaEngine/Input.hpp"

namespace Interface {
    class ButtonInterface: public IInterface {
        public:
            ButtonInterface(IPosition position, std::string path, std::array<sf::IntRect, 3> rects);
            ButtonInterface() = delete;
            ButtonInterface(const ButtonInterface &) = delete;

            void OnRenderInterface(IPosition parent) override;

            void setOnClick(std::function<void()> onClick);
            void setOnRelease(std::function<void()> onRelease);
            void setOnHover(std::function<void()> onHover);
            void setOnUnhover(std::function<void()> onUnhover);

            std::array<sf::IntRect, 3> _rects;
            IPosition _rect;

            sf::Sprite _sprite;
            sf::Texture _texture;
            sf::Font _font;
            sf::Text _text;
    };
}


#endif //KAPPA_ENGINE_BUTTONINTERFACE_HPP
