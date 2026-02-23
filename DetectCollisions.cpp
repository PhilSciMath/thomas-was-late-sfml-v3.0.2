#include "Engine.hpp"
#include <SFML/Graphics/Rect.hpp>


bool Engine::detect_collisions(PlayableCharacter& character) {

    bool reached_goal = false; // Player didn't reach the goal

    // A rect for all the character parts (global bounds of the sprite)
    sf::FloatRect detection_zone = character.get_position();

    // Make a FloatRect to test each block
    sf::FloatRect block;
    block.size.x = TILE_SIZE;
    block.size.y = TILE_SIZE;

    // Build a zone around the Thomas to detect collisions; because detecting
    // collisions on blocks too far away makes no sense
    int start_x = (int) (detection_zone.position.x / TILE_SIZE) - 1;
    int start_y = (int) (detection_zone.position.y / TILE_SIZE) - 1;
    int end_x = (int) (detection_zone.position.x / TILE_SIZE) + 2;

    // Thomas is taller than bob, check a few tiles vertically
    int end_y = (int) (detection_zone.position.y / TILE_SIZE) + 3;

    // Make sure we don't test positions lower than zero or higher than
    // the end of the array
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x >= lm.get_level_size().x) end_x = lm.get_level_size().x;
    if (end_y >= lm.get_level_size().y) end_y = lm.get_level_size().y;

    // Has the character fallen out of the map?
    float leve_size_x = lm.get_level_size().x * TILE_SIZE;
    float level_size_y = lm.get_level_size().y * TILE_SIZE;
    sf::FloatRect level({0, 0}, {leve_size_x, level_size_y});

    if (!character.get_position().findIntersection(level)) {
        // Respawn the character
        character.spawn(lm.get_start_position(), GRAVITY);
    }

    // Loop through all the local blocks
    for (size_t x = start_x; x < end_x; x++) {
        for (size_t y = start_y; y < end_y; y++) {

            // Initialize the starting position of the current block
            block.position.x = x * TILE_SIZE;
            block.position.y = y * TILE_SIZE;

            // Has the character been burnt or drowned?
            // Use head as this allows him to sink a bit
            if (array_level[y][x] == 2 || array_level[y][x] == 3) {

                if (character.get_head().findIntersection(block)) {

                    // Spawn the character again and play a sound
                    character.spawn(lm.get_start_position(), GRAVITY);

                    // Fire sound
                    if (array_level[y][x] == 2) {
                        sm.play_fall_in_fire();
                    }
                    // Water sound
                    else {
                        sm.play_fall_in_water();
                    }

                }
            }

            // Handle character collision with a regular block
            if (array_level[y][x] == 1) {

                if (character.get_right().findIntersection(block))
                    character.stop_right(block.position.x);
                else if (character.get_left().findIntersection(block))
                    character.stop_left(block.position.x);

                if (character.get_feet().findIntersection(block))
                    character.stop_falling(block.position.y);
                else if (character.get_head().findIntersection(block))
                    character.stop_jump();

                // More to come here once we deal with particle effects


            }

            // Has the character reached the goal
            if (array_level[y][x] == 4) {
                reached_goal = true;
            }
        }
    }

    // All done, return whether or not a new level might be required
    return reached_goal;
}
