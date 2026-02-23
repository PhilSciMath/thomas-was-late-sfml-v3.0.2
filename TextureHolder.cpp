#include "TextureHolder.hpp"
#include <assert.h>
#include <iostream>

TextureHolder* TextureHolder::m_instance = nullptr;

TextureHolder::TextureHolder() {
    assert(m_instance == nullptr); // If false, game will exit.
    m_instance = this;
}

sf::Texture& TextureHolder::get_texture(const std::string& filename) {
    // Get a reference to m_textures using m_instance
    auto& m = m_instance->m_textures;

    // Iterate through the map to find the key-value where key is filename
    auto key_val = m.find(filename);

    if (key_val != m.end()) {
        // True means we found a match, so return the texture
        return key_val->second;
    }
    else {
        // Match not found, then create a new key-value pair
        sf::Texture& texture = m[filename];
        if (!texture.loadFromFile(filename))
            std::cerr << "Error loading the texture.";
        return texture;
    }
}
