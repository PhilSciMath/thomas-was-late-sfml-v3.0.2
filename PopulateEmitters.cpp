#include "Engine.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>


void Engine::populate_emitters(std::vector<sf::Vector2f>& sound_emitters,
                               int** array_level)
{
    // Make sure the vector is empty
    if (!sound_emitters.empty()) {
        sound_emitters.clear();
        sound_emitters.shrink_to_fit();
    }

    // Keep track of the previous emitter so we don't make too many
    sf::FloatRect previous_emitter;

    // Search for fire tiles in the level
    for (size_t x = 0; x < (int) lm.get_level_size().x; x++) {
        for (size_t y = 0; y < (int) lm.get_level_size().y; y++) {

            // Fire is present
            if (array_level[y][x] == 2) {

                // Skip over any fire tiles too near a previous emitter
                if (!sf::FloatRect({(float) x * TILE_SIZE,
                    (float) y * TILE_SIZE}, {(float) TILE_SIZE, (float) TILE_SIZE}).findIntersection(previous_emitter)) {

                    // Add the coordinates of this fire block
                    sound_emitters.push_back(sf::Vector2f({
                        (float) x * TILE_SIZE, (float) y * TILE_SIZE}));

                    // Make a rectangle 6x6 blocks so we don't make any more
                    // emitters too close to this one
                    previous_emitter.position.x = x * TILE_SIZE;
                    previous_emitter.position.y = y * TILE_SIZE;
                    previous_emitter.size.x = TILE_SIZE * 6;
                    previous_emitter.size.y = TILE_SIZE * 6;
                }
            }
        }
    }

    return;
}
