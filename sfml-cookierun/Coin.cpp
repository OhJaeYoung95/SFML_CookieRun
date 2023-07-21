#include "stdafx.h"
#include "Coin.h"
#include "ResourceMgr.h"
#include "Scene.h"
#include "SceneGame.h"

Coin::Coin(const std::string& textureId, const std::string& n)
	: Item(textureId, n)
{
}

Coin::~Coin()
{
}

void Coin::Init()
{
	Item::Init();
}

void Coin::Release()
{
	Item::Release();
}

void Coin::Reset()
{
	Item::Reset();
	switch (type)
	{
	case CoinTypes::Coin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Jelly/Coin/Coin/Coin.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		sortLayer = 5;
		animation.Play("Coin");
		break;

	case CoinTypes::BigCoin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Jelly/Coin/BigCoin/BigCoin.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		sortLayer = 5;
		animation.Play("BigCoin");
		break;

	case CoinTypes::GoldCoin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Jelly/Coin/GoldCoin/GoldCoin.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		sortLayer = 5;
		animation.Play("GoldCoin");
		break;

	case CoinTypes::BigGoldCoin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Jelly/Coin/BigGoldCoin/BigGoldCoin.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		sortLayer = 5;
		animation.Play("BigGoldCoin");
		break;

	}
}

void Coin::Update(float dt)
{
	Item::Update(dt);
	if (IsColPlayer())
	{
		switch (type)
		{
		case CoinTypes::Coin:
 			scene->AddCoin(1000);
			scene->AddScore(10000);
			scene->AddDia(100);
			break;

		case CoinTypes::BigCoin:
			scene->AddCoin(50);
			break;

		case CoinTypes::GoldCoin:
			scene->AddCoin(10);
			break;

		case CoinTypes::BigGoldCoin:
			scene->AddCoin(100);
			break;

		}

	}
	animation.Update(dt);
}

void Coin::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}