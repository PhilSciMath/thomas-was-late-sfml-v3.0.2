#include "Engine.hpp"


void Engine::draw() {

    // Clean the last frame painting the screen white
    m_window.clear(sf::Color::White);

    // Handling the full screen mode
    if (!m_screen_is_split) {

        m_window.setView(m_bg_main_view); // Switch to background view
        m_window.draw(m_bg_sprite);       // Then draw the background
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
    }

    // Handling the split screen mode
    else {

        // Drawing first Thomas' side of the screen
        m_window.setView(m_bg_left_view); // Switch to left background view
        m_window.draw(m_bg_sprite);       // Draw the background there
        m_window.setView(m_left_view);    // Then Switch to left view

        m_window.draw(va_level, &texture_tiles); // Draw the level

        m_window.draw(bob.get_sprite());     // Draw Bob first
        m_window.draw(thomas.get_sprite());  // Draw thomas

        // Now drawing Bob's side of the screen
        m_window.setView(m_bg_right_view); // Switch to right background view
        m_window.draw(m_bg_sprite);        // Draw the sprite there
        m_window.setView(m_right_view);    // Then switch to the right view

        m_window.draw(va_level, &texture_tiles); // Draw the level

        m_window.draw(thomas.get_sprite());  // Draw Thomas first
        m_window.draw(bob.get_sprite());     // Then draw Bob
    }

    // Handling the HUD
    m_window.setView(m_hud_view); // Switch to HUD view



    // Show everything drawn
    m_window.display();
}
