//
// Created by leo_b on 03/02/2023.
//

#include "KappaEngine/Console/Command.hpp"

namespace Console {

    Command::Command(std::string string, std::function<void(CmdArguments)> function, CmdArguments args) : _string(std::move(string)), _function(std::move(function)), _args(std::move(args)) {}
    Command::Command(std::string string, std::string helper, std::function<void(CmdArguments)> function, CmdArguments args) : _string(std::move(string)), _helper(std::move(helper)), _function(std::move(function)), _args(std::move(args)) {}

    std::string Command::getString() const {
        return _string;
    }

    std::string Command::getHelper() const {
        return _helper;
    }

    std::function<void(CmdArguments)> Command::getFunction() const {
        return _function;
    }

    CmdArguments Command::getArgs() const {
        return _args;
    }
}