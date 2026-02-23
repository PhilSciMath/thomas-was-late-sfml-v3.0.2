#include "Engine.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>


void Engine::input() {

    while (std::optional<sf::Event> event = m_window.pollEvent()) {

        // Handle closing the game
        if (event->is<sf::Event::Closed>()
            || event->is<sf::Event::KeyPressed>()
            && event->getIf<sf::Event::KeyPressed>()->code
            == sf::Keyboard::Key::Escape)
            m_window.close();

        // Handle the player starting the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            m_game_is_playing = true;

        // Handle switching characters
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
            m_char_1_is_focused = !m_char_1_is_focused;

        // Handle switching between full screen and split screen modes
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
            m_screen_is_split = !m_screen_is_split;

    }

    // Handle input and play a sound when jump starts
    if (thomas.handle_input()) {
        sm.play_jump();
    }

    if (bob.handle_input()) {
        sm.play_jump();
    }
}
