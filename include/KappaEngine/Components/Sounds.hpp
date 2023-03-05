#pragma once

#include <string>
#include "IComponent.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace Component {

    class Sound {
        public:
            Sound(std::string id, std::string soundPath, float duration, bool loop):
                _soundPath(soundPath),
                _duration(duration),
                _loop(loop),
                _id(id) {};

            std::string _soundPath;
            sf::Sound _sound;
            std::string _id;
            float _duration;
            bool _loop;
            sf::Clock _clock;
    };
    class Sounds : public IComponent {
        public:
            Sounds(std::unordered_map<std::string, Sound *> sounds):
                _sounds(sounds) {};
            std::unordered_map<std::string, Sound *> _sounds;
    };
}