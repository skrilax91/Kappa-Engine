//
// Created by leo_b on 03/02/2023.
//

#include "KappaEngine/Console/Console.hpp"
#include "KappaEngine/GameManager.hpp"
#include <iostream>

namespace Console {
    std::vector<Command *> Console::_commands = {};

    Console::Console() {
        registerCommand(new Command("help", "Display all commands", [this](CmdArguments args) {
            for (auto &command : _commands) {
                std::cout << command->getString() << " : " << command->getHelper() << std::endl;
            }
        }));

        if (KappaEngine::GameManager::GetServer() != nullptr) {
            _consoleThread = std::thread([this]() {
                while (KappaEngine::GameManager::GameStarted()) {
                    std::string command;
                    std::getline(std::cin, command);
                    executeCommand(command);
                }
            });
        }
    }

    Console::~Console() {
        _consoleThread.join();
    }

    Command *Console::getCommand(const std::string& command) {
        for (auto &cmd : _commands) {
            if (cmd->getString() == command) {
                return cmd;
            }
        }
        return nullptr;
    }

    void Console::registerServerCommand(Command *command) {
        if (getCommand(command->getString()) != nullptr)
            throw std::runtime_error("Command already exists");

        if (KappaEngine::GameManager::GetServer() != nullptr)
            _commands.push_back(command);
    }

    void Console::registerClientCommand(Command *command) {
        if (getCommand(command->getString()) != nullptr)
            throw std::runtime_error("Command already exists");

        if (KappaEngine::GameManager::GetClient() != nullptr)
            _commands.push_back(command);
    }

    void Console::registerCommand(Command *command) {
        if (getCommand(command->getString()) != nullptr)
            throw std::runtime_error("Command already exists");

        _commands.push_back(command);
    }

    void Console::executeCommand(std::string command) {

        std::string commandName = command.substr(0, command.find(' '));
        CmdArguments args = {};


        while (command.find(' ') != std::string::npos) {
            command = command.substr(command.find(' ') + 1);
            args.push_back(command.substr(0, command.find(' ')));
        }

        for (auto &cmd : _commands) {
            if (cmd->getString() == commandName) {
                cmd->getFunction()(args);
            }
        }
    }
}