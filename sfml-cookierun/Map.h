#pragma once
#include "GameObject.h"
#include "ObjectPool.h"

class Background;
class Scene;
class SceneGame;
class Platform;
class Cookie;
class ItemSpeedUp;
class SpriteEffect;

class Map : public GameObject
{
protected:
	SceneGame* scene;
	Cookie* cookie;

	// 1, 3 배경 2, 4 하늘
	Background* bg1;
	Background* bg2;
	Background* bg3;
	Background* bg4;

	// 바닥
	Platform* ground1;
	Platform* ground2;

	// 장애물
	Platform* pf1;
	Platform* pf2;

	ItemSpeedUp* itemSpeedUp1;

	float bgSpeed = 300.f;
	float pfSpeed = 500.f;


	// 스피드 아이템 상태를 위한 변수
	float speedUpTimer = 0.0f;
	float speedUpDuration = 3.0f;
	bool isSpeedUp = false;

	ObjectPool<SpriteEffect> effectPool;
public:
	Map(const std::string& n = "");
	virtual ~Map() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetScene(SceneGame* scene);
	void SetCookie(Cookie*& cookie);

	void BackgroundMove(float dt);
	void PlatformMove(float dt);
	void AddSpeedUp();
	void ResetSpeed();
};

