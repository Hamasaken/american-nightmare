#include "GameObject.h"


GameObject* GameObject::clone()
{
	return new GameObject(*this);
}






FloatRect GameObject::getHitBox() const
{
	return hitBox;
}

void GameObject::setHitBox(const FloatRect& hitBox)
{
	this->hitBox = hitBox;
}

Vector2f GameObject::getPosition() const
{
	return position;
}

void GameObject::setPosition(const Vector2f& position)
{
	this->position = position;
	hitBox.left = position.x - (hitBox.width / 2);
	hitBox.top = position.y - (hitBox.height / 2);
}

Vector2f GameObject::getSize() const
{
	return Vector2f(hitBox.width, hitBox.height);
}

void GameObject::setSize(const Vector2f& size)
{
	hitBox.width = size.x;
	hitBox.height = size.y;
	hitBox.left = position.x - (size.x / 2);
	hitBox.top = position.y - (size.y / 2);
}

Vector2f GameObject::getVelocity() const
{
	return velocity;
}

void GameObject::setVelocity(const Vector2f& velocity)
{
	this->velocity = velocity;
}







void GameObject::Update(const float& dt, const float& at)
{
	if (currentAnimation != "none" && loader.getAnimation(currentAnimation) != nullptr)
	{
		loader.getAnimation(currentAnimation)->play(at, &sprite);
	}

	position += velocity;
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(getPosition());

	velocity = Vector2f(0, 0);
}





void GameObject::draw(RenderTarget& target, RenderStates states) const
{
	if (currentAnimation == "none")
	{
		//cout << "> Error drawing map: No animation selected!" << endl;
	}
	else if (loader.getAnimation(currentAnimation) == nullptr)
	{
		//cout << "> Error drawing map: The selected animation does not exist!" << endl;
	}
	else
	{
		target.draw(sprite, states);
	}
}

