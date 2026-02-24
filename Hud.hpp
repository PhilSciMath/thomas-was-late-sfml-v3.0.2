#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>


class Hud {

private:
    sf::Font font;
    sf::Text start_text;
    sf::Text time_text;
    sf::Text level_text;

public:
    Hud();

    sf::Text get_message();
    sf::Text get_level_text();
    sf::Text get_time_text();

    void set_level_text(std::string text);
    void set_time_text(std::string text);
};
