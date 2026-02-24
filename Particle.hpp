#pragma once
#include <SFML/Graphics.hpp>


class Particle {

private:
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Particle(sf::Vector2f initial_velocity);

    void update(float dt);
    void set_position(sf::Vector2f new_position);
    sf::Vector2f get_position();
};
