//
// Created by leo_b on 29/01/2023.
//

#ifndef KAPPA_ENGINE_GAMEMANAGER_HPP
#define KAPPA_ENGINE_GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "Scene.hpp"
#include "KappaEngine/Network/ServerInterface.hpp"
#include "KappaEngine/Network/ClientInterface.hpp"

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
            static void CreateGameWindow(const std::string& name, int width, int height);

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

            /**
             * @brief Get the window
             * @return The window
             */
            static sf::RenderWindow *GetWindow();

            static void Draw(sf::Drawable& drawable);

            /**
             * @brief Render the window
             */
            static void RenderWindow();


            /**
             * @brief Close the window
             */
            static void CloseWindow();


            /**
             * @brief Create a scene
             * @param name The name of the scene
             * @return The scene
             */
            static Scene *CreateScene(const std::string& name);

            /**
             * @brief Get the scene
             * @param name The name of the scene
             * @return The scene
             */
            static Scene* GetScene(const std::string& name);


            Template<class T>
            static void makeServer(int port) {
                static_assert(std::is_base_of<ServerInterface, T>::value, "T must inherit from ServerInterface");

                if (isNetworked())
                    throw std::runtime_error("A networked game is already running"

                _server = new T(port);
            }

            Template<class T>
            static void makeClient() {
                static_assert(std::is_base_of<ClientInterface, T>::value, "T must inherit from ClientInterface");

                if (isNetworked())
                    throw std::runtime_error("A networked game is already running"


                _client = new T();
            }

            static bool isNetworked() {
                return getClient() || getServer();
            }

            static ServerInterface* getServer() {
                return _server;
            }

            static ClientInterface* getClient() {
                return _client;
            }

        private:
            static sf::RenderWindow *_window;
            static std::string _name;
            static bool _fullscreen;

            static std::vector<Scene *> _scenes;

            static ServerInterface *_server;
            static ClientInterface *_client;


    };
}


#endif //KAPPA_ENGINE_GAMEMANAGER_HPP
