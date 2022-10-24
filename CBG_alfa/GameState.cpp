#include "GameState.h"

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!backgroundTexture.loadFromFile("Resources/backgroundGame.png")) {

		cout << "Error::MainManuState::Could not load the file!" << '\n';

	}

	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initKeyBinds()
{
	ifstream configKeys("Config/gamestate_keybinds.ini");

	if (configKeys.is_open()) {

		string key = "";
		string key2 = "";

		while (configKeys >> key >> key2) {
			this->keyBinds[key] = this->validKeys->at(key2);
		}

	}

	configKeys.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Oswald-VariableFont_wght.ttf"))
	{
		cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT";
	}
}

void GameState::initTileMap()
{
	this->tileMap = new Map(50.f, 10, 10);
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("QUIT", 200.f, "Quit");
	this->pauseMenu->addButton("SAVE", 280.f, "Save the game");
}



//Konstruktor i Destruktor
GameState::GameState(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states)
	:State(window, validKeys, states)
{
	this->initBackground();
	this->initKeyBinds();
	this->initFonts();
	this->initTileMap();
	this->initPauseMenu();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->tileMap;
}

//Funkcje
void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);

	this->tileMap->render(*target);

	if (this->paused) {

		this->pauseMenu->render(*target);

	}

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isPauseMenuButtonPressed("QUIT")) {
		this->quit = true;
	}
}


void GameState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) { //Unpaused game

		this->updatePlayerInput(dt);
	}
	else { //Paused game
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::endState()
{
	cout << "Ending GameState!" << '\n';
}