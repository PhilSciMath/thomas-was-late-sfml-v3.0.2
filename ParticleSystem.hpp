#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Particle.hpp"


class ParticleSystem : public sf::Drawable {

private:
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    float duration;
    bool is_running = false;

public:
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    void init(unsigned int count);
    void emit_particles(sf::Vector2f position);
    void update(float elapsed);
    bool running();
};

