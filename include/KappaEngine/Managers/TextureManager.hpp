//
// Created by leo_b on 02/03/2023.
//

#ifndef KAPPAENGINE_TEXTUREMANAGER_HPP
#define KAPPAENGINE_TEXTUREMANAGER_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace KappaEngine {
    class TextureManager {
        public:
            static std::shared_ptr<sf::Texture> GetTexture(const std::string& name, std::string path = "") {
                if (_textures.find(name) != _textures.end())
                    return _textures[name];
                if (path.empty())
                    throw std::runtime_error("Texture not found: " + name);

                auto texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile(path))
                    throw std::runtime_error("Failed to load texture: " + path);
                _textures[name] = texture;
            };

        private:
            static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
    };
}

#endif //KAPPAENGINE_TEXTUREMANAGER_HPP
