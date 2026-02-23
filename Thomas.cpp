#include "Thomas.hpp"
#include "TextureHolder.hpp"
#include <SFML/Window/Keyboard.hpp>


Thomas::Thomas() :
    // Call the base class constructor since it is not possible for a derived
    // class to initialize base class members in the member initializer list
    PlayableCharacter()
{
    character_sprite.setTexture(
        TextureHolder::get_texture("graphics/thomas.png"), true);

    jump_duration = .45f;
}

// Override the virtual function
bool Thomas::handle_input() {

    player_just_jumped = false;

    // Handle jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        // Jump if standing on a block, but not if falling
        if (!character_is_jumping && !character_is_falling) {
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
    left_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ?
        true : false;

    right_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ?
        true : false;

    return player_just_jumped;
}
