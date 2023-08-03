#pragma once
#include "Item.h"
#include "AnimationController.h"

class ItemSpeedUp : public Item
{
protected:
	AnimationController animation;
public:

	ItemSpeedUp(const std::string& textureId = "", const std::string& n = "");
	virtual ~ItemSpeedUp() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};