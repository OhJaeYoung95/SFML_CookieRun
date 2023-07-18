#pragma once
#include "SpriteGo.h"

enum class CookieTypes
{
	None = -1,
	Pancake,
	Pirate,
	Moonlighter,
};

class SceneGame;
class Map;

class Cookie : public SpriteGo
{
protected:
	CookieTypes type = CookieTypes::None;

	SceneGame* scene;
	Map* map;
	int maxHp;
	int hp;

	bool isAlive = true;
	float velocity = 0.f;
	int jumpCount = 2;

	bool isDieAnim = false;
	float dieTimer = 0.f;
	float dieDuration = 1.0f;

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

	float hitTimer = 0.f;
	float hitDuration = 1.f;

	bool isHit = false;

	bool isHitAnim = false;

	float isHitAnimTimer = 0.f;
	float isHitAnimDuration = 0.1f;


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

	float GetMaxHp() { return maxHp; }
	float GetHp() { return hp; }
	bool GetIsHit() { return isHit; }

	void SetType(CookieTypes type) { this->type = type; }

	void SetHp(int value);
	void SetScale(sf::Vector2f value);

	void SetIsGround(bool isGround);
	void SetGravity();
	void SetJumpCount();
	void SetIsDouble(bool isDobule);
	void SetIsHit(bool isHit) { this->isHit = isHit; }

	void SetScene(SceneGame* scene) { this->scene = scene; }
	void SetMap(Map* map) { this->map = map; }
	//void PickUpItem();
};