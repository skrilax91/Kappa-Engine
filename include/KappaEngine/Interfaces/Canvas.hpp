//
// Created by leo_b on 01/03/2023.
//

#ifndef KAPPAENGINE_CANVA_HPP
#define KAPPAENGINE_CANVA_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Utils.hpp"

namespace Interface {

    class Canvas: public IInterface {
        public:
            Canvas(IPosition pos): _rect(pos) {};
            ~Canvas() = default;

            void OnRenderInterface(IPosition parent) override {
                auto newPos = Interface::Utils::GetAbsolutePosition(parent, _rect);
                for (auto &interface : _interfaces) {
                    interface->OnRenderInterface(newPos);
                }
            };

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

            void AddInterface(std::shared_ptr<IInterface> interface) {
                _interfaces.push_back(interface);
            }

        private:
            std::vector<std::shared_ptr<IInterface>> _interfaces;
            IPosition _rect;

    };
}

#endif //KAPPAENGINE_CANVA_HPP
