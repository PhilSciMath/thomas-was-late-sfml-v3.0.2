#include "Engine.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>


// Engine has a sprite member, which doesn't have a default constructor
// in SFML v3, so we must explicitly initialize this sprite.
Engine::Engine() :
    m_bg_sprite(t_holder.get_texture("graphics/bg.png"))
{
    // Get screen resolution
    sf::Vector2u resolution = sf::VideoMode::getDesktopMode().size;

    // Create a window object with appropriate resolution, title and state
    m_window.create(sf::VideoMode(resolution), "Thomas was Late",
        sf::State::Fullscreen);

    // Setting up the full screen view
    m_main_view.setSize({(float) resolution.x, (float) resolution.y});
    m_hud_view.setViewport(sf::FloatRect({0.f, 0.f},{1.f, 1.f})); // ?????

    // Now the split screen views
    m_left_view.setViewport(
        sf::FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_right_view.setViewport(
        sf::FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));

    // Background view for left and right halves of screen (if split)
    m_bg_left_view.setViewport(
        sf::FloatRect({0.001f, 0.001f}, {0.498f, 0.998f}));
    m_bg_right_view.setViewport(
        sf::FloatRect({0.5f, 0.001f}, {0.499f, 0.998f}));

    // Load the texture for the background vertex array
    texture_tiles = TextureHolder::get_texture("graphics/tileset.png");
}


void Engine::run() {
    // Timing the game
    sf::Clock clock;

    // Main game loop
    while (m_window.isOpen()) {

        // Time taken by the previous loop pass
        sf::Time dt = clock.restart();

        // Update the total game time
        m_total_game_time += dt;

        // Make a decimal fraction of dt
        float dt_as_seconds = dt.asSeconds();

        // Calling each part of the game loop in turn
        input();
        update(dt_as_seconds);
        draw();
    }
}
