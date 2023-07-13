#pragma once
#include "GameObject.h"

class Background;
class Scene;
class SceneGame;
class Platform;

class Map : public GameObject
{
protected:
	Scene* scene;

	// 1, 3 배경 2, 4 하늘
	Background* bg1;
	Background* bg2;
	Background* bg3;
	Background* bg4;

	// 장애물
	Platform* pf1;



	float bgSpeed = 300.f;

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

	void BackgroundMove(float dt);
};

