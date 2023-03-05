//
// Created by leo_b on 04/03/2023.
//

#pragma once

#include "KappaEngine/Interfaces/IInterface.hpp"

namespace Interface {
    class InputInterface: public IInterface {
        public:
            InputInterface(IPosition position, std::string placeholder);
            InputInterface() = delete;
            InputInterface(const InputInterface &) = delete;

            void OnRenderInterface(IPosition parent) override;

            std::string getText();


            IPosition _position;
            sf::Font _font;
            std::string _placeholder;
            sf::Text _inputText;
            std::string _text;


            bool _pressed = false;
            bool _isFocused = false;


    };
}
