#include "AnimationComponent.h"


//Konstruktor i Destruktor
AnimationComponent::AnimationComponent(const sf::IntRect& frameSize, unsigned int startFrame, unsigned int endFrame, float duration)
{
	this->frameSize = frameSize;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->duration = duration;

	this->currentTime = 0.f;
	this->currentAnim = -1;
}

AnimationComponent::~AnimationComponent()
{
}

//Funkcje
unsigned int AnimationComponent::getLength()
{
	return endFrame-startFrame+1;
}

void AnimationComponent::update(const float& dt)
{
	if (currentAnim >= this->animations.size() || currentAnim < 0)
		return;

	if (int((currentTime + dt) / this->animations[currentAnim].duration) > int(currentTime / this->animations[currentAnim].duration))
	{
		int frame = int((currentTime + dt) / this->animations[currentAnim].duration);

		frame %= this->animations[currentAnim].getLength();

		sf::IntRect rect = this->frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * this->currentAnim;
		this->bounds = rect;
	}

	this->currentTime += dt;

	if (this->currentTime > this->animations[currentAnim].duration * this->animations[currentAnim].getLength())
		this->currentTime = 0.f;


}

void AnimationComponent::addAnim(AnimationComponent& anim)
{
	this->animations.push_back(anim);
}

void AnimationComponent::changeAnim(unsigned int animNum)
{
	if (this->currentAnim == animNum || animNum >= this->animations.size() || animNum < 0)
		return;

	this->currentAnim = animNum;

	sf::IntRect rect = this->frameSize;
	rect.top = rect.height * animNum;
	this->bounds = rect;
	this->currentTime = 0.0;
}
