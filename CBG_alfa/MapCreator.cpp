#include "MapCreator.h"


//Funkcje wywo³awcze
void MapCreator::initVariables()
{
	this->textureRect = sf::IntRect(0,0, 50, 50);
}


void MapCreator::initKeyBinds()
{
	ifstream configKeys("Config/mapcreator_keybinds.ini");

	if (configKeys.is_open()) {

		string key = "";
		string key2 = "";

		while (configKeys >> key >> key2) {
			this->keyBinds[key] = this->validKeys->at(key2);
		}

	}

	configKeys.close();
}

void MapCreator::initButtons()
{
	this->buttons["GRASS"] = new GUI::Button(80, 20, 200, 50, &this->font, "Grass",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	
	this->buttons["WATER"] = new GUI::Button(300, 20, 200, 50, &this->font, "Water",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["STONE"] = new GUI::Button(520, 20, 200, 50, &this->font, "Stone",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MapCreator::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Oswald-VariableFont_wght.ttf"))
	{
		cout << "ERROR::MAPCREATOR::COULD NOT LOAD THE FONT";
	}
}

void MapCreator::initTileSelector()
{
	this->selector = new GUI::tileSelector();
}



void MapCreator::initTileMap()
{
	this->tileMap = new Map(50.f, this->window->getSize().x, this->window->getSize().y);
}

void MapCreator::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("QUIT", 200.f, "Quit");
	this->pauseMenu->addButton("SAVE", 280.f, "Save");
}

//Konstruktor i Destruktor
MapCreator::MapCreator(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states)
	:State(window, validKeys, states)
{
	this->initVariables();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();
	this->initTileSelector();
	this->initTileMap();
	this->initPauseMenu();
}

MapCreator::~MapCreator()
{
	for (auto iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}

	delete this->tileMap;
	delete this->pauseMenu;
	

}

//Funkcje
void MapCreator::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void MapCreator::updateEdition(const float& dt)
{
	
	//Dodawanie kafelki
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {

		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);

	}//Usuwanie kafelki
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {

		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);

	} 
	
	if (this->buttons["GRASS"]->isPressed()) {
		this->tileMap->initTexture("Resources/Graphics/grass1.png");
	}
	if (this->buttons["WATER"]->isPressed()) {
		this->tileMap->initTexture("Resources/Graphics/Water1.png");
	}
	if (this->buttons["STONE"]->isPressed()) {
		this->tileMap->initTexture("Resources/Graphics/Stone.png");
	}
	
	
}

void MapCreator::updateButtons()
{
	for (auto& iterator : this->buttons)
	{
		iterator.second->update(this->mousePosView);
	}
}

void MapCreator::updateTileSelector()
{
	this->selector->updateTileSelector(sf::Vector2f(this->mousePosGrid));
}



void MapCreator::updatePauseMenuButtons()
{
	if (this->pauseMenu->isPauseMenuButtonPressed("QUIT")) {
		this->quit = true;
	}
}

void MapCreator::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	this->updateButtons();

	if (!this->paused) { //Unpaused game

		this->updateEdition(dt);
		this->updateTileSelector();
	}
	else { //Paused game
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void MapCreator::renderButtons(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons) {

		iterator.second->render(target);
	
	}

}

void MapCreator::renderTileSelector(sf::RenderTarget* target)
{
	this->selector->renderTileSelector(target);
}



void MapCreator::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderButtons(target);
	this->renderTileSelector(target);

	this->tileMap->render(*target);

	if (this->paused) {

		this->pauseMenu->render(*target);

	}

}

void MapCreator::endState()
{
}
