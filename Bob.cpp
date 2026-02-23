#include "TextureHolder.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Bob.hpp"

Bob::Bob() : PlayableCharacter()
{
    character_sprite.setTexture(
        TextureHolder::get_texture("graphics/bob.png"), true);

    jump_duration = 0.25f;
}

// Override the virtual function
bool Bob::handle_input() {

    player_just_jumped = false;

    // Handle jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        if (!character_is_jumping && !character_is_falling) {
            // Start jumping if not jumping/falling
            character_is_jumping = true;
            this_jump_duration = 0;
            player_just_jumped = true;
        }
    }
    else {
        character_is_jumping = false;
        character_is_falling = true;
    }

    // Handle left/right movement
    left_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ?
        true : false;
    right_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ?
        true : false;

    return player_just_jumped;
}
