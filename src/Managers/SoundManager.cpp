#include "KappaEngine/Managers/SoundManager.hpp"

std::unordered_map<std::string, sf::Music> KappaEngine::SoundManager::_sounds = {};

sf::Music KappaEngine::SoundManager::GetSound(const std::string &name, std::string path) {
    if (_sounds.find(name) != _sounds.end())
        return _sounds[name];
    if (path.empty())
        throw std::runtime_error("Sound not found: " + name);

    sf::Music sound;
    if (!sound.loadFromFile(path))
        throw std::runtime_error("Failed to load sound: " + path);
    _sounds[name] = sound;
    return sound;
}
