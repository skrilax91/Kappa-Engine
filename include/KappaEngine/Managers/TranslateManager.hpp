//
// Created by leo_b on 05/03/2023.
//

#pragma once
#include <yaml-cpp/yaml.h>
#include <SFML/Graphics/Text.hpp>

namespace KappaEngine {
    class TranslateManager {
        public:
            static void loadTranslates();

            static void registerTranslate(std::string *translate, const std::string& key);
            static void registerTranslate(sf::Text *translate, const std::string& key);

            static void translate(std::string *translate, const std::string& key);
            static void translate(sf::Text *translate, const std::string& key);

            static void setTranslate(const std::string& translate);

            static std::string getCurrentTranslate();
            static std::string getDefaultTranslate();

            static std::vector<std::string> getAvailableTranslates();

            static std::string getTranslate(const std::string& key);
        private:
            static void updateTranslates();

            static YAML::Node _configs;
            static std::map<std::string, YAML::Node> _translateData;
            static std::vector<std::pair<std::string *, std::string>> _translatePointers;
            static std::vector<std::pair<sf::Text *, std::string>> _translateTextPointers;
            static std::string _defaultTranslate;
            static std::string _currentTranslate;
            static std::vector<std::string> _availableTranslates;
    };

}
