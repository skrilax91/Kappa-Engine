//
// Created by leo_b on 29/01/2023.
//

#ifndef KAPPA_ENGINE_GAMEMANAGER_HPP
#define KAPPA_ENGINE_GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>

namespace KappaEngine {

    /**
     * @brief The GameManager class is used to manage the entire game.
     */
    class GameManager {
        public:

            /**
             * @brief Create a window
             * @param name The name of the window
             * @param width The width of the window
             * @param height The height of the window
             */
            static void createWindow(const std::string& name, int width, int height);

            /**
             * @brief Set the framerate limit of the window
             * @param limit The framerate limit
             */
            static void setFramerateLimit(int limit);

            /**
             * @brief Set the fullscreen mode of the window
             * @param fullscreen The fullscreen mode
             */
            static void setFullscreen(bool fullscreen);


        private:
            static sf::Window _window;
            static std::string _name;
            static bool _fullscreen;


    };
}


#endif //KAPPA_ENGINE_GAMEMANAGER_HPP
