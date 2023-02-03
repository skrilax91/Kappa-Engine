//
// Created by leo_b on 03/02/2023.
//

#ifndef KAPPAENGINE_CONSOLE_HPP
#define KAPPAENGINE_CONSOLE_HPP

#include <thread>

#include "KappaEngine/Console/Command.hpp"

namespace Console {
    class Console {
        public:
            Console();
            virtual ~Console();

            static void registerServerCommand(Command *command);
            static void registerClientCommand(Command *command);
            static void registerCommand(Command *command);

            static Command *getCommand(const std::string &command);

            static void executeCommand(std::string command);

        private:
            static std::vector<Command *> _commands;
            std::thread _consoleThread;
    };
}


#endif //KAPPAENGINE_CONSOLE_HPP
