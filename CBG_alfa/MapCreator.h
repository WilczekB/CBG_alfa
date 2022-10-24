#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "State.h"
#include "Map.h"
#include "PauseMenu.h"
#include "Gui.h"


class MapCreator:
	public State
{
private:

	sf::Font font;
	sf::IntRect textureRect;
	//sf::RectangleShape selectorRect;

	Map *tileMap;
	PauseMenu* pauseMenu;
	GUI::tileSelector* selector;
	
	

	map<string, GUI::Button*> buttons;

	//Funkcje wywo³awcze
	void initVariables();
	void initKeyBinds();
	void initButtons();
	void initFonts();
	void initTileSelector();
	void initTileMap();
	void initPauseMenu();

public:

	//Konstruktor i Destruktor
	MapCreator(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states);
	virtual ~MapCreator();

	//Funkcje
	void updateInput(const float& dt);
	void updateEdition(const float& dt);
	void updateButtons();
	void updateTileSelector();
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void renderTileSelector(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
	void endState();

};

#endif
