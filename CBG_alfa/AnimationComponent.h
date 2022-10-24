#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

class AnimationComponent
{
private:

	vector<AnimationComponent> animations;

	sf::IntRect bounds;
	sf::IntRect frameSize;

	unsigned int startFrame;
	unsigned int endFrame;
	float duration;
	float currentTime;
	int currentAnim;

public:

	//Konstruktor i Destruktor
	AnimationComponent(const sf::IntRect& frameSize, unsigned int startFrame, unsigned int endFrame, float duration);
	virtual ~AnimationComponent();

	//Funkcje
	unsigned int getLength();
	void addAnim(AnimationComponent& anim);
	void update(const float& dt);
	void changeAnim(unsigned int animNum);


};

#endif

