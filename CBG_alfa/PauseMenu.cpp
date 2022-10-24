#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)
	)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y)
	)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		0.f
	)
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(200, 200, 200, 255));
	this->menuText.setCharacterSize(70);
	this->menuText.setString("Pauza");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);
}

PauseMenu::~PauseMenu()
{
	for (auto iterator = this->buttons.begin(); iterator != this->buttons.end(); ++iterator) {

		delete iterator->second;

	}
}

//Akcesor
map<string, GUI::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Funkcje
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons) {
		
		i.second->render(&target);

	}

	target.draw(this->menuText);
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::addButton(const string key, float y, const string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - this->container.getGlobalBounds().width / 2.f;
	this->buttons[key] = new GUI::Button(x, y, 250.f, 50.f, &this->font, text,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

const bool PauseMenu::isPauseMenuButtonPressed(const string key)
{
	return this->buttons[key]->isPressed();
}
