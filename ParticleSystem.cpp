#include "ParticleSystem.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "RandGen.hpp"


void ParticleSystem::init(unsigned int num_particles) {

    vertices.setPrimitiveType(sf::PrimitiveType::Points);
    vertices.resize(num_particles);

    // Create the particles
    for (size_t i = 0; i < num_particles; i++) {

        // Create a radian angle
        float angle = RandGen::get_int(0, 360) * 3.14f / 180.f;

        // Random speed value for this particle
        float speed = RandGen::get_int(0, 600) + 600.f;

        // Create this particle with an initial random velocity
        sf::Vector2f velocity({std::cos(angle) * speed,
            std::sin(angle) * speed});
        particles.push_back(Particle(velocity));
    }
}

void ParticleSystem::update(float dt) {

        duration -= dt;

        std::vector<Particle>::iterator it;
        int current_vertex = 0;
        for (it = particles.begin(); it < particles.end(); it++) {

            // Move the particle
            (*it).update(dt);

            // Update the vertex array
            vertices[current_vertex++].position = it->get_position();
        }

        if (duration < 0)
            is_running = false;
}

void ParticleSystem::emit_particles(sf::Vector2f start_position) {

    is_running = true;
    duration = 2;

    int current_vertex = 0;
    for (auto it = particles.begin(); it != particles.end(); it++) {
        vertices[current_vertex++].color = sf::Color::Yellow;
        it->set_position(start_position);
    }
}

void ParticleSystem::draw(sf::RenderTarget& target,
                          sf::RenderStates states) const
{
    target.draw(vertices, states);
}

bool ParticleSystem::running() {
    return is_running;
}
