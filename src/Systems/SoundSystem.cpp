#include "KappaEngine/Systems/AnimationSystem.hpp"
#include "KappaEngine/Components/Animator.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
#include "KappaEngine/Systems/SpriteRendererSystem.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {

    void SoundSystem::Awake(std::shared_ptr<Entity> entity) {
        auto sound = entity->getComponent<Component::Sound>();
        if (sound == nullptr) {
            return;
        }

        if (!sound->enabled)
            return;

        if (sound->_soundBuffer.loadFromFile(sound->_soundPath)) {
            sound->_sound.setBuffer(sound->_soundBuffer);
        } else {
            std::cout << "Error while loading sound " << sound->_soundPath << std::endl;
        }
    }

    void SoundSystem::OnSound() {
        auto entities = _scene->getEntityManager()->getEntitiesWithComponent<Component::Sound>();
        for (auto entity : entities) {
            auto sound = entity->getComponent<Component::Sound>();
            if (sound == nullptr) {
                return;
            }

            if (!sound->enabled)
                return;

            if (sound->_sound.getStatus() == sf::Sound::Status::Stopped) {
                sound->_sound.play();
            }
        }
    }
}