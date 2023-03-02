//
// Created by Dylan A on 01/03/2023.
//

#include "KappaEngine/ConfigurationManager.hpp"
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace KappaEngine {
    ConfigurationManager::ConfigurationManager(const std::string& configFilename)
        : m_configFilename(configFilename) {
        LoadConfig();
    }

    auto ConfigurationManager::GetValue(const std::string& key) const {
        auto it = m_configData.find(key);
        if (it != m_configData.end()) {
            return it->second;
        }
        else {
            return std::string(); // Return an empty string if key not found
        }
    }

    void ConfigurationManager::SetValue(const std::string& key, const auto& value) {
        m_configData[key] = value;
    }

    void ConfigurationManager::SaveConfig() const {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        for (const auto& it : m_configData) {
            emitter << YAML::Key << it.first << YAML::Value << it.second;
        }
        emitter << YAML::EndMap;

        std::ofstream outputFile(m_configFilename);
        if (outputFile.is_open()) {
            outputFile << emitter.c_str();
        }
        else {
            std::cerr << "Failed to open file " << m_configFilename << " for writing." << std::endl;
        }
    }

    void ConfigurationManager::LoadConfig() {
        std::ifstream inputFile(m_configFilename);
        if (inputFile.is_open()) {
            m_configData = YAML::Load(inputFile).as<std::unordered_map<std::string, std::string>>();
        }
        else {
            std::cerr << "Failed to open file " << m_configFilename << " for reading." << std::endl;
        }
    }
}
