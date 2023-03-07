//
// Created by Dylan A on 01/03/2023.
//

#pragma once

#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>

namespace KappaEngine {
    class ConfigManager {
        public:
            static void loadConfigs();

            static YAML::Node getConfig(const std::string &configName);

        private:
            static std::map<std::string, YAML::Node> _configData;

    };
}
