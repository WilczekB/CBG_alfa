#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

using namespace std;

class PauseMenu
{
private:

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text menuText;

	map<string, GUI::Button*> buttons;

public:

	//Konstruktor i Destruktor
	PauseMenu(sf::RenderWindow &window, sf::Font& font);
	virtual ~PauseMenu();

	//Akcesor
	map<string, GUI::Button*>& getButtons();

	//Funkcje
	void render(sf::RenderTarget& target);
	void update(const sf::Vector2f& mousePos);
	void addButton(const string key, float y, const string text);
	const bool isPauseMenuButtonPressed(const string key);
};

#endif

