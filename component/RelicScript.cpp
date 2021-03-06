//
// Created by iagoc on 30/12/2020.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "RelicScript.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <SFML/Audio.hpp>

// some global sound buffers and sounds for sfx
sf::SoundBuffer relicGetBuffer;
sf::Sound relicGetSound;


RelicScript::RelicScript(GameObject * relic, GameObject * player, glm::vec3 destination) {
    this->relic = relic;
    this->player = player;
    this->destination = destination;
    this->originalPosition = relic->getTransform()->getPosition();

    // Load sounds
    if (!relicGetBuffer.loadFromFile("sounds/relicget.wav"))
        std::cout << "ERROR: can't load sound sounds/relicget.wav" << std::endl;
    relicGetSound.setBuffer(relicGetBuffer);
    relicGetSound.setVolume(70.0f);
}

void RelicScript::update(float dt) {
    auto relicPos = relic->getTransform()->getPosition();
    auto playerPos = player->getTransform()->getPosition();

    if (this->attached) {
        // Place relic in front of player view
        auto t = glm::rotateY(player->getTransform()->getFront(), glm::radians(30.f));
        relic->getTransform()->setPosition(player->getTransform()->getPosition() + 0.25 * t + glm::vec3(0, -.1, 0));
        relic->getTransform()->setRotation(glm::vec3(0, player->getTransform()->getRotation().y-0.7, 0));

        // Check if relic inside target zone
        auto distance = relicPos - destination;
        if (glm::length(distance) <= 2) {
            // SFX
            relicGetSound.setPosition(relicPos.x, relicPos.y, relicPos.z);
            relicGetSound.play();

            // TODO: visual feedback for score
            std::cout << "+1 point" << std::endl;

            // Put back at original position
            attached = false;
            relic->getTransform()->scale(glm::vec3(5, 5, 5));
            relic->getTransform()->setPosition(originalPosition);
        }

    } else {
        auto distance = relicPos - playerPos;
        // Pick up relic if close enough
        if (glm::length(distance) <= 1.1) {
            attached = true;
            relic->getTransform()->scale(glm::vec3(0.2, 0.2, 0.2));
        }
    }
}

bool RelicScript::isAttached() {
    return attached;
}

void RelicScript::reset() {
    if (attached) {
        attached = false;
        relic->getTransform()->scale(glm::vec3(5, 5, 5));
    }
    relic->getTransform()->setPosition(originalPosition);
}
