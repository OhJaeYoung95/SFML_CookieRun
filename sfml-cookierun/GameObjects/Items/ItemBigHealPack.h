#pragma once
#include "Item.h"
#include "AnimationController.h"

class ItemBigHealPack : public Item
{
protected:
	AnimationController animation;

public:
	ItemBigHealPack(const std::string& textureId = "", const std::string& n = "");
	virtual ~ItemBigHealPack() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

