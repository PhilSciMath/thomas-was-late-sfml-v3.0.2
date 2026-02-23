#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>


class PlayableCharacter {
protected:

    // A sprite and an empty texture
    sf::Sprite character_sprite;
    sf::Texture empty_texture;

    // The duration of a jump: when it ends the character starts falling
    float jump_duration;

    // Is the character jumping or falling? Can't jump while in mid-air.
    bool character_is_jumping;
    bool character_is_falling;

    // Direction the character is moving into
    bool left_is_pressed;
    bool right_is_pressed;

    // This is used so we know if jump_duration has been reached.
    float this_jump_duration;

    // Has the player just initiated a jump, if so we play the sound.
    bool player_just_jumped = false;

private:

    // Number of pixels per second the character falls
    float character_gravity;

    // Pixels per second the character can move left/right
    float character_speed = 400;

    // Position (in the world, not the screen) of the character's center
    sf::Vector2f character_position;

    // Character's body "parts" for collision detection
    sf::FloatRect feet;
    sf::FloatRect head;
    sf::FloatRect right;
    sf::FloatRect left;

public:
    // A constructor to fix the sprite problem
    PlayableCharacter();

    // Spawn the character
    void spawn(sf::Vector2f start_position, float gravity);

    // Pure virtual function to override later
    bool virtual handle_input() = 0;

    // Get player's current position
    sf::FloatRect get_position();

    // Get the character's body parts to calculate collision
    sf::FloatRect get_feet();
    sf::FloatRect get_head();
    sf::FloatRect get_left();
    sf::FloatRect get_right();

    // Send the sprite to main
    sf::Sprite get_sprite();

    // Stopping movement in all directions when colliding with something
    void stop_falling(float position);
    void stop_left(float position);
    void stop_right(float position);
    void stop_jump(); // Or when jump duration has been reached

    // Get the center of the character
    sf::Vector2f get_center();

    // Update the character every frame
    void update (float elapsed_time);
};
