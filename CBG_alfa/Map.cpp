#include "Map.h"


//Konstruktor i Destruktor
Map::Map(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSize = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = width;
	this->mapSize.y = height;
	this->layers = 4;


	this->tileMap.resize(this->mapSize.x, vector < vector<Tile*> >());
	for (size_t x = 0; x  < this->mapSize.x; x ++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			this->tileMap[x].resize(this->mapSize.y, vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->tileMap[x][y].resize(this->layers, nullptr);
			}

		}
	}


}

Map::~Map()
{
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{

				delete this->tileMap[x][y][z];
			}

		}
	}
}



//Funkcje
void Map::update()
{
}

void Map::render(sf::RenderTarget& target)
{
	for (auto& x : this->tileMap) {

		for (auto& y : x) {

			for (auto& z : y) {

				if (z != nullptr) {
					z->render(target);
				}

			}

		}

	}

}


void Map::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->mapSize.x && x >= 0 && y < this->mapSize.y && y >= 0 && z < this->layers && z >= 0) {

		if (this->tileMap[x][y][z] == nullptr) {

			this->tileMap[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTexture);
		
		}
	}
}

void Map::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->mapSize.x && x >= 0 && y < this->mapSize.y && y >= 0 && z < this->layers && z >= 0) {

		if (this->tileMap[x][y][z] != nullptr) {

			delete this->tileMap[x][y][z];
			this->tileMap[x][y][z] = nullptr;
		}
	}
}


void Map::initTexture(string file_name)
{
	this->tileTexture.loadFromFile(file_name);
}

void Map::saveMapToFile(const string file_name)
{
	ofstream output_file;
	output_file.open(file_name);
	if (output_file.is_open()) {

		output_file << this->mapSize.x << " " << this->mapSize.y << '\n'
			<< this->gridSize << '\n'
			<< this->layers << '\n';

		for (size_t x = 0; x < this->mapSize.x; x++)
		{
			for (size_t y = 0; y < this->mapSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{

					
				}

			}
		}

	}
	else {
		cout << "ERROR::NOT ABLE TO SAVE THE MAP TO " << file_name << '\n';
	}

	output_file.close();
}

void Map::loadMapToFile(const string file_name)
{
}