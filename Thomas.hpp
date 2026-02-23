#pragma once
#include "PlayableCharacter.hpp"
#include <SFML/Graphics.hpp>


class Thomas : public PlayableCharacter {
public:
    // A constructor specific for Thomas
    Thomas();

    // The overridden input handler function for Thomas
    bool virtual handle_input();
};
