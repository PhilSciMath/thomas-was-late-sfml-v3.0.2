#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.hpp"
#include "TextureHolder.hpp"
#include "Thomas.hpp"
#include "Bob.hpp"
#include "LevelManager.hpp"
#include "SoundManager.hpp"


class Engine {
private:
    // The only instance of texture holder class
    TextureHolder t_holder;

    // Add Thomas and Bob characters
    Thomas thomas;
    Bob bob;

    // A class to manage levels
    LevelManager lm;

    // Create a sound manager object
    SoundManager sm;

    // Each tile is a square 50x50
    const int TILE_SIZE = 50;

    // Using triangles to make squared tiles, useful for VertexArray
    const int VERTS_IN_QUAD = 6;

    // Gravity force: number of pixels pushed down each second
    const int GRAVITY = 300;

    // The render window object
    sf::RenderWindow m_window;

    // The main views
    sf::View m_main_view;
    sf::View m_left_view;
    sf::View m_right_view;

    // Three views for the background
    sf::View m_bg_main_view;
    sf::View m_bg_left_view;
    sf::View m_bg_right_view;

    // A view for the HUD
    sf::View m_hud_view;

    // Sprite background (texture set in the constructor using t_holder)
    sf::Sprite m_bg_sprite;

    // State of the game: playing or not playing
    bool m_game_is_playing = false;

    // Focus on character 1 or 2
    bool m_char_1_is_focused = true;

    // Start in full screen mode (not split mode)
    bool m_screen_is_split = false;

    // Time remaining to finish the current level in seconds
    float m_time_left = 10;

    // Time taken since the game started
    sf::Time m_total_game_time;

    // Is it time for a new/first level?
    bool m_new_level_required = true;

    // The vertex array for the level tiles
    sf::VertexArray va_level;

    // The 2D array with the map for the level
    int** array_level = NULL;

    // The texture for the level tiles
    sf::Texture texture_tiles;

    // Some private functions for internal use (the 3 main parts of the loop)
    void input();
    void update(float dt_as_seconds);
    void draw();

    // Load a new level
    void load_level();

    // Function to handle collision detection
    bool detect_collisions(PlayableCharacter& character);

    // Make a vector of the best places to emit sound from
    void populate_emitters(std::vector<sf::Vector2f>& sound_emitters,
                           int** array_level);

    // A vector of Vector2f for the fire emitter locations
    std::vector<sf::Vector2f> fire_emitters;

public:
    // Constructor
    Engine();

    // This function calls all three private functions
    void run();

};
