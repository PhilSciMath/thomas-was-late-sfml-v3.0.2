#include "Engine.hpp"


void Engine::draw() {

    // Clean the last frame painting the screen white
    m_window.clear(sf::Color::White);

    // Update the shader parameters
    ripple_shader.setUniform("uTime", m_total_game_time.asSeconds());

    // Handling the full screen mode
    if (!m_screen_is_split) {

        m_window.setView(m_bg_main_view); // Switch to background view

        // Draw the background with shader effect
        m_window.draw(m_bg_sprite, &ripple_shader);

        m_window.setView(m_main_view);    // Switch back to the main view

        m_window.draw(va_level, &texture_tiles); // Draw the level

        // Draw Thomas and Bob in full screen mode
        if (m_char_1_is_focused) {
            m_window.draw(bob.get_sprite());     // Bob in background
            m_window.draw(thomas.get_sprite());  // Thomas focused
        }
        else {
            m_window.draw(thomas.get_sprite()); // Thomas in background
            m_window.draw(bob.get_sprite());    // Bob focused
        }

        // Draw the particle system
        if (ps.running())
            m_window.draw(ps);
    }

    // Handling the split screen mode
    else {

        // Left side
        m_window.setView(m_bg_left_view); // Switch to left background view

        // Draw background with shader effect
        m_window.draw(m_bg_sprite, &ripple_shader);

        m_window.setView(m_left_view);    // Then Switch to left main view

        m_window.draw(va_level, &texture_tiles); // Draw the level

        m_window.draw(bob.get_sprite());     // Draw Bob first
        m_window.draw(thomas.get_sprite());  // Draw thomas

        // Draw  the particle system
        if (ps.running())
            m_window.draw(ps);

        // Right side
        m_window.setView(m_bg_right_view); // Switch to right background view

        // Draw background with shader effect
        m_window.draw(m_bg_sprite, &ripple_shader);

        m_window.setView(m_right_view);    // Then switch to the right view

        m_window.draw(va_level, &texture_tiles); // Draw the level

        m_window.draw(thomas.get_sprite());  // Draw Thomas first
        m_window.draw(bob.get_sprite());     // Then draw Bob

        // Draw the particle system
        if (ps.running())
            m_window.draw(ps);
    }

    // Handling the HUD
    m_window.setView(m_hud_view);
    m_window.draw(hud.get_level_text()); // Draw the level number
    m_window.draw(hud.get_time_text());  // Draw time left
    if (!m_game_is_playing)
        m_window.draw(hud.get_message()); // Draw "Press Enter" message

    // Show everything drawn
    m_window.display();
}
