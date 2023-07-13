#pragma once
#include "GameObject.h"

class Background;
class Scene;
class SceneGame;

class Map : public GameObject
{
protected:
	Scene* scene;

	Background* bg1;
	Background* bg2;
	Background* bg3;
	Background* bg4;

	float bgSpeed = 200.f;

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
};

