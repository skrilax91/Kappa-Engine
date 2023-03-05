#include "KappaEngine/Systems/SoundSystem.hpp"
#include "KappaEngine/GameManager.hpp"

namespace KappaEngine {
    void SoundSystem::Awake(std::shared_ptr<Entity> entity) {
        auto sound = entity->GetComponent<Sound>();
        if (sound) {
            sound->sound = SoundManager::GetSound(sound->name, sound->path);
            sound->sound.setLoop(sound->loop);
            sound->sound.setVolume(sound->volume);
            sound->sound.setPitch(sound->pitch);
            sound->sound.setRelativeToListener(sound->relativeToListener);
            sound->sound.setPosition(sound->position.x, sound->position.y, sound->position.z);
            sound->sound.setMinDistance(sound->minDistance);
            sound->sound.setAttenuation(sound->attenuation);
            sound->sound.setPlayingOffset(sound->playingOffset);
        }
    }

    void SoundSystem::OnSound() {
        for (auto &entity : _scene->GetEntities()) {
            auto sound = entity->GetComponent<Sound>();
            if (sound) {
                if (sound->play) {
                    sound->sound.play();
                    sound->play = false;
                }
                if (sound->pause) {
                    sound->sound.pause();
                    sound->pause = false;
                }
                if (sound->stop) {
                    sound->sound.stop();
                    sound->stop = false;
                }
            }
        }
    }
}