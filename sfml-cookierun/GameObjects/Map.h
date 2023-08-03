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

class GameOver;

class Map : public GameObject
{
protected:
	SceneGame* scene;
	Cookie* cookie;

	GameOver* gameOver;

	// 1, 3 배경 2, 4 하늘
	Background* bg1;
	Background* bg2;
	Background* bg3;
	Background* bg4;


	float patternDiff = 0.f;
	int patternCircuit = 0;
	int currentPatternOrder = 0;

	float repeatDistance = 0.f;


	float bgSpeed = 300.f;
	float pfSpeed = 500.f;


	// 아이템 충돌중복 방지 상태 시간
	float timer = 0.0f;
	float duration = 0.1f;

	// 스피드 아이템 상태를 위한 변수
	float speedUpTimer = 0.0f;
	float speedUpDuration = 3.0f;
	bool isSpeedUp = false;

	float speedUpEffectTimer = 0.0f;
	float speedUpEffectDuration = 0.05f;

	// 체력 증가 상태 변수
	bool isBigHp = false;
	
	// 캐릭터 몸체 증가 상태 변수
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

	std::vector<sf::Vector2f> platformsPos;
	std::vector<sf::Vector2f> obstaclesPos;
	std::vector<sf::Vector2f> itemSpeedUpsPos;
	std::vector<sf::Vector2f> itemBigHealPacksPos;
	std::vector<sf::Vector2f> itemBigsPos;
	std::vector<sf::Vector2f> coinsPos;

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

	void CSVRead(const std::string& fileName, sf::Vector2f spawnPos);

	bool GetIsAlive();

	void SetScene(SceneGame* scene);
	void SetCookie(Cookie*& cookie);
	void SetGameOver(bool isActive);

	void BackgroundMove(float dt);
	void ObjectMove(GameObject* obj, float dt);
	void ClearObject();
	void ItemReset();
	void PlatformMove(float dt);

	void EatSpeedUp(ItemSpeedUp* obj);
	void EatBigHp(ItemBigHealPack* obj);


	void AddSpeedUp();
	void ResetSpeed();
	void MoveStop();

	void AllObjectSetCookie();
};