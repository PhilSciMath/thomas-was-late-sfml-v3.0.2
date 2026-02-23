#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>


class SoundManager {
private:
    // Buffers
    sf::SoundBuffer fire_buffer;
    sf::SoundBuffer fall_in_fire_buffer;
    sf::SoundBuffer reach_goal_buffer;
    sf::SoundBuffer fall_in_water_buffer;
    sf::SoundBuffer jump_buffer;

    // Sounds
    sf::Sound fire1_sound;
    sf::Sound fire2_sound;
    sf::Sound fire3_sound;
    sf::Sound fall_in_fire_sound;
    sf::Sound fall_in_water_sound;
    sf::Sound jump_sound;
    sf::Sound reach_goal_sound;

    // Which fire sound to use next?
    int next_sound;

public:
    SoundManager();

    void play_fire(sf::Vector2f emitter_location,
                   sf::Vector2f listener_location);

    void play_fall_in_fire();
    void play_fall_in_water();
    void play_jump();
    void play_reach_goal();
};
