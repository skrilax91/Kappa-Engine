#ifndef KAPPAENGINE_SOUNDMANAGER_HPP
#define KAPPAENGINE_SOUNDMANAGER_HPP

#include <unordered_map>
#include <SFML/Audio.hpp>

namespace KappaEngine {
    class SoundManager {
        public:
            static sf::Music GetSound(const std::string& name, std::string path = "");

        private:
            static std::unordered_map<std::string, sf::Music> _sounds;
    };
}

#endif //KAPPAENGINE_SOUNDMANAGER_HPP
