#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Config.hpp"
#include "SFML/System.hpp"

using namespace std;

class State
{
protected:
	stack<State*>* states;
	sf::RenderWindow* window;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	map<string, int>* validKeys;
	map<string, int> keyBinds;
	vector<sf::Texture> textures;

	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;


	//Funkcja wywowa³wcza
	virtual void initKeyBinds()=0;

public:
	//Konstruktor i Destruktor
	State(sf::RenderWindow* window, map<string, int>* validKeys,stack<State*>* states);
	virtual ~State();

	//Akcesory
	const bool& getQuit() const;
	const bool getKeyTime();

	//Funkcje 
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePos();
	virtual void updateKeyTime(const float& dt);

	void pauseState();
	void unpauseState();
};

#endif
