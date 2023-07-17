#pragma once
#include "SpriteGo.h"

class Cookie;
class Scene;
class SceneGame;
class Map;

class Item : public SpriteGo
{
protected:
	Cookie* cookie;
	Scene* scene;
	Map* map;

	bool isUsed = false;

public:
	Item(const std::string& textureId, const std::string& n);
	virtual ~Item() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCookie(Cookie*& cookie);
	bool IsColPlayer();
	void SetScene(SceneGame* scene);
	void SetMap(Map* map);

	bool GetIsUsed() { return isUsed; }
	void SetIsUsed(bool isUsed) { this->isUsed = isUsed; }
};

