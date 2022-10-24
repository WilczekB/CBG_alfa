#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SFML/Graphics.hpp"
#include <map>

using namespace std;

class TextureManager
{
private:
	
	map<string, sf::Texture> textures;

public:
	TextureManager();

	//Funkcje
	void loadTextures(const string& file_name, const string& name);
	sf::Texture& getRef(const string& name);

};


#endif // !TEXTUREMANAGER_H
