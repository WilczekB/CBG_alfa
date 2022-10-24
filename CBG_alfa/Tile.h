#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <fstream>

#include "AnimationComponent.h"

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

enum class TileType
{
	GRASS,
	WATER,
	STONE
};

class Tile
{
private:

protected:

	sf::RectangleShape tile;


public:

	//Konstruktor i Destruktor
	Tile();
	Tile(float x, float y, float gridSize, sf::Texture& texture);
	virtual ~Tile();

	//Funkcje
	void update();
	void render(sf::RenderTarget& target);
	string tileTypeToString(TileType type);
};

#endif TILE_H