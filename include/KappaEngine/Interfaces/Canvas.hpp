//
// Created by leo_b on 01/03/2023.
//

#ifndef KAPPAENGINE_CANVA_HPP
#define KAPPAENGINE_CANVA_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Utils.hpp"
#include "KappaEngine/GameManager.hpp"

namespace Interface {

    class Canvas: public IInterface {
        public:
            Canvas(IPosition pos): _rect(pos) { _type = InterfaceType::CANVAS; };
            ~Canvas() = default;

            void OnRenderInterface(IPosition parent) override;

            void OnClick() override {
                for (auto interface : _interfaces) {
                    interface->OnClick();
                }
            };

            void OnRelease() override {
                for (auto interface : _interfaces) {
                    interface->OnRelease();
                }
            };

            void OnHover() override {
                for (auto interface : _interfaces) {
                    interface->OnHover();
                }
            };

            void OnUnhover() override {
                for (auto interface : _interfaces) {
                    interface->OnUnhover();
                }
            };

            void SetPosition(IPosition pos);
            void AddInterface(std::shared_ptr<IInterface> interface);
            std::vector<std::shared_ptr<IInterface>> GetInterfaces() { return _interfaces; };
            void SetColor(sf::Color color);

        private:
            std::vector<std::shared_ptr<IInterface>> _interfaces;
            IPosition _rect;
            sf::Color _color = sf::Color::Transparent;
    };
}

#endif //KAPPAENGINE_CANVA_HPP
