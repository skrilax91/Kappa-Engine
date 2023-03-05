//
// Created by leo_b on 05/03/2023.
//

#include <filesystem>
#include <iostream>
#include "KappaEngine/Managers/TranslateManager.hpp"

namespace KappaEngine {

    YAML::Node TranslateManager::_configs;
    std::map<std::string, YAML::Node> TranslateManager::_translateData;
    std::vector<std::pair<std::string *, std::string>> TranslateManager::_translatePointers;
    std::vector<std::pair<sf::Text *, std::string>> TranslateManager::_translateTextPointers;
    std::string TranslateManager::_defaultTranslate;
    std::string TranslateManager::_currentTranslate;
    std::vector<std::string> TranslateManager::_availableTranslates;

    void TranslateManager::loadTranslates() {
        _translateData.clear();

        if (!std::filesystem::exists("configs/translation.yaml"))
            throw std::runtime_error("Can't load translate base configs\n"
                                     "File configs/translation.yaml doesn't exist. "
                                     "Please create it or check if it's in the right place");

        _configs = YAML::LoadFile("configs/translation.yaml");

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

                if (!std::filesystem::exists(path)) {
                    std::cerr << "Can't load translate file: " << path << "\n Locale " << entry["code"].as<std::string>() << " will be ignored" << std::endl;
                    continue;
                }

                YAML::Node translate = YAML::LoadFile(path);
                _translateData[entry["code"].as<std::string>()] = translate;
                _availableTranslates.push_back(entry["code"].as<std::string>());

                std::cout << "Loaded locale " << entry["code"].as<std::string>() << " from " << path << std::endl;
            }
        }
        updateTranslates();
    }

    std::string TranslateManager::getTranslate(const std::string& key) {
        YAML::Node node;

        if (_translateData.find(_currentTranslate) != _translateData.end())
            node = Clone(_translateData[_currentTranslate]);
        else if (_translateData.find(_defaultTranslate) != _translateData.end())
            node = Clone(_translateData[_defaultTranslate]);
        else {
            std::cerr << "Can't find any translate file for locale " << _currentTranslate << " or " << _defaultTranslate << std::endl;
            return key;
        }

        size_t pos = 0;
        std::string token;
        std::string cpkey = key;
        while ((pos = cpkey.find('.')) != std::string::npos) {
            token = cpkey.substr(0, pos);

            if (!(node)[token])
                return key;
            node = node[token];
            cpkey.erase(0, pos + 1);
        }

        return (node[cpkey] && node[cpkey].IsScalar()) ? node[cpkey].as<std::string>() : key;
    }

    void TranslateManager::setTranslate(const std::string& translate) {

        if (_translateData.find(translate) == _translateData.end())
            return;

        _currentTranslate = translate;
        updateTranslates();
    }

    std::string TranslateManager::getCurrentTranslate() {
        return _currentTranslate;
    }

    std::string TranslateManager::getDefaultTranslate() {
        return _defaultTranslate;
    }

    std::vector<std::string> TranslateManager::getAvailableTranslates() {
        return _availableTranslates;
    }

    void TranslateManager::registerTranslate(std::string *str, const std::string& key) {
        _translatePointers.emplace_back(str, key);
        translate(str, key);
    }

    void TranslateManager::registerTranslate(sf::Text *text, const std::string& key) {
        _translateTextPointers.emplace_back(text, key);
        translate(text, key);
    }

    void TranslateManager::updateTranslates() {
        for (auto &entry : _translatePointers) {
            translate(entry.first, entry.second);
        }

        for (auto &entry : _translateTextPointers) {
            translate(entry.first, entry.second);
        }
    }

    void TranslateManager::translate(std::string *str, const std::string& key) {
        str->assign(getTranslate(key));
    }

    void TranslateManager::translate(sf::Text *text, const std::string& key) {
        text->setString(getTranslate(key));
    }
}