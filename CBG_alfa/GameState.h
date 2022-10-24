#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "Map.h"

class GameState :
    public State
{
private:

    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;

    PauseMenu* pauseMenu;
    Map *tileMap;

    //Funkcja wywo³awcza
    void initBackground();
    void initKeyBinds();
    void initFonts();
    void initTileMap();
    void initPauseMenu();

public:
    
    //Konstruktor i destruktor
    GameState(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states);
    virtual ~GameState();

    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void endState();
};

#endif