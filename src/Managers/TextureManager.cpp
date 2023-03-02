//
// Created by leo_b on 02/03/2023.
//

#include "KappaEngine/Managers/TextureManager.hpp"

std::unordered_map<std::string, sf::Texture> KappaEngine::TextureManager::_textures = {};

sf::Texture KappaEngine::TextureManager::GetTexture(const std::string &name, std::string path) {
    if (_textures.find(name) != _textures.end())
        return _textures[name];
    if (path.empty())
        throw std::runtime_error("Texture not found: " + name);

    sf::Texture texture;
    if (!texture.loadFromFile(path))
        throw std::runtime_error("Failed to load texture: " + path);
    _textures[name] = texture;
    return texture;
}
