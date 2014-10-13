#include "Animation.h"
#include "ResourceManager.h"


Animation::Animation(const std::string& filename, int timePerFrame, int numberOfFrames) :
	mTimePerFrame(timePerFrame),
	mNumberOfFrames(numberOfFrames),
	mCurrentFrame(0),
	mTexture(ResourceManager::getTexture(filename)),
	mSprite(std::make_shared<sf::Sprite>(*mTexture))
 {
	// Create a rectangle with the width of a single frame from the spritesheet and set the sprite to match the selection
	sf::IntRect textureRectangle(0, 0, (mTexture->getSize().x / mNumberOfFrames), mTexture->getSize().y);
	mSprite->setTextureRect(textureRectangle);
}

Animation::~Animation()
{
}

// Update the animation
void Animation::update()
{
	if (mFrameTimer.getElapsedTime().asMilliseconds() > mTimePerFrame){
		mFrameTimer.restart();

		mCurrentFrame++;

		if (mCurrentFrame >= mNumberOfFrames){
			mCurrentFrame = 0;
		}

		sf::IntRect currentRectangle = mSprite->getTextureRect();
		currentRectangle.left = currentRectangle.width * mCurrentFrame;

		mSprite->setTextureRect(currentRectangle);

	}

}

// Set the position of the animated sprite
void Animation::setPosition(const sf::Vector2f& position)
{
	mSprite->setPosition(position);
}

// Fetch areference to the animated sprite
const std::shared_ptr<sf::Sprite> Animation::getSprite() const
{
	return mSprite;
}
