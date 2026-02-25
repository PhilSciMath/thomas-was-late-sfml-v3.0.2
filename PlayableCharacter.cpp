#include "PlayableCharacter.hpp"


PlayableCharacter::PlayableCharacter() :
    character_sprite(empty_texture)
{}

void PlayableCharacter::spawn(sf::Vector2f start_position, float gravity) {

    // Position the player at the starting point
    character_position = start_position;

    // Initialize gravity
    character_gravity = gravity;

    // Move the character in to position
    character_sprite.setPosition(character_position);
}

void PlayableCharacter::update(float elapsed_time) {

    // Handle movement left and right
    if (right_is_pressed) {
        character_position.x += character_speed * elapsed_time;
    }
    if (left_is_pressed) {
        character_position.x -= character_speed * elapsed_time;
    }

    // Handle jumping
    if (character_is_jumping) {

        // Update how long the jump has been going
        this_jump_duration += elapsed_time;

        // If not at maximum jump duration yet, then this jump can keep going
        if (this_jump_duration < jump_duration) {

            // Move the character up at twice the gravity
            character_position.y -= character_gravity * 2 * elapsed_time;
        }
        else {
            // Maximum jump duration reached, character starts falling
            character_is_jumping = false;
            character_is_falling = true;
        }
    }

    // Handle falling
    if (character_is_falling) {
        character_position.y += character_gravity * elapsed_time;
    }

    // Update all body parts (these are just lines around the sprite)
    sf::FloatRect rect = get_position();

    // Feet
    feet.position.x = rect.position.x + 5;
    feet.position.y = rect.position.y + rect.size.y - 1;
    feet.size.x = rect.size.x - 10;
    feet.size.y = 1;

    // Head
    head.position.x = rect.position.x + 10;
    head.position.y = rect.position.y + (rect.size.y * .3f);
    head.size.x = rect.size.x - 20;
    head.size.y = 1;

    // Right
    right.position.x = rect.position.x + rect.size.x - 2;
    right.position.y = rect.position.y + rect.size.y * .35f;
    right.size.x = 1;
    right.size.y = rect.size.y * .3f;

    // Left
    left.position.x = rect.position.x;
    left.position.y = rect.position.y + rect.size.y * .35f;
    left.size.x = 1;
    left.size.y = rect.size.y * .3f;

    // Move the sprite to the new position
    character_sprite.setPosition(character_position);
}

sf::FloatRect PlayableCharacter::get_position() {
    return character_sprite.getGlobalBounds();
}

sf::Vector2f PlayableCharacter::get_center() {
    return sf::Vector2f ({character_position.x +
        character_sprite.getGlobalBounds().size.x / 2.0f,
        character_position.y
        + character_sprite.getGlobalBounds().size.y / 2.0f});
}

sf::FloatRect PlayableCharacter::get_feet() {
    return feet;
}

sf::FloatRect PlayableCharacter::get_head() {
    return head;
}

sf::FloatRect PlayableCharacter::get_right() {
    return right;
}

sf::FloatRect PlayableCharacter::get_left() {
    return left;
}

sf::Sprite PlayableCharacter::get_sprite() {
    return character_sprite;
}

void PlayableCharacter::stop_falling(float position) {
    character_position.y = position - get_position().size.y;
    character_sprite.setPosition(character_position);
    character_is_falling = false;
}

void PlayableCharacter::stop_right(float position) {
    character_position.x = position - character_sprite.getGlobalBounds().size.x;
    character_sprite.setPosition(character_position);
}

void PlayableCharacter::stop_left(float position) {
    character_position.x = position + character_sprite.getGlobalBounds().size.x;
    character_sprite.setPosition(character_position);
}

void PlayableCharacter::stop_jump() {
    character_is_jumping = false;
    character_is_falling = true;
}



