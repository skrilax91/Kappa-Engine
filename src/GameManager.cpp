//
// Created by leo_b on 29/01/2023.
//

#include <iostream>
#include <utility>
#include "KappaEngine/GameManager.hpp"
#include "KappaEngine/Managers/InterfaceManager.hpp"
#include "KappaEngine/Input.hpp"

namespace KappaEngine {

    sf::RenderWindow *GameManager::_window = nullptr;
    std::string GameManager::_name = "Kappa Engine Game";
    bool GameManager::_fullscreen = false;
    std::list<std::shared_ptr<Scene>> GameManager::_scenes = std::list<std::shared_ptr<Scene>>();
    std::shared_ptr<Scene> GameManager::_selectedScene = nullptr;

    Console::Console *GameManager::_console = nullptr;


    ///////////////////////////
    // WINDOW
    ///////////////////////////

    void GameManager::CreateGameWindow(const std::string &name, int width, int height) {
        _name = name;
        _window = new sf::RenderWindow();
        _window->create(sf::VideoMode(width, height), name);
        std::cout << "Window created" << std::endl;
    }

    void GameManager::setFramerateLimit(int limit) {
        if (!_window)
            return;
        _window->setFramerateLimit(limit);
    }

    void GameManager::setFullscreen(bool fullscreen) {
        if (fullscreen == _fullscreen || !_window)
            return;

        if (fullscreen)
            _window->create(sf::VideoMode::getFullscreenModes()[0], _name, sf::Style::Fullscreen);
        else
            _window->create(sf::VideoMode::getFullscreenModes()[0], _name);
    }

    sf::RenderWindow *GameManager::GetWindow() {
        return _window;
    }

    void GameManager::Draw(sf::Drawable& drawable) {
        if (!_window)
            return;

        _window->draw(drawable);
    }

    void GameManager::RenderWindow() {
        if (!_window)
            return;

        _window->display();
    }

    void GameManager::CloseWindow() {
        if (!_window)
            return;

        _window->close();
    }

    void GameManager::StartGame() {
        if (!_window && !_server)
            throw std::runtime_error("Cannot start a game if the window is not created");
        else if (_window && _server)
            throw std::runtime_error("A Server and a Window cannot be created at the same time");

        _started = true;

        _console = new Console::Console();

        if (_server)
            Input::InitNetworkKeys();

        for (auto scene : _scenes) {
            scene->Awake();
        }

        _selectedScene->Start();

        while (_started) {
            if (_server)
                _server->Update();
            else if (_window && !_window->isOpen())
                _started = false;

            if (_client && _client->IsConnected())
                _client->Update();

            _selectedScene->Update();

            if (_window) {
                _window->clear();
                _selectedScene->OnAnimator();
                _selectedScene->OnRenderObject();
                KappaEngine::InterfaceManager::OnRenderInterface();
                RenderWindow();
            }
        }
    }

    bool GameManager::GameStarted() {
        return _started;
    }

    bool GameManager::_started = false;

    ///////////////////////////
    // SCENE
    ///////////////////////////

    std::shared_ptr<Scene> GameManager::CreateScene(const std::string &name) {
        auto scene = std::make_shared<Scene>(name);
        if (!_selectedScene)
            _selectedScene = scene;
        _scenes.push_back(scene);
        return scene;
    }

    std::list<std::shared_ptr<Scene>> GameManager::GetScenes() {
        return _scenes;
    }

    std::shared_ptr<Scene> GameManager::GetScene(const std::string& name) {
        for (auto scene : _scenes) {
            if (scene->getName() == name)
                return scene;
        }
        return nullptr;
    }

    std::shared_ptr<Scene> GameManager::GetSelectedScene() {
        return _selectedScene;
    }

    void GameManager::SelectScene(const std::string &name) {
        for (auto scene : _scenes) {
            if (scene->getName() == name) {
                _selectedScene = scene;
                if (_started)
                    _selectedScene->Start();
                break;
            }
        }
    }

    ///////////////////////////
    // NETWORK
    ///////////////////////////

    Network::ServerInterface *GameManager::_server = nullptr;
    Network::ClientInterface *GameManager::_client = nullptr;


    bool GameManager::isNetworked() {
        return _server || _client;
    }

    void GameManager::StartServer() {
        if (!_server)
            throw std::runtime_error("Cannot start a server if it is not created");

        _server->Start();
    }

    Network::ServerInterface *GameManager::GetServer() {
        return _server;
    }

    Network::ClientInterface *GameManager::GetClient() {
        return _client;
    }

    void GameManager::RegisterServerMessageHandler(uint32_t id, std::function<void(std::shared_ptr<Network::Connection>, Network::Message&)> callback) {
        if (!_server)
            return;

        _server->AddOnMessageCallback(id, std::move(callback));
    }

    void GameManager::RegisterClientMessageHandler(uint32_t id, std::function<void(Network::Message&)> callback) {
        if (!_client)
            return;

        _client->RegisterMessageCallback(id, std::move(callback));
    }

}
