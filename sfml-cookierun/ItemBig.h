#pragma once
#include "Item.h"
#include "AnimationController.h"

class ItemBig : public Item
{
protected:
	AnimationController animation;

public:
	ItemBig(const std::string& textureId = "", const std::string& n = "");
	virtual ~ItemBig() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

