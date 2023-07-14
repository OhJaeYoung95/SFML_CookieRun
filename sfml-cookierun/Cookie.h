#pragma once
#include "SpriteGo.h"
class Cookie : public SpriteGo
{
protected:
	bool isAlive = true;
	float velocity = 0.f;
	int jumpCount = 2;

	bool isGround = true;
	bool isLanding = false;
	bool isSliding = false;
	bool isDouble = false;
	//bool isJump = true;

	float jumpForce = -400.f;
	float doubleJumpForce = -350.f;
	float gravity = 500.f;

	float jumpSpeed = 3.f;

	float landingTimer = 0.1f;


public:
	sf::RectangleShape rect;

	Cookie(const std::string& textureId, const std::string& n);
	virtual ~Cookie() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Die();

	float GetVelocity();
	bool GetIsGround();

	void SetIsGround(bool isGround);
	void SetGravity();
	void SetJumpCount();
	void SetIsDouble(bool isDobule);
	//void PickUpItem();
};