#include "State.h"

State::State(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states)
{
	this->states = states;
	this->window = window;
	this->validKeys = validKeys;
	this->quit = false;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State()
{
}

//Akcesory
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {

		this->keyTime = 0.f;
		return true;
	}
	return false;
}
//Funkcje
void State::updateMousePos()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(this->mousePosView.x) / 50.f,
		static_cast<unsigned>(this->mousePosView.y) / 50.f
	);
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 100.f * dt;
	}
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}


