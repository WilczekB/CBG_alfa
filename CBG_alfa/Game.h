#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
	//Zmienne
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	sf::ContextSettings windowSettings;

	stack<State*> states;
	map<string, int> validKeys;
	vector<sf::VideoMode> videoModes;

	float dt;
	//Funkcja wywo³awcza
	void initWindow();
	void initKeys();
	void initState();
	

public:

	Game();
	virtual ~Game();

	//Funkcje
	void run();
	void update();
	void render();
	void updateSFMLEvents();
	void updateDt();
};


#endif
