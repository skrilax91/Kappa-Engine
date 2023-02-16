#include <string>
#include "IComponent.hpp"

namespace Component {

    /**
     * @brief The Animation class
     * @def This class is used to create an animation
     * @def The texturePath is the path to the texture
     * @def The textureRect is the rectangle of the texture to use
     * @def The layer is the layer to render the sprite
     * @def The frameCount is the number of frames in the animation
     * @def The frameDuration is the duration of each frame
     * @def The loop is a boolean to know if the animation should loop
     */
    class Animation : public IComponent {
        public:
            Animation(std::string texturePath, sf::IntRect textureRect, std::string layer, int frameCount, float frameDuration, bool loop):
                _texturePath(std::move(texturePath)),
                _textureRect(textureRect),
                _layer(std::move(layer)),
                _frameCount(frameCount),
                _frameDuration(frameDuration),
                _loop(loop) {};

            std::string _texturePath;
            sf::IntRect _textureRect;
            std::string _layer;
            int _frameCount;
            float _frameDuration;
            bool _loop;
    };
}