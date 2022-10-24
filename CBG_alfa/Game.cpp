#include "Game.h"
using namespace std;

//Funkcje wywo³awcze
void Game::initWindow()
{

	ifstream inputConfig("Config/window.ini");

	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();
	this->videoModes = sf::VideoMode::getFullscreenModes();
	bool fullscreen = false;
	string title = "None";
	unsigned frameLimit = 120;
	bool vSyncEnable = false;
	unsigned antialiasingLvl = 0;

	if (inputConfig.is_open()) {
		getline(inputConfig, title);
		inputConfig >> windowBounds.width >> windowBounds.height;
		inputConfig >> fullscreen;
		inputConfig >> frameLimit;
		inputConfig >> vSyncEnable;
		inputConfig >> antialiasingLvl;
	}

	inputConfig.close();

	
	this->windowSettings.antialiasingLevel = antialiasingLvl;
	if (fullscreen) {
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen, windowSettings);
	}
	else {
		this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	}
	this->window->setFramerateLimit(frameLimit);
	this->window->setVerticalSyncEnabled(vSyncEnable);
}

void Game::initKeys()
{
	ifstream configKeys("Config/valid_keys.ini");

	if (configKeys.is_open()) {
		
		string key = "";
		int key_value = 0;

		while (configKeys >> key >> key_value) {
			this->validKeys[key] = key_value;
		}

	}

	configKeys.close();

	//Debug
	for (auto i : this->validKeys) {
		cout << i.first << ' ' << i.second << '\n';
	}
}

void Game::initState()
{
	this->states.push(new MainMenuState(this->window, &this->validKeys,&this->states));
}



//Konstruktor i Desktruktor
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initState();
}

Game::~Game()
{
	delete this->window;

	if (!this->states.empty()) {
		
		delete this->states.top();
		this->states.pop();

	}
}



//Funkcje
void Game::run()
{
	while (this->window->isOpen()) {

		this->updateDt();
		this->update();
		this->render();

	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {

			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();

		}
	}
	else { //Aplication shut down

		this->window->close();

	}

}

void Game::render()
{

	this->window->clear();

	//Rendering rzeczy
	if (!this->states.empty()) {
		this->states.top()->render();
	}

	this->window->display();
}

void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->sfEvent)) {

		if (this->sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}

	}

}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

	system("cls");
	cout << this->dt << '\n';
}
