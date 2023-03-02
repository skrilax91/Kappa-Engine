//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_IINTERFACE_HPP
#define KAPPA_ENGINE_IINTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <functional>

namespace Interface {

    enum Anchor {
        TOP_LEFT,
        TOP_RIGHT,
        TOP_CENTER,

        CENTER_LEFT,
        CENTER_RIGHT,
        CENTER_CENTER,

        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        BOTTOM_CENTER,
    };

    struct IPosition {
        int x = 0;
        int y = 0;
        unsigned int width = 0;
        unsigned int height = 0;
        Anchor anchor = TOP_LEFT;
    };


    class IInterface {
        public:
            virtual ~IInterface() = default;
            bool enabled = true;
            bool onFocus = false;

            virtual void OnRenderInterface(IPosition pos) {};

            virtual void OnClick() { if (_onClick) { _onClick(); }};
            virtual void OnRelease() { if (_onRelease) { _onRelease(); }};
            virtual void OnHover() { if (_onHover) { _onHover(); }};
            virtual void OnUnhover() { if (_onUnhover) { _onUnhover(); }};

        protected:
            std::function<void()> _onClick;
            bool _isClicked = false;

            std::function<void()> _onRelease;
            bool _isReleased = true;

            std::function<void()> _onHover;
            bool _isHovered = false;

            std::function<void()> _onUnhover;
            bool _isUnhovered = true;
    };
}



#endif //KAPPA_ENGINE_IINTERFACE_HPP
