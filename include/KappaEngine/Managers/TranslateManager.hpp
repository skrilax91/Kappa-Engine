//
// Created by leo_b on 05/03/2023.
//

#pragma once
#include <yaml-cpp/yaml.h>

namespace KappaEngine {
    class TranslateManager {
        public:
            static void loadTranslates();

            static void registerTranslate(std::string *translate, std::string key);
        private:
            static void updateTranslates();

            static YAML::Node _configs;
            static std::map<std::string, YAML::Node> _translateData;
            static std::vector<std::pair<std::string *, std::string>> _translatePointers;
            static std::string _defaultTranslate;
            static std::string _currentTranslate;
    };

}
