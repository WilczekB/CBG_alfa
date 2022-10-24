#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "TextureManager.h"

using namespace std;

class Map
{
private:

	sf::Vector2u mapSize;


	vector< vector < vector < Tile* > > > tileMap;
	sf::Texture tileTexture;
	unsigned gridSize;
	float gridSizeF;
	unsigned layers;


public:

	//Konstruktor i Destruktor
	Map(float gridSize, unsigned width, unsigned height);
	virtual ~Map();


	//Funkcje
	void update();
	void render(sf::RenderTarget& target);
	void addTile(const unsigned x, const unsigned y, const unsigned z);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void initTexture(string file_name);
	void saveMapToFile(const string file_name);
	void loadMapToFile(const string file_name);
	
};

#endif