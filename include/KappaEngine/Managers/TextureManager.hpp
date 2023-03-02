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
            static sf::Texture GetTexture(const std::string& name, std::string path = "");

        private:
            static std::unordered_map<std::string, sf::Texture> _textures;
    };
}

#endif //KAPPAENGINE_TEXTUREMANAGER_HPP
