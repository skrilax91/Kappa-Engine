//
// Created by leo_b on 04/03/2023.
//

#include "KappaEngine/Interfaces/ImageInterface.hpp"
#include "KappaEngine/Interfaces/Utils.hpp"
#include "KappaEngine/GameManager.hpp"

Interface::ImageInterface::ImageInterface(IPosition position, std::string path): _position(position) {
    if (!_texture.loadFromFile(path))
        std::cout << "Error while loading image " << path << std::endl;
    _sprite.setTexture(_texture);
}

void Interface::ImageInterface::OnRenderInterface(IPosition parent) {
    auto newPos = Interface::Utils::GetAbsolutePosition(parent, _position);
    _sprite.setPosition(newPos.x, newPos.y);

    _sprite.setScale(newPos.width / _sprite.getTextureRect().width, newPos.height / _sprite.getTextureRect().height);
    KappaEngine::GameManager::GetWindow()->draw(_sprite);
}