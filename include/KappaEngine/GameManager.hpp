//
// Created by leo_b on 29/01/2023.
//

#ifndef KAPPA_ENGINE_GAMEMANAGER_HPP
#define KAPPA_ENGINE_GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>

#include "Scene.hpp"
#include "Console/Console.hpp"
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

            /**
             * @brief Draw a drawable
             * @param drawable
             */
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
             * @brief Start the game
             *
             * @details This function will start the game logic
             * @details It will call the Awake() function of all systems and call the Start() function of active scene systems
             * @details It will then run the game loop
             */
            static void StartGame();

            /**
             * @brief Check if the game is started
             * @return True if the game is started
             */
            static bool GameStarted();


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

            /**
             * @brief Get the selected scene
             * @return The selected scene
             */
            static Scene* GetSelectedScene();

            /**
             * @brief Select the scene
             * @param name The name of the scene
             */
            static void SelectScene(const std::string& name);


            /**
             * @brief Check if the game is networked
             * @return True if the game is networked, false otherwise
             */
            static bool isNetworked();

            /**
             * @brief Make the game a server
             * @attention This function will throw an exception if a client or a server is already running
             *
             * @param port The port of the server
             * @throw std::runtime_error
             */
            static void makeServer(int port) {

                if (isNetworked())
                    throw std::runtime_error("Cannot make a server if a client is already running");

                _server = new Network::ServerInterface(port);
            }

            /**
             * @brief Make the game a client
             * @attention This function will throw an exception if a client or a server is already running
             *
             * @throw std::runtime_error
             */
            static void makeClient() {

                if (isNetworked())
                    throw std::runtime_error("Cannot make a client if a server is already running");

                _client = new Network::ClientInterface();
            }

            /**
             * @brief Get the server
             * @return The server if the game is a server, nullptr otherwise
             */
            static Network::ServerInterface *GetServer();

            /**
             * @brief Get the client
             * @return The client if the game is a client, nullptr otherwise
             */
            static Network::ClientInterface *GetClient();

            /**
             * @brief Start the server
             * @attention This function will throw an exception if the game is not a server
             *
             * @throw std::runtime_error
             */
            static void StartServer();


            /**
             * @brief Register new server message handler
             *
             * @param id The id of the message
             * @param callback The callback function
             */
            static void RegisterServerMessageHandler(uint32_t id, std::function<void(std::shared_ptr<Network::Connection>, Network::Message&)> callback);

            /**
             * @brief Register new client message handler
             *
             * @param id The id of the message
             * @param callback The callback function
             */
            static void RegisterClientMessageHandler(uint32_t id, std::function<void(Network::Message&)> callback);


        private:
            static Console::Console *_console;


            static sf::RenderWindow *_window;
            static std::string _name;
            static bool _started;
            static bool _fullscreen;

            static std::vector<Scene *> _scenes;
            static Scene *_selectedScene;

            static Network::ServerInterface *_server;
            static Network::ClientInterface *_client;
    };
}


#endif //KAPPA_ENGINE_GAMEMANAGER_HPP
