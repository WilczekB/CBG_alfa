#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "Gui.h"
#include "GameState.h"
#include "MapCreator.h"

class MainMenuState :
    public State
{
private:
    //Zmienne
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;

    map<string, GUI::Button*> buttons;

    //Funkcja wywo³awcza
    void initBackground();
    void initFonts();
    void initKeyBinds();
    void initButtons();

public:
    //Konstrukor i destruktor
    MainMenuState(sf::RenderWindow* window, map<string, int>* validKeys, stack<State*>* states);
    virtual ~MainMenuState();

    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void endState();
    void updateButtons();
    void renderButtons(sf::RenderTarget* target = nullptr);

};

#endif

