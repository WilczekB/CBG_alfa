#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;

enum ButtonStatus
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_PRESSED
};

namespace GUI
{
	class Button
	{
	private:

		short unsigned buttonState;
		//short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:

		//Konstruktor i Destruktor
		Button(float x, float y, float width, float height, sf::Font* font, string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		virtual ~Button();

		//Funkcje
		void render(sf::RenderTarget* target);
		void update(const sf::Vector2f& mousePos);
		void setText(const string text);
		//void setId(const short unsigned id);
		//Funkcje dostêpu
		const bool isPressed() const;
		const string getText() const;
		//const short unsigned& getId() const;

	};

	class tileSelector
	{
	private:

		sf::RectangleShape selector;

	public:

		tileSelector();
		virtual ~tileSelector();

		//Funkcje
		void renderTileSelector(sf::RenderTarget* target);
		void updateTileSelector(const sf::Vector2f& mousePos);

	};

	class textureSelector
	{
	private:

		sf::RectangleShape selectorBounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousPosGrid;
		sf::IntRect textureRect;
		bool active;
		float gridSize;

	public:

		//Konstruktor i Destruktor
		textureSelector(float x, float y, float width, float height, float gridSize,const sf::Texture* texture_sheet);
		~textureSelector();

		//Funkcje
		void update(const sf::Vector2i& MousPosWindow);
		void render(sf::RenderTarget* target);
		const bool& isActive() const;

	};

}

#endif
