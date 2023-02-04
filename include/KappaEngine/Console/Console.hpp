//
// Created by leo_b on 03/02/2023.
//

#ifndef KAPPAENGINE_CONSOLE_HPP
#define KAPPAENGINE_CONSOLE_HPP

#include <thread>

#include "KappaEngine/Console/Command.hpp"

namespace Console {

    /**
     * @brief Class that represents the console
     * @details This class is used to create a console that can be used to execute commands
     */
    class Console {
        public:
            Console();
            virtual ~Console();

            /**
             * @brief Register a command to the server console
             * @details This function is used to register a command to the server console
             * @attention The command will be only available in the server console
             *
             * @param command The command to register
             */
            static void registerServerCommand(Command *command);

            /**
             * @brief Register a command to the client console
             * @details This function is used to register a command to the client console
             * @attention The command will be only available in the client console
             *
             * @param command The command to register
             */
            static void registerClientCommand(Command *command);

            /**
             * @brief Register a command to the console
             * @details This function is used to register a command to the console
             * @attention The command will be available in the client and server console
             *
             * @param command The command to register
             */
            static void registerCommand(Command *command);

            /**
             * @brief Get a command from the console
             * @details This function is used to get a command from the console
             *
             * @param command The string of the command
             * @return The command
             */
            static Command *getCommand(const std::string &command);

            /**
             * @brief Execute a command
             * @details This function is used to execute a command
             *
             * @param command The string of the command
             */
            static void executeCommand(std::string command);

        private:
            static std::vector<Command *> _commands;
            std::thread _consoleThread;
    };
}


#endif //KAPPAENGINE_CONSOLE_HPP
