#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Engine.h"
#include "AssetList.h"
#include "AAnimation.h"
#include "IdList.h"

class GameObject:public Drawable, public Asset
{
protected:
	string currentAnimation;
	IdList idList;
	Sprite sprite;

	FloatRect hitBox;
	Vector2f position;
	Vector2f velocity;

public:

	GameObject()
		: Asset()
	{
		hitBox = FloatRect(0, 0, 0, 0);
		position = Vector2f(0, 0);
		velocity = Vector2f(0, 0);
	}

	GameObject(const string& name, const string& currentAnimation = "none", const FloatRect& hitBox = FloatRect(0, 0, 0, 0), const Vector2f& velocity = Vector2f(0, 0))
		: Asset(name),
		currentAnimation(currentAnimation),
		hitBox(hitBox),
		velocity(velocity)
	{
		position.x = hitBox.left + (hitBox.width / 2);
		position.y = hitBox.top + (hitBox.top / 2);
	}

	GameObject(const string& name, const string& currentAnimation = "none", const Vector2f& position = Vector2f(0, 0), const Vector2f& size = Vector2f(0, 0), const Vector2f& velocity = Vector2f(0, 0))
		: Asset(name),
		currentAnimation(currentAnimation),
		velocity(velocity)
	{
		hitBox.width = size.x;
		hitBox.height = size.y;
		hitBox.left = position.x - (size.x / 2);
		hitBox.top = position.y - (size.y / 2);
	}

	~GameObject()
	{
	}

	GameObject(const GameObject& other)
		: Drawable(other),
		  Asset(other),
		  currentAnimation(other.currentAnimation),
		  idList(other.idList),
		  sprite(other.sprite),
		  hitBox(other.hitBox),
		  position(other.position),
		  velocity(other.velocity)
	{
	}

	GameObject& operator=(const GameObject& other)
	{
		if (this != &other)
		{
			Drawable::operator =(other);
			Asset::operator =(other);
			currentAnimation = other.currentAnimation;
			idList = other.idList;
			sprite = other.sprite;
			hitBox = other.hitBox;
			position = other.position;
			velocity = other.velocity;
		}
		return *this;
	}

	GameObject* clone() override;

	FloatRect getHitBox() const;
	void setHitBox(const FloatRect& hitBox);
	Vector2f getPosition() const;
	void setPosition(const Vector2f& position);
	Vector2f getSize() const;
	void setSize(const Vector2f& size);
	Vector2f getVelocity() const;
	void setVelocity(const Vector2f& velocity);

	virtual void Update(const float& dt, const float& at);

protected:
	void draw(RenderTarget& target, RenderStates states) const override;
};


#endif
