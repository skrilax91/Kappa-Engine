//
// Created by leo_b on 01/02/2023.
//

#ifndef KAPPA_ENGINE_IINTERFACE_HPP
#define KAPPA_ENGINE_IINTERFACE_HPP

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


    class IInterface {
        public:
            virtual ~IInterface() = default;
            bool enabled = true;
            bool onFocus = false;

            virtual void OnRenderObject() {};

            virtual void OnClick() { if (_onClick) { _onClick(); }};
            virtual void OnRelease() { if (_onRelease) { _onRelease(); }};
            virtual void OnHover() { if (_onHover) { _onHover(); }};
            virtual void OnUnhover() { if (_onUnhover) { _onUnhover(); }};

        protected:
            std::function<void()> _onClick;
            std::function<void()> _onRelease;

            std::function<void()> _onHover;
            std::function<void()> _onUnhover;
    };
}



#endif //KAPPA_ENGINE_IINTERFACE_HPP
