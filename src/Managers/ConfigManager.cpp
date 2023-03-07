//
// Created by Dylan A on 01/03/2023.
//

#include <filesystem>
#include "KappaEngine/Managers/ConfigManager.hpp"


namespace KappaEngine {

    std::map<std::string, YAML::Node> ConfigManager::_configData;

    void ConfigManager::loadConfigs() {
        _configData.clear();

        YAML::Node kappaConf = YAML::LoadFile("configs/kappa.yaml");

        if (!kappaConf)
            throw std::runtime_error("Can't load kappa base configs");

        _configData["kappa"] = kappaConf;

        for (const auto &entry : std::filesystem::directory_iterator("configs/packages")) {
            std::string path = entry.path().string();
            YAML::Node config = YAML::LoadFile(path);

            if (!config)
                throw std::runtime_error("Can't load config file: " + path);

            if (!config["configName"])
                throw std::runtime_error("Can't load config file: " + path + " because it doesn't have a configName");

            if (_configData.find(config["configName"].as<std::string>()) != _configData.end())
                throw std::runtime_error("Can't load config file: " + path + " because the configName is already used");

            _configData[config["configName"].as<std::string>()] = config;
        }
    }

    YAML::Node ConfigManager::getConfig(const std::string &configName) {
        if (_configData.find(configName) == _configData.end())
            throw std::runtime_error("Can't find config: " + configName);

        return _configData[configName];
    }
}
