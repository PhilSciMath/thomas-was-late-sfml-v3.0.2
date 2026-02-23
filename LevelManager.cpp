#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <sstream>
#include <fstream>
#include "LevelManager.hpp"


int** LevelManager::next_level(sf::VertexArray& r_va_level) {

    // Current number of tiles reset to zero
    level_size = {0, 0};

    // Get the next level
    current_level++;

    if (current_level > NUM_LEVELS) {
        current_level = 1;     // Return to level 1 after the last level
        time_modifier -= .1f;  // Reduce time to finish level 1
    }

    // Load the appropriate level from a text file
    std::string level_to_load;
    switch (current_level) {

        case 1: {
            level_to_load = "levels/level1.txt";
            start_position = {100, 100};
            base_time_limit = 30.0f;
            break;
        }

        case 2: {
            level_to_load = "levels/level2.txt";
            start_position = {100, 3600};
            base_time_limit = 100.0f;
            break;
        }

        case 3: {
            level_to_load = "levels/level3.txt";
            start_position = {1250, 0};
            base_time_limit = 30.0f;
            break;
        }

        case 4: {
            level_to_load = "levels/level4.txt";
            start_position = {50, 200};
            base_time_limit = 50.0f;
            break;
        }
    } // End switch

    // Computing how many tiles we need to the new level
    std::ifstream input_file(level_to_load); // Open the text file
    std::string s;

    while (getline(input_file, s))
        ++level_size.y;             // Increase vertical number of tiles
    level_size.x = s.length();      // Increase horizontal number of tiles

    // Returning to the start of the file so we can read it again line by line
    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    // Prepare the 2D array to hold the int values from the file
    int** array_level = new int* [level_size.y];
    for (size_t i = 0; i < level_size.y; ++i) {
        // Add a new array into each array elelment
        array_level[i] = new int [level_size.x];
    }

    // Loop through the text file again, store all values in the 2D array
    std::string row;
    int y = 0;
    while (input_file >> row) {
        for (size_t x = 0; x < row.length(); x++) {
            const char val = row[x];
            array_level[y][x] = atoi(&val);
        }
        y++;
    }

    // Close the text file
    input_file.close();

    // The type of primitive we are using with vertex array
    r_va_level.setPrimitiveType(sf::PrimitiveType::Triangles);

    // Set the size of the vertex array
    r_va_level.resize(level_size.x * level_size.y * VERTS_IN_QUAD);

    // Start at the beginning of the vertex array
    int current_vertex = 0;

    for (size_t x = 0; x < level_size.x; x++) {
        for (size_t y = 0; y < level_size.y; y++) {

            // Position each vertex in the current quad
            // Triangle 1: top-left, bottom-left, top-right
            r_va_level[current_vertex + 0].position =
                sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            r_va_level[current_vertex + 1].position =
                sf::Vector2f(x *TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);
            r_va_level[current_vertex + 2].position =
                sf::Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

            // Triangle 2: top-right, bottom-left, bottom-right
            r_va_level[current_vertex + 3].position =
                sf::Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);
            r_va_level[current_vertex + 4].position =
                sf::Vector2f(x * TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);
            r_va_level[current_vertex + 5].position =
                sf::Vector2f((x * TILE_SIZE) + TILE_SIZE,
                             (y * TILE_SIZE) + TILE_SIZE);

            // Adjusting the texture from the tile set to use with this quad
            int vertical_offset = array_level[y][x] * TILE_SIZE;

            r_va_level[current_vertex + 0].texCoords =
                sf::Vector2f(0, vertical_offset);
            r_va_level[current_vertex + 1].texCoords =
                sf::Vector2f(0, vertical_offset + TILE_SIZE);
            r_va_level[current_vertex + 2].texCoords =
                sf::Vector2f(TILE_SIZE, vertical_offset);
            r_va_level[current_vertex + 3].texCoords =
                sf::Vector2f(TILE_SIZE, vertical_offset);
            r_va_level[current_vertex + 4].texCoords =
                sf::Vector2f(0, vertical_offset + TILE_SIZE);
            r_va_level[current_vertex + 5].texCoords =
                sf::Vector2f(TILE_SIZE, vertical_offset + TILE_SIZE);

            // Get ready for the next 6 vertices
            current_vertex = current_vertex + VERTS_IN_QUAD;
        }
    }

    return array_level;
}

sf::Vector2i LevelManager::get_level_size() {
    return level_size;
}

int LevelManager::get_current_level() {
    return current_level;
}

float LevelManager::get_time_limit() {
    return base_time_limit *time_modifier;
}

sf::Vector2f LevelManager::get_start_position() {
    return start_position;
}
