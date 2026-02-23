#include "Engine.hpp"


void Engine::load_level() {

    m_game_is_playing = false;

    // Delete the previously allocated memory
    for (size_t i = 0; i < lm.get_level_size().y; ++i) {
        delete[] array_level[i];
    }
    delete[] array_level;

    // Load the next 2D array with the map for the level, also repopulate
    // the vertex array
    array_level = lm.next_level(va_level);

    // Prepare the sound emitters
    populate_emitters(fire_emitters, array_level);

    // Duration of the current time limit
    m_time_left = lm.get_time_limit();

    // Spawn Thomas and Bob
    thomas.spawn(lm.get_start_position(), GRAVITY);
    bob.spawn(lm.get_start_position(), GRAVITY);

    // Make sure this code isn't run again
    m_new_level_required = false;
}
