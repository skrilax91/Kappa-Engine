/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-dylan.akpinar
** File description:
** ParalaxSystem
*/

#pragma once

#include "KappaEngine/Systems/ISystem.hpp"
#include "KappaEngine/Components/SpriteRenderer.hpp"
namespace KappaEngine {
    class ParallaxSystem : public ISystem {
        public:
            ParallaxSystem(Scene *scene) : ISystem(scene) {};

            void FixedUpdate() override;
    };
}