//
// Created by Dylan A on 01/03/2023.
//

#ifndef KAPPAENGINE_CONFIGURATIONMANAGER_HPP
#define KAPPAENGINE_CONFIGURATIONMANAGER_HPP

#include <string>
#include <unordered_map>

namespace KappaEngine {
    class ConfigManager {
    public:
        ConfigManager(const std::string& configFilename);
        ~ConfigManager() = default;

        auto GetValue(const std::string& key) const;

        void SetValue(const std::string& key, const auto& value);

        void SaveConfig() const;

    private:
        std::string m_configFilename;
        std::unordered_map<std::string, std::string> m_configData;

        void LoadConfig();
    };
}


#endif //KAPPAENGINETESTS_CONFIGURATIONMANAGER_HPP
