#pragma once
#include "GameObject.h"
#include "ObjectPool.h"

class Background;
class Scene;
class SceneGame;
class Platform;
class Cookie;

class ItemSpeedUp;
class ItemBigHealPack;
class ItemBig;

class SpriteEffect;
class Coin;

class Obstacle;

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

	//// �ٴ�
	//Platform* ground1;
	//Platform* ground2;

	//// ����
	//Platform* pf1;
	//Platform* pf2;

	//// ��ֹ�
	//Obstacle* ob1;
	//Obstacle* ob2;

	//// ������
	//ItemSpeedUp* itemSpeedUp1;
	//ItemBigHealPack* itemBigHealPack1;
	//ItemBig* itemBig1;

	//// ����
	//Coin* coin1;

	float bgSpeed = 300.f;
	float pfSpeed = 500.f;


	// ������ �浹�ߺ� ���� ���� �ð�
	float timer = 0.0f;
	float duration = 0.1f;

	// ���ǵ� ������ ���¸� ���� ����
	float speedUpTimer = 0.0f;
	float speedUpDuration = 3.0f;
	bool isSpeedUp = false;

	float speedUpEffectTimer = 0.0f;
	float speedUpEffectDuration = 0.05f;

	// ü�� ���� ���� ����
	bool isBigHp = false;
	
	// ĳ���� ��ü ���� ���� ����
	bool isBig = false;
	bool isBigTimerOn = false;
	float bigTimer = 0.0f;
	float bigDuration = 2.0f;


	ObjectPool<SpriteEffect> speedUpEffectPool;

	std::vector<Platform*> platforms;
	std::vector<Obstacle*> obstacles;
	std::vector<ItemSpeedUp*> itemSpeedUps;
	std::vector<ItemBigHealPack*> itemBigHealPacks;
	std::vector<ItemBig*> itemBigs;
	std::vector<Coin*> coins;

	std::vector<GameObject*>pattern1;
	std::vector<GameObject*>pattern2;


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

	void CSVRead(const std::string& fileName);

	void SetScene(SceneGame* scene);
	void SetCookie(Cookie*& cookie);

	void BackgroundMove(float dt);
	void ObjectMove(GameObject* obj, float dt);
	void ItemReset();
	void PlatformMove(float dt);

	void EatSpeedUp(ItemSpeedUp* obj);
	void EatBigHp(ItemBigHealPack* obj);


	void AddSpeedUp();
	void ResetSpeed();
	void MoveStop();

	void AllObjectSetCookie();
};