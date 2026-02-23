#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>


class TextureHolder {
private:
    // A map that holds strings and textures
    std::map<std::string, sf::Texture> m_textures;

    // A pointer of the same type as the class itself
    static TextureHolder* m_instance;

public:
    TextureHolder();

    static sf::Texture& get_texture(const std::string& filename);
};

#endif
