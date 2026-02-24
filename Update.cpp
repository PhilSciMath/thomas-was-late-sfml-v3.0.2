#include "Engine.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <sstream>


void Engine::update(float dt_as_seconds) {

    // Handle loading new levels
    if (m_new_level_required) {
        load_level();
    }

    // Handle the playing state
    if (m_game_is_playing) {

        // Update both characters
        thomas.update(dt_as_seconds);
        bob.update(dt_as_seconds);

        // Detect collisions, check both characters reached the goal tile
        if (detect_collisions(thomas) && detect_collisions(bob)) {

            // New level required
            m_new_level_required = true;

            // Play the reach goal sound
            sm.play_reach_goal();
        }
        else {
            // Runs Bob collision detection
            detect_collisions(bob);
        }

        // Let Bob and Thomas jump on each on each other's head
        if (bob.get_feet().findIntersection(thomas.get_head()))
            bob.stop_falling(thomas.get_head().position.y);
        else if (thomas.get_feet().findIntersection(bob.get_head()))
            thomas.stop_falling(bob.get_head().position.y);

        // Reduce the time the player has left
        m_time_left -= dt_as_seconds;

        // When time has run out for any character, start new level
        if (m_time_left <= 0)
            m_new_level_required = true;

    } // End if game state is playing

    // Check if fire sound needs to be played
    std::vector<sf::Vector2f>::iterator it;
    for (it = fire_emitters.begin(); it != fire_emitters.end(); it++) {

        // Where is the emitter? Store the location in pos
        float pos_x = (*it).x;
        float pos_y = (*it).y;

        // Is the emitter near the player? Then make a 500px rectangle
        // around the emitter
        sf::FloatRect local_rect({pos_x - 250, pos_y - 250}, {500.f, 500.f});

        // Is the player inside local_rect?
        if (thomas.get_position().findIntersection(local_rect)) {
            // Play the sound and pass in the location as well
            sm.play_fire(sf::Vector2f({pos_x, pos_y}), thomas.get_center());
        }
    }

    // Set the appropriate view around each character
    if (m_screen_is_split) {
        m_left_view.setCenter(thomas.get_center());
        m_right_view.setCenter(bob.get_center());
    }
    else {
        // Full screen, center view around the character in focus
        if (m_char_1_is_focused)
            m_main_view.setCenter(thomas.get_center());
        else
            m_main_view.setCenter(bob.get_center());
    }

    // Time to update the HUD?
    // Increment number of frames since last HUD update
    frames_since_last_update++;

    // Update the HUD every target_frames_per_hud_upadte frames
    if (frames_since_last_update > target_frames_per_hud_update) {

        // Update game HUD text
        std::stringstream ss_time;
        std::stringstream ss_level;

        // Update the time text
        ss_time << static_cast<int>(m_time_left);
        hud.set_time_text(ss_time.str());

        // Update the level text
        ss_level.str("");   // This line
        ss_level.clear();   // And this one together fixed a problem
        ss_level << "Level: " << lm.get_current_level();
        hud.set_level_text(ss_level.str());

        // Reset frames to next update
        frames_since_last_update = 0;
    }
}
