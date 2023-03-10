#pragma once

#include <string>
#include "IComponent.hpp"
#include "SpriteRenderer.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <unordered_map>

namespace Component {

    class Animation {
        public:
            Animation(std::string id, std::string texturePath, std::shared_ptr<Component::SpriteRenderer> spriteRenderer, std::vector<sf::IntRect> textureRect, float duration, bool loop):
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect),
                _spriteRenderer(spriteRenderer),
                _duration(duration),
                _loop(loop),
                _id(id) {};

            std::string _texturePath;
            sf::Texture _texture;
            std::shared_ptr<Component::SpriteRenderer> _spriteRenderer;
            std::vector<sf::IntRect> _textureRect;
            std::string _id;
            int _actualFrame = 0;
            float _duration;
            bool _loop;
            sf::Clock _clock;
    };
    class Animator : public IComponent {
        public:
            Animator(std::unordered_map<std::string, Animation *> animations, std::string idleAnimation):
                _animations(animations),
                _actualAnimation(idleAnimation),
                _idleAnimation(idleAnimation) {};
            std::unordered_map<std::string, Animation *> _animations;
            std::string _idleAnimation;
            std::string _actualAnimation;
    };
}