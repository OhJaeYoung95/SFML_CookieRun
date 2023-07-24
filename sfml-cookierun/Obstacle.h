#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Cookie;
class Scene;
class SceneGame;
class Map;

class Obstacle : public SpriteGo
{
protected:

	Cookie* cookie;
	SceneGame* scene;
	Map* map;

	AnimationController animation;
public:
	Obstacle(const std::string& textureId = "", const std::string& n = "");
	virtual ~Obstacle() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCookie(Cookie*& cookie);
	bool IsColPlayer();
	void SetScene(SceneGame* scene);
	void SetMap(Map* map);
};

