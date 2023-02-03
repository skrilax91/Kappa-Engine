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
            Command(std::string string, std::function<void(CmdArguments)> function, CmdArguments args = {});
            Command(std::string string, std::string helper, std::function<void(CmdArguments)> function, CmdArguments args = {});

            virtual ~Command() = default;

            std::string getString() const;
            std::string getHelper() const;
            std::function<void(CmdArguments)> getFunction() const;
            CmdArguments getArgs() const;

        private:
            std::string _string;
            std::string _helper;
            std::function<void(std::vector<std::string>)> _function;
            CmdArguments _args;

    };
}


#endif //KAPPAENGINE_COMMAND_HPP
