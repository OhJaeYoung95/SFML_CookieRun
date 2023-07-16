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
class Coin;

class Map : public GameObject
{
protected:
	SceneGame* scene;
	Cookie* cookie;

	// 1, 3 ��� 2, 4 �ϴ�
	Background* bg1;
	Background* bg2;
	Background* bg3;
	Background* bg4;

	// �ٴ�
	Platform* ground1;
	Platform* ground2;

	// ��ֹ�
	Platform* pf1;
	Platform* pf2;

	// ������
	ItemSpeedUp* itemSpeedUp1;

	// ����
	Coin* coin1;

	float bgSpeed = 300.f;
	float pfSpeed = 500.f;


	// ���ǵ� ������ ���¸� ���� ����
	float speedUpTimer = 0.0f;
	float speedUpDuration = 3.0f;
	bool isSpeedUp = false;

	float speedUpEffectTimer = 0.0f;
	float speedUpEffectDuration = 0.05f;


	ObjectPool<SpriteEffect> speedUpEffectPool;
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

