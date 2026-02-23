#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


class LevelManager {
private:
    sf::Vector2i level_size;      // Number of tiles for the current level
    sf::Vector2f start_position;  // World coordinates for spawn of characters
    float time_modifier = 1;      // Each pass through same level reduces time
    float base_time_limit = 0;    // Holds original unmodified time limit
    int current_level = 0;        // What is the current level?
    const int NUM_LEVELS = 4;     // Helps with returning to lvl 1 after 4

public:
    const int TILE_SIZE = 50;     // Tiles are squares 50px each side
    const int VERTS_IN_QUAD = 6;  // Make a square with two triangles, so 6v

    // Getters
    sf::Vector2f get_start_position();
    sf::Vector2i get_level_size();
    int get_current_level();
    float get_time_limit();

    // This one is for building the level layouts from integers in a text file
    int** next_level(sf::VertexArray& r_va_level);
};
