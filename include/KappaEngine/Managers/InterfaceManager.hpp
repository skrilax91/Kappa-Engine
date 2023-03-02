//
// Created by leo_b on 01/03/2023.
//

#ifndef KAPPAENGINE_INTERFACEMANAGER_HPP
#define KAPPAENGINE_INTERFACEMANAGER_HPP

#include <unordered_map>
#include "KappaEngine/Interfaces/Canvas.hpp"

namespace KappaEngine {
    class InterfaceManager {
        public:
            static void AddCanvas(const std::string& name, std::shared_ptr<Interface::Canvas> canvas);
            static void SetCurrentCanvas(const std::string& name);
            static std::shared_ptr<Interface::Canvas> GetCurrentCanvas();
            static std::shared_ptr<Interface::Canvas> GetCanvas(const std::string& name);

            static void OnRenderInterface();

        private:
            static std::unordered_map<std::string, std::shared_ptr<Interface::Canvas>> _canvases;
            static std::shared_ptr<Interface::Canvas> _currentCanvas;
    };
}

#endif //KAPPAENGINE_INTERFACEMANAGER_HPP
