//
// Created by leo_b on 05/03/2023.
//

#include "KappaEngine/Managers/TranslateManager.hpp"

namespace KappaEngine {
    void TranslateManager::loadTranslates() {
        _translateData.clear();

        _configs = YAML::LoadFile("configs/translation.yaml");

        if (!_configs)
            throw std::runtime_error("Can't load translate base configs");

        std::string basePath = (_configs["folder"]) ? _configs["folder"].as<std::string>() : "translations";

        _defaultTranslate = (_configs["default"]) ? _configs["default"].as<std::string>() : "en";
        _currentTranslate = _defaultTranslate;

        if (_configs["locales"]) {
            for (const auto &entry : _configs["locales"]) {
                if (!entry["file"] || !entry["code"])
                    continue;

                if (_translateData.find(entry["code"].as<std::string>()) != _translateData.end())
                    continue;

                std::string path = basePath + "/" + entry["file"].as<std::string>();
                YAML::Node translate = YAML::LoadFile(path);

                if (!translate)
                    throw std::runtime_error("Can't load translate file: " + path);

                _translateData[entry["code"].as<std::string>()] = translate;
            }
        }

        updateTranslates();
    }

    void TranslateManager::registerTranslate(std::string *translate, std::string key) {
        _translatePointers.push_back(std::make_pair(translate, key));



    }

    void TranslateManager::updateTranslates() {
        for (auto &entry : _translatePointers) {
            if (_translateData.find(_configs["default"].as<std::string>()) == _translateData.end())
                throw std::runtime_error("Can't find default translate");

            if (_translateData[_configs["default"].as<std::string>()][entry.second])
                *entry.first = _translateData[_configs["default"].as<std::string>()][entry.second].as<std::string>();
        }
    }
}