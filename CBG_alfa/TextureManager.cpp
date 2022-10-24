#include "TextureManager.h"

//Konstruktor
TextureManager::TextureManager()
{
}


//Funkcje
void TextureManager::loadTextures(const string& file_name, const string& name)
{
    sf::Texture texture;
    texture.loadFromFile(file_name);

    this->textures[name] = texture;
}

sf::Texture& TextureManager::getRef(const string& name)
{
    return this->textures.at(name);
}
