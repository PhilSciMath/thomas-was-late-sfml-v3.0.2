#pragma once
#include "PlayableCharacter.hpp"
#include <SFML/Graphics.hpp>


class Bob : public PlayableCharacter {
public:
    // Bob's constructor
    Bob();

    // Input handler function override
    bool virtual handle_input();
};
