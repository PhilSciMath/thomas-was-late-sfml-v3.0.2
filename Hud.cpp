#include "Hud.hpp"
#include <SFML/Graphics/Rect.hpp>


Hud::Hud() :
    font("fonts/RobotoCondensed-Medium.ttf"),
    start_text(font),
    time_text(font),
    level_text(font)
{
    sf::Vector2u resolution;
    resolution = sf::VideoMode::getDesktopMode().size;

    // When paused
    start_text.setCharacterSize(100);
    start_text.setFillColor(sf::Color::White);
    start_text.setString("Press Enter when ready!");

    // Position the text in the middle of the screen
    sf::FloatRect text_rect = start_text.getGlobalBounds();

    start_text.setOrigin({text_rect.position.x + text_rect.size.x / 2.0f,
        text_rect.position.y + text_rect.size.y / 2.0f});

    start_text.setPosition({resolution.x / 2.0f, resolution.y / 2.0f});

    // Time
    time_text.setCharacterSize(75);
    time_text.setFillColor(sf::Color::White);
    time_text.setPosition({resolution.x - 150.0f, 0.0f});
    time_text.setString("------");

    // Level
    level_text.setCharacterSize(75);
    level_text.setFillColor(sf::Color::White);
    level_text.setPosition({25.0f, 0.0f});
    level_text.setString("1");
}

sf::Text Hud::get_message() {
    return start_text;
}

sf::Text Hud::get_level_text() {
    return level_text;
}

sf::Text Hud::get_time_text() {
    return time_text;
}

void Hud::set_level_text(std::string text) {
    level_text.setString(text);
}

void Hud::set_time_text(std::string text) {
    time_text.setString(text);
}
