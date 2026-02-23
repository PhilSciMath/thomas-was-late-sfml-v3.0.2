#include "SoundManager.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Listener.hpp>
#include <SFML/System/Vector2.hpp>


SoundManager::SoundManager() :

    fire_buffer("sounds/fire.ogg"),
    fall_in_fire_buffer("sounds/fallinfire.ogg"),
    fall_in_water_buffer("sounds/fallinwater.ogg"),
    jump_buffer("sounds/jump.ogg"),
    reach_goal_buffer("sounds/reachgoal.ogg"),

    fire1_sound(fire_buffer),
    fire2_sound(fire_buffer),
    fire3_sound(fire_buffer),
    fall_in_fire_sound(fall_in_fire_buffer),
    fall_in_water_sound(fall_in_water_buffer),
    jump_sound(jump_buffer),
    reach_goal_sound(reach_goal_buffer)
{
    // When the player is 50 pixels away sound is full volume
    float min_distance = 150;

    // Reducing the sound volume with distance from the player
    float attenuation = 15;

    fire1_sound.setAttenuation(attenuation);
    fire2_sound.setAttenuation(attenuation);
    fire3_sound.setAttenuation(attenuation);

    // Set all the minimum distance levels
    fire1_sound.setMinDistance(min_distance);
    fire2_sound.setMinDistance(min_distance);
    fire3_sound.setMinDistance(min_distance);

    // Loop all fire sounds when they are played
    fire1_sound.setLooping(true);
    fire2_sound.setLooping(true);
    fire3_sound.setLooping(true);
}


void SoundManager::play_fire(sf::Vector2f emitter_location,
                             sf::Vector2f listener_location) {

    // Where is the listener? (We are using Thomas)
    sf::Listener::setPosition({listener_location.x,
        listener_location.y, 0.0f});

    switch (next_sound) {

        case 1: {
            // Locate/move the source of the sound
            fire1_sound.setPosition({emitter_location.x,
                emitter_location.y, 0.0f});

            // Play the sound if not already playing
            if (fire1_sound.getStatus() == sf::Sound::Status::Stopped)
                fire1_sound.play();
            break;
        }

        case 2: {
            // Same as previous case
            fire2_sound.setPosition({emitter_location.x,
                emitter_location.y, 0.0f});

            if (fire2_sound.getStatus() == sf::Sound::Status::Stopped)
                fire2_sound.play();
            break;
        }

        case 3: {
            // Same thing
            fire3_sound.setPosition({emitter_location.x,
                emitter_location.y, 0.0f});

            if (fire3_sound.getStatus() == sf::Sound::Status::Stopped)
                fire3_sound.play();
            break;
        }
    }

    // Increment to the next sound
    next_sound++;

    // Go back to sound 1 when the 3rd one has been started
    if (next_sound > 3)
        next_sound = 1;
}

void SoundManager::play_fall_in_fire() {
    fall_in_fire_sound.setRelativeToListener(true);
    fall_in_fire_sound.play();
}

void SoundManager::play_fall_in_water() {
    fall_in_water_sound.setRelativeToListener(true);
    fall_in_water_sound.play();
}

void SoundManager::play_jump() {
    jump_sound.setRelativeToListener(true);
    jump_sound.play();
}

void SoundManager::play_reach_goal() {
    reach_goal_sound.setRelativeToListener(true);
    reach_goal_sound.play();
}
