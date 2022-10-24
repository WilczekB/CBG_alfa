#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y,float gridSize, sf::Texture& texture)
{
	this->tile.setSize(sf::Vector2f(gridSize, gridSize));
	this->tile.setPosition(x, y);
	this->tile.setTexture(&texture);
	
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tile);
}

string Tile::tileTypeToString(TileType type)
{
	switch (type)
	{
	case TileType::GRASS: return "GRASS";
		break;
	case TileType::WATER: return "WATER";
		break;
	case TileType::STONE: return "STONE";
		break;
	default:
		break;
	}
}



