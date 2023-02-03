//
// Created by leo_b on 03/02/2023.
//

#include "KappaEngine/Console/Command.hpp"

namespace Console {

    Command::Command(std::string string, std::function<void(CmdArguments)> function) : _string(std::move(string)), _function(std::move(function)) {}
    Command::Command(std::string string, std::string helper, std::function<void(CmdArguments)> function) : _string(std::move(string)), _helper(std::move(helper)), _function(std::move(function)) {}

    std::string Command::getString() const {
        return _string;
    }

    std::string Command::getHelper() const {
        return _helper;
    }

    std::function<void(CmdArguments)> Command::getFunction() const {
        return _function;
    }
}