#include "Particle.hpp"
#include <SFML/System/Vector2.hpp>


Particle::Particle(sf::Vector2f initial_velocity) {

    // Determine the direction
    velocity = initial_velocity;
}

void Particle::update(float dt_as_seconds) {

    // Move the particle
    position += velocity * dt_as_seconds;
}

void Particle::set_position(sf::Vector2f new_position) {
    position = new_position;
}

sf::Vector2f Particle::get_position() {
    return position;
}
