//
// Created by leo_b on 03/02/2023.
//

#ifndef KAPPAENGINE_COMMAND_HPP
#define KAPPAENGINE_COMMAND_HPP

#include <string>
#include <vector>
#include <functional>

#define CmdArguments std::vector<std::string>

namespace Console {

    /**
     * @brief Class that represents a command
     * @details This class is used to create a command that can be used in the console
     */
    class Command {
        public:
            Command(std::string string, std::function<void(CmdArguments)> function);
            Command(std::string string, std::string helper, std::function<void(CmdArguments)> function);

            virtual ~Command() = default;

            /**
             * @brief Get the string of the command
             * @return The string of the command
             */
            std::string getString() const;

            /**
             * @brief Get the helper of the command
             * @return The helper of the command
             */
            std::string getHelper() const;

            /**
             * @brief Get the function of the command
             * @return The function of the command
             */
            std::function<void(CmdArguments)> getFunction() const;

        private:
            std::string _string;
            std::string _helper;
            std::function<void(std::vector<std::string>)> _function;

    };
}


#endif //KAPPAENGINE_COMMAND_HPP
