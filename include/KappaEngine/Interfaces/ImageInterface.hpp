//
// Created by leo_b on 04/03/2023.
//

#pragma once

#include <KappaEngine/Interfaces/IInterface.hpp>
#include <iostream>

namespace Interface {
    class ImageInterface: public IInterface {
        public:
            ImageInterface(IPosition position, std::string path);
            ImageInterface() = delete;
            ImageInterface(const ImageInterface &) = delete;

            void OnRenderInterface(IPosition parent) override;

            IPosition _position;
            sf::Sprite _sprite;
            sf::Texture _texture;
    };
}
