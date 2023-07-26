#include "stdafx.h"
#include "Map.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "Background.h"
#include "Platform.h"
#include "ItemSpeedUp.h"
#include "ItemBigHealPack.h"
#include "ItemBig.h"

#include "Cookie.h"
#include "SpriteEffect.h"
#include "Coin.h"

#include "Obstacle.h"
#include "PatternObject.h"
#include <rapidcsv.h>


Map::Map(const std::string& n)
	: GameObject(n)
{
}

Map::~Map()
{
}

void Map::SetPosition(const sf::Vector2f& p)
{
	position = p;
}

void Map::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Map::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
}

void Map::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
}

void Map::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	// 배경
	bg1 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background1.png"));
	bg2 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background2.png"));
	bg1->SetPosition(0.f, 0.f);
	bg1->sprite.setScale(3.02f, 3.0f);
	bg1->sortLayer = 0;

	bg2->SetPosition(0.f, 0.f);
	bg2->sprite.setScale(3.02f, 3.f);
	bg2->sortLayer = -1;

	bg3 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background1.png"));
	bg4 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background2.png"));
	bg3->SetPosition(2400.f, 0.f);
	bg3->sprite.setScale(3.02f, 3.0f);
	bg3->sortLayer = 0;

	bg4->SetPosition(2400.f, 0.f);
	bg4->sprite.setScale(3.02f, 3.f);
	bg4->sortLayer = -1;

	std::string fileName = "PatternData/Pattern1.csv";
	CSVRead(fileName, { 2500.f, 0.f });

	// 이펙트 풀 sortLayer 2
	speedUpEffectPool.OnCreate = [this](SpriteEffect* speedUp)
	{
		speedUp->SetAnim("animations/Effect/EffectSpeedUp.csv");
		speedUp->SetDuration(3.f);
		speedUp->SetPool(&speedUpEffectPool);
		speedUp->SetOrigin(Origins::MC);
		speedUp->SetType(EffectTypes::SpeedUp);
		speedUp->sortLayer = 2;
	};
}
void Map::Release()
{

}

void Map::Reset()
{
	currentPatternOrder = 1;
	AllObjectSetCookie();

	bgSpeed = 300.f;
	pfSpeed = 500.f;
	isSpeedUp = false;
	speedUpTimer = 0.f;
	isBigHp = false;
	isBig = false;

	// 배경
	bg1->SetPosition(0.f, 0.f);
	bg2->SetPosition(0.f, 0.f);
	bg3->SetPosition(2400.f, 0.f);
	bg4->SetPosition(2400.f, 0.f);



	for (auto platform : platforms)
	{
		platform->Reset();
	}
	for (auto obstacle : obstacles)
	{
		obstacle->Reset();

	}
	for (auto itemSpeedUp : itemSpeedUps)
	{
		itemSpeedUp->Reset();

	}
	for (auto itemBigHealPack : itemBigHealPacks)
	{
		itemBigHealPack->Reset();

	}
	for (auto itemBig : itemBigs)
	{
		itemBig->Reset();

	}
	for (auto coin : coins)
	{
		coin->Reset();

	}


	for (auto itemSpeedUp : itemSpeedUps)
	{
		itemSpeedUp->sortLayer = 5;
		itemSpeedUp->SetScene(scene);
		itemSpeedUp->SetMap(this);
	}

	for (auto itemBigHP : itemBigHealPacks)
	{
		itemBigHP->sortLayer = 5;
		itemBigHP->SetScene(scene);
		itemBigHP->SetMap(this);
	}


	for (auto coin : coins)
	{
		coin->sortLayer = 5;
		coin->SetScene(scene);
		coin->SetMap(this);
	}

}

void Map::Update(float dt)
{
	if (isBigTimerOn)
	{
		bigTimer += dt;
	}

	if (bigTimer > bigDuration)
	{
		cookie->SetScale({ 1.0f, 1.0f });
		cookie->rect.setScale({ 1.0f, 1.0f });
		isBigTimerOn = false;
		bigTimer = 0.f;
	}

	//if (itemBig1->IsColPlayer() && !itemBig1->GetIsUsed())
	//{
	//	itemBig1->SetIsUsed(true);
	//	cookie->SetScale({ 2.0f, 2.5f });
	//	cookie->rect.setScale({ 2.0f, 2.5f });
	//	isBigTimerOn = true;
	//}

	//if (itemBigHealPack1->IsColPlayer() && !itemBigHealPack1->GetIsUsed())
	//{
	//	itemBigHealPack1->SetIsUsed(true);
	//	cookie->SetHp(20);
	//}

	for (auto itemBigHP : itemBigHealPacks)
	{
		if (itemBigHP != nullptr)
		{
			EatBigHp(itemBigHP);
		}
	}

	for (auto itemSpeedUp : itemSpeedUps)
	{
		if (itemSpeedUp != nullptr)
		{
			EatSpeedUp(itemSpeedUp);
		}
	}

	if (isSpeedUp)
	{
		speedUpTimer += dt;
		speedUpEffectTimer += dt;
		if (speedUpEffectTimer > speedUpEffectDuration)
		{
			SpriteEffect* speedEffect = speedUpEffectPool.Get();
			speedEffect->SetPosition(cookie->GetPosition());
			speedEffect->SetOrigin(Origins::BC);
			scene->AddGo(speedEffect);
			speedUpEffectTimer = 0.f;
		}
	}
	if (speedUpTimer > speedUpDuration && isSpeedUp)
	{
		isSpeedUp = false;
		ResetSpeed();
	}

	// 코인

	BackgroundMove(dt);

	for (auto platform : platforms)
	{
		ObjectMove(platform, dt);
	}
	for (auto obstacle : obstacles)
	{
		ObjectMove(obstacle, dt);
	}
	for (auto coin : coins)
	{
		ObjectMove(coin, dt);
	}	
	for (auto itemSpeedup : itemSpeedUps)
	{
		ObjectMove(itemSpeedup, dt);
	}
	for (auto itemBigHP : itemBigHealPacks)
	{
		ObjectMove(itemBigHP, dt);
	}	


	patternDiff += -pfSpeed * dt;
	//std::cout << patternDiff << std::endl;
	//if (patternDiff < -1920.f)
	//{
	//	patternDiff = 0.f;
	//	currentPatternOrder++;
	//	if (currentPatternOrder > 3)
	//		currentPatternOrder = 1;
	//	// 패턴 생성
	//	//int Utils::RandomRange()

	//	std::string fileName = "PatternData/Pattern" + std::to_string(currentPatternOrder) + ".csv";
	//	// 다음 패턴 위치에서 생성
	//	//CSVRead("PatternData/Pattern1.csv", {580.f, 0.f});
	//	CSVRead("PatternData/Pattern1.csv", { 2500.f, 0.f});
	//}
	//ItemReset();

	ItemReset();
	PlatformMove(dt);
}

void Map::Draw(sf::RenderWindow& window)
{
	//window.draw();
}

void Map::CSVRead(const std::string& fileName, sf::Vector2f spawnPos)
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	rapidcsv::Document doc(fileName);

	std::vector<std::string> paths = doc.GetColumn<std::string>("Path");
	std::vector<int> types = doc.GetColumn<int>("Type");
	std::vector<float> posX = doc.GetColumn<float>("Pos X");
	std::vector<float> posY = doc.GetColumn<float>("Pos Y");
	std::vector<float> scaleX = doc.GetColumn<float>("Scale X");
	std::vector<float> scaleY = doc.GetColumn<float>("Scale Y");
	std::vector<int> origin = doc.GetColumn<int>("Origin");

	// 1540 = -960
	// 3460 = 960

	// -2500
	for (int i = 0; i < paths.size(); i++)
	{
		posX[i] -= spawnPos.x;
		posY[i] -= windowSize.y * 0.5f;

		repeatDistance = repeatDistance > posX[i] ? repeatDistance : posX[i];
		switch ((PatternObjectType)types[i])
		{
		case PatternObjectType::Platform:
		{
			Platform* platform = (Platform*)scene->AddGo(new Platform(paths[i]));
			platform->vectorType = PatternObjectType::Platform;
			platform->SetPosition(posX[i], posY[i]);
			platform->sprite.setScale(scaleX[i], scaleY[i]);
			platform->SetOrigin((Origins)origin[i]);
			platforms.push_back(platform);
		}
		break;
		case PatternObjectType::Obstacle:
		{
			Obstacle* obstacle = (Obstacle*)scene->AddGo(new Obstacle(paths[i]));
			obstacle->vectorType = PatternObjectType::Obstacle;
			obstacle->SetPosition(posX[i], posY[i]);
			obstacle->sprite.setScale(scaleX[i], scaleY[i]);
			obstacle->SetOrigin((Origins)origin[i]);
			obstacles.push_back(obstacle);
		}
		break;
		case PatternObjectType::ItemSpeedUp:
		{
			ItemSpeedUp* itemSpeed = (ItemSpeedUp*)scene->AddGo(new ItemSpeedUp(paths[i]));
			itemSpeed->vectorType = PatternObjectType::ItemSpeedUp;
			itemSpeed->SetPosition(posX[i], posY[i]);
			itemSpeed->sprite.setScale(scaleX[i], scaleY[i]);
			itemSpeed->SetOrigin((Origins)origin[i]);
			itemSpeedUps.push_back(itemSpeed);
		}
		break;
		case PatternObjectType::ItemBigHealPack:
		{
			ItemBigHealPack* itemBigHP = (ItemBigHealPack*)scene->AddGo(new ItemBigHealPack(paths[i]));
			itemBigHP->vectorType = PatternObjectType::ItemBigHealPack;
			itemBigHP->SetPosition(posX[i], posY[i]);
			itemBigHP->sprite.setScale(scaleX[i], scaleY[i]);
			itemBigHP->SetOrigin((Origins)origin[i]);
			itemBigHealPacks.push_back(itemBigHP);
		}
		break;
		case PatternObjectType::ItemBig:
		{
			ItemBig* itemBig = (ItemBig*)scene->AddGo(new ItemBig(paths[i]));
			itemBig->vectorType = PatternObjectType::ItemBig;
			itemBig->SetPosition(posX[i], posY[i]);
			itemBig->sprite.setScale(scaleX[i], scaleY[i]);
			itemBig->SetOrigin((Origins)origin[i]);
			itemBigs.push_back(itemBig);
		}
		break;
		case PatternObjectType::Coin:
		{
			Coin* coin = (Coin*)scene->AddGo(new Coin(paths[i]));
			coin->vectorType = PatternObjectType::Coin;
			coin->SetType(CoinTypes::Coin);
			coin->SetPosition(posX[i], posY[i]);
			coin->sprite.setScale(scaleX[i], scaleY[i]);
			coin->SetOrigin((Origins)origin[i]);
			coins.push_back(coin);
		}
		break;
		case PatternObjectType::BigCoin:
		{
			Coin* bigCoin = (Coin*)scene->AddGo(new Coin(paths[i]));
			bigCoin->vectorType = PatternObjectType::Coin;
			bigCoin->SetType(CoinTypes::BigCoin);
			bigCoin->SetPosition(posX[i], posY[i]);
			bigCoin->sprite.setScale(scaleX[i], scaleY[i]);
			bigCoin->SetOrigin((Origins)origin[i]);
			coins.push_back(bigCoin);
		}

		break;
		case PatternObjectType::GoldCoin:
		{
			Coin* goldCoin = (Coin*)scene->AddGo(new Coin(paths[i]));
			goldCoin->vectorType = PatternObjectType::Coin;
			goldCoin->SetType(CoinTypes::GoldCoin);
			goldCoin->SetPosition(posX[i], posY[i]);
			goldCoin->sprite.setScale(scaleX[i], scaleY[i]);
			goldCoin->SetOrigin((Origins)origin[i]);
			coins.push_back(goldCoin);

		}
		break;
		case PatternObjectType::BigGoldCoin:
		{
			Coin* bigGoldCoin = (Coin*)scene->AddGo(new Coin(paths[i]));
			bigGoldCoin->vectorType = PatternObjectType::Coin;
			bigGoldCoin->SetType(CoinTypes::BigGoldCoin);
			bigGoldCoin->SetPosition(posX[i], posY[i]);
			bigGoldCoin->sprite.setScale(scaleX[i], scaleY[i]);
			bigGoldCoin->SetOrigin((Origins)origin[i]);
			coins.push_back(bigGoldCoin);
		}

		break;
		case PatternObjectType::Diamond:
		{
			Coin* dia = (Coin*)scene->AddGo(new Coin(paths[i]));
			dia->vectorType = PatternObjectType::Coin;
			dia->SetType(CoinTypes::Diamond);
			dia->SetPosition(posX[i], posY[i]);
			dia->sprite.setScale(scaleX[i], scaleY[i]);
			dia->SetOrigin((Origins)origin[i]);
			coins.push_back(dia);
		}

		break;
		case PatternObjectType::DiamondBox:
		{
			Coin* diaBox = (Coin*)scene->AddGo(new Coin(paths[i]));
			diaBox->vectorType = PatternObjectType::Coin;
			diaBox->SetType(CoinTypes::DiamondBox);
			diaBox->SetPosition(posX[i], posY[i]);
			diaBox->sprite.setScale(scaleX[i], scaleY[i]);
			diaBox->SetOrigin((Origins)origin[i]);
			coins.push_back(diaBox);
		}

		break;
		case PatternObjectType::LuckyBox:
		{
			Coin* luckyBox = (Coin*)scene->AddGo(new Coin(paths[i]));
			luckyBox->vectorType = PatternObjectType::Coin;
			luckyBox->SetType(CoinTypes::LuckyBox);
			luckyBox->SetPosition(posX[i], posY[i]);
			luckyBox->sprite.setScale(scaleX[i], scaleY[i]);
			luckyBox->SetOrigin((Origins)origin[i]);
			coins.push_back(luckyBox);
		}

		break;
		}
		//PatternObject* pattern = (PatternObject*)scene->AddGo(new PatternObject(paths[i]));
		////patterns.push_back(pattern);
		//pattern->SetPosition(posX[i], posY[i]);
		//pattern->SetType((PatternObjectType)types[i]);
		//pattern->sprite.setScale(scaleX[i], scaleY[i]);
		//pattern->SetOrigin((Origins)origin[i]);
		//pattern->sortLayer = 100;
		//pattern->Init();
		//pattern->Reset();

	}
	repeatDistance -= windowSize.x;
	AllObjectSetCookie();

	for (auto itemSpeedUp : itemSpeedUps)
	{
		itemSpeedUp->sortLayer = 5;
		itemSpeedUp->SetScene(scene);
		itemSpeedUp->SetMap(this);
	}

	for (auto itemBigHP : itemBigHealPacks)
	{
		itemBigHP->sortLayer = 5;
		itemBigHP->SetScene(scene);
		itemBigHP->SetMap(this);
	}


	for (auto coin : coins)
	{
		coin->sortLayer = 5;
		coin->SetScene(scene);
		coin->SetMap(this);
	}
}

void Map::SetScene(SceneGame* scene)
{
	this->scene = scene;
}

void Map::SetCookie(Cookie*& cookie)
{
	this->cookie = cookie;
}

void Map::BackgroundMove(float dt)
{
	// 1, 3 배경 2,4 하늘
	float bg1PosX = bg1->GetPosition().x;
	float bg3PosX = bg3->GetPosition().x;
	bg1PosX += -bgSpeed * dt;
	bg3PosX += -bgSpeed * dt;

	bg1->SetPosition({ bg1PosX,bg1->GetPosition().y });
	bg2->SetPosition({ bg1->GetPosition().x,bg1->GetPosition().y });

	bg3->SetPosition({ bg3PosX ,bg3->GetPosition().y });
	bg4->SetPosition({ bg3->GetPosition().x,bg3->GetPosition().y });


	if (bg1->GetPosition().x < -2400.f)
		bg1->SetPosition(2400.f, 0.f);

	if (bg3->GetPosition().x < -2400.f)
		bg3->SetPosition(2400.f, 0.f);
}

void Map::ObjectMove(GameObject* obj, float dt)
{
	float movePos = obj->GetPosition().x;
	movePos += -pfSpeed * dt;
	obj->SetPosition(movePos, obj->GetPosition().y);
	
	
	// 1540 = -960
	// 3460 = 960

	//if (obj->GetPosition().x < -1920.f)
	//{
	//	obj->isOutOfRange = true;
	//}	

	if (obj->GetPosition().x < -960 - repeatDistance)
	{
		obj->SetPosition(1920.f, obj->GetPosition().y);
	}

}

void Map::ClearObject()
{
	platforms.clear();
	obstacles.clear();
	itemSpeedUps.clear();
	itemBigHealPacks.clear();
	itemBigs.clear();
	coins.clear();
}

void Map::ItemReset()
{
	for (auto itemSpeedUp : itemSpeedUps)
	{
		if (itemSpeedUp->GetPosition().x < -1910.f)
		{
			itemSpeedUp->SetActive(true);
			itemSpeedUp->SetIsUsed(false);
		}
	}

	for (auto itemBigHP : itemBigHealPacks)
	{
		if (itemBigHP->GetPosition().x < -1910.f)
		{
			itemBigHP->SetActive(true);
			itemBigHP->SetIsUsed(false);
		}
	}


	for (auto coin : coins)
	{
		if (coin->GetPosition().x < -1910.f)
		{
			coin->SetActive(true);
			coin->SetIsUsed(false);
		}
	}

}



void Map::PlatformMove(float dt)
{
}

void Map::EatSpeedUp(ItemSpeedUp* obj)
{
	if (obj->IsColPlayer() && !isSpeedUp && !obj->GetIsUsed())
	{
		obj->SetIsUsed(true);
		obj->SetActive(false);
		AddSpeedUp();
		isSpeedUp = true;
		speedUpTimer = 0.f;
		//cookie->GetPosition();
	}
}

void Map::EatBigHp(ItemBigHealPack* obj)
{
	if (obj->IsColPlayer() && !obj->GetIsUsed())
	{
		obj->SetIsUsed(true);
		obj->SetActive(false);
		cookie->SetHp(20);
	}
}

void Map::AddSpeedUp()
{
	bgSpeed += 800.f;
	pfSpeed += 800.f;
}

void Map::ResetSpeed()
{
	bgSpeed = 300.f;
	pfSpeed = 500.f;
}

void Map::MoveStop()
{
	bgSpeed = 0.f;
	pfSpeed = 0.f;
}

void Map::AllObjectSetCookie()
{
	for (auto platform : platforms)
		platform->SetCookie(cookie);
	for (auto obstacle : obstacles)
		obstacle->SetCookie(cookie);
	for (auto itemSpeed : itemSpeedUps)
		itemSpeed->SetCookie(cookie);
	for (auto itemBigHP : itemBigHealPacks)
		itemBigHP->SetCookie(cookie);
	for (auto itemBig : itemBigs)
		itemBig->SetCookie(cookie);
	for (auto coin : coins)
		coin->SetCookie(cookie);
	//ground1->SetCookie(cookie);
	//ground2->SetCookie(cookie);
	//pf1->SetCookie(cookie);
	//pf2->SetCookie(cookie);
	//ob1->SetCookie(cookie);
	//ob2->SetCookie(cookie);
	//itemSpeedUp1->SetCookie(cookie);
	//itemBigHealPack1->SetCookie(cookie);
	//itemBig1->SetCookie(cookie);
	//coin1->SetCookie(cookie);

}
