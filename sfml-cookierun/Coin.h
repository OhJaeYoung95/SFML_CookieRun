#pragma once
#include "Item.h"
#include "AnimationController.h"

enum class CoinTypes
{
	None = -1,
	Coin,
	BigCoin,
	GoldCoin,
	BigGoldCoin,
};
class Coin : public Item
{
protected:
	AnimationController animation;
	CoinTypes type = CoinTypes::None;

public:
	Coin(const std::string& textureId = "", const std::string& n = "");
	virtual ~Coin() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetType(CoinTypes type) { this->type = type; }
};

