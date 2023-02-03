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
    class Command {
        public:
            Command(std::string string, std::function<void(CmdArguments)> function);
            Command(std::string string, std::string helper, std::function<void(CmdArguments)> function);

            virtual ~Command() = default;

            std::string getString() const;
            std::string getHelper() const;
            std::function<void(CmdArguments)> getFunction() const;

        private:
            std::string _string;
            std::string _helper;
            std::function<void(std::vector<std::string>)> _function;

    };
}


#endif //KAPPAENGINE_COMMAND_HPP
