#include <string>
#include "IComponent.hpp"
#include "SpriteRenderer.hpp"
#include <list>

namespace Component {

    class Animation {
        public:
            Animation(std::string id, std::string texturePath, Component::SpriteRenderer & spriteRenderer, std::list<sf::IntRect> textureRect, int frameCount, float frameDuration, bool loop):
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect),
                _spriteRenderer(spriteRenderer),
                _frameCount(frameCount),
                _frameDuration(frameDuration),
                _loop(loop),
                _id(id) {};

            std::string _texturePath;
            Component::SpriteRenderer & _spriteRenderer;
            std::list<sf::IntRect> _textureRect;
            std::string _id;
            int _frameCount;
            float _frameDuration;
            bool _loop;
    };
    class Animator : public IComponent {
        public:
            Animator(std::list<Animation> animations, std::string idleAnimation):
                _animations(animations),
                _idleAnimation(std::move(idleAnimation)) {};
            std::list<Animation> _animations;
            std::string _idleAnimation;
    };
}