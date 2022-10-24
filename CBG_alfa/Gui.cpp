#include "Gui.h"

GUI::Button::Button(float x, float y, float width, float height, sf::Font* font, string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{

	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->shape.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->shape.getGlobalBounds().height / 2.f);
	this->text.setCharacterSize(40);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

GUI::Button::~Button()
{
}

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) {
		return true;
	}

	return false;
}

const string GUI::Button::getText() const
{
	return string();
}


void GUI::Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void GUI::Button::update(const sf::Vector2f& mousePos)
{

	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos)) {

		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			this->buttonState = BTN_PRESSED;

		}

	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}

}

void GUI::Button::setText(const string text)
{
	this->text.setString(text);
}


/// <End of Button Class>
/// 
/// <Beginnig of TileSelector Class>

GUI::tileSelector::tileSelector()
{
	this->selector.setSize(sf::Vector2f(50.f, 50.f));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineColor(sf::Color::Yellow);
	this->selector.setOutlineThickness(1.f);

}

GUI::tileSelector::~tileSelector()
{
}

void GUI::tileSelector::renderTileSelector(sf::RenderTarget* target)
{
	target->draw(this->selector);
}

void GUI::tileSelector::updateTileSelector(const sf::Vector2f& mousePos)
{
	this->selector.setPosition(mousePos.x * 50.f, mousePos.y*50.f);
}

/// End of tileSelector
/// 
/// 
/// 
/// 
/// 
/// Beginnig of textureSelector


//Konstruktor i Destruktor
GUI::textureSelector::textureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet)
{
	this->selectorBounds.setPosition(x, y);
	this->selectorBounds.setSize(sf::Vector2f(width, height));
	this->selectorBounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->selectorBounds.setOutlineThickness(1.f);
	this->selectorBounds.setOutlineColor(sf::Color(250, 250, 250, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);


	if (this->sheet.getGlobalBounds().width > this->selectorBounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->selectorBounds.getGlobalBounds().width, this->selectorBounds.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->selectorBounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->selectorBounds.getGlobalBounds().width, this->selectorBounds.getGlobalBounds().height));
	}

	this->active = false;
	this->gridSize = gridSize;

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);
	
}

GUI::textureSelector::~textureSelector()
{
}


//Funkcje
void GUI::textureSelector::update(const sf::Vector2i& MousPosWindow)
{
	if (this->selectorBounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousPosWindow))) {
		this->active = true;
	}
	else {
		this->active = false;
	}

	if (this->active) {

		this->mousPosGrid.x = (mousPosGrid.x - static_cast<int>(this->selectorBounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
		this->mousPosGrid.y = (mousPosGrid.y - static_cast<int>(this->selectorBounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

		this->selector.setPosition(

			this->selectorBounds.getPosition().x + this->mousPosGrid.x * this->gridSize,
			this->selectorBounds.getPosition().y + this->mousPosGrid.y * this->gridSize

		);
	}

}

void GUI::textureSelector::render(sf::RenderTarget* target)
{
	target->draw(this->selectorBounds);
	target->draw(this->sheet);
	if(this->active)
		target->draw(this->selector);
}

const bool& GUI::textureSelector::isActive() const
{
	return this->active;
}
