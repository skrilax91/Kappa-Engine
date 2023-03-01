//
// Created by Dylan A on 01/03/2023.
//

#include "ConfigurationManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

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
            return std::string();
        }
    }

    void ConfigurationManager::SetValue(const std::string& key, const auto& value) {
        m_configData[key] = value;
        SaveConfig();
    }

    void ConfigurationManager::SaveConfig() const {
        std::ofstream outputFile(m_configFilename);
        if (outputFile.is_open()) {
            for (const auto& it : m_configData) {
                outputFile << it.first << ":" << it.second << std::endl;
            }
        }
        else {
            std::cerr << "Failed to open file " << m_configFilename << " for writing." << std::endl;
        }
    }

    void ConfigurationManager::LoadConfig() {
        std::ifstream inputFile(m_configFilename);
        if (inputFile.is_open()) {
            std::string line;
            std::regex pattern("^(.*?):(.*)$");
            while (std::getline(inputFile, line)) {
                std::smatch match;
                if (std::regex_match(line, match, pattern)) {
                    m_configData[match[1]] = match[2];
                }
            }
        }
        else {
            std::cerr << "Failed to open file " << m_configFilename << " for reading." << std::endl;
        }
    }
}
