#include "MainMenuState.h"


//Funkcje wywo³awcze
void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!backgroundTexture.loadFromFile("Resources/Background.png")) {
		
		cout << "Error::MainManuState::Could not load the file!"<<'\n';

	}

	this->background.setTexture(&this->backgroundTexture);

}
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Oswald-VariableFont_wght.ttf"))
	{
		cout<<"ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT";
	}
}
void MainMenuState::initKeyBinds()
{
	ifstream configKeys("Config/mainmenustate_keybinds.ini");

	if (configKeys.is_open()) {

		string key = "";
		string key2 = "";

		while (configKeys >> key >> key2) {
			this->keyBinds[key] = this->validKeys->at(key2);
		}

	}

	configKeys.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new GUI::Button(800, 350, 200, 50, &this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["MAP_CREATOR"] = new GUI::Button(800, 450, 200, 50, &this->font, "Map Creator",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT_STATE"] = new GUI::Button(800, 550, 200, 50, &this->font, "Quit Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

//Konstruktor i destruktor
MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states)
	:State(window, validKeys, states)
{
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();
	
}

MainMenuState::~MainMenuState()
{
	for (auto iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator) {

		delete iterator->second;

	}
}

//Funkcje
void MainMenuState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);
	this->updateButtons();

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
}

void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::endState()
{
}

void MainMenuState::updateButtons()
{
	for (auto& iterator : this->buttons) {

		iterator.second->update(this->mousePosView);

	}

	//Nowa gra
	if (this->buttons["GAME_STATE"]->isPressed()) {

		this->states->push(new GameState(this->window, this->validKeys, this->states));

	}

	//Kreator Mapy
	if (this->buttons["MAP_CREATOR"]->isPressed()) {

		this->states->push(new MapCreator(this->window, this->validKeys, this->states));

	}

	//Wyjœcie z gry
	if (this->buttons["QUIT_STATE"]->isPressed()) {

		this->quit = true;

	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& iterator : this->buttons) {

		iterator.second->render(target);

	}
}
