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
#include "Cookie.h"
#include "SpriteEffect.h"
#include "Coin.h"


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

	// 바닥
	ground1 = (Platform*)scene->AddGo(new Platform("graphics/Stage1/Ground.png"));
	ground1->sprite.setScale(10.0f, 1.0f);
	ground1->SetPosition(-300.f, 340.f);
	ground1->SetCookie(cookie);
	ground1->sortLayer = 1;

	ground2 = (Platform*)scene->AddGo(new Platform("graphics/Stage1/Ground.png"));
	ground2->sprite.setScale(10.0f, 1.0f);
	ground2->SetPosition(1300.f, 340.f);
	ground2->SetCookie(cookie);
	ground2->sortLayer = 1;

	// 발판 세팅
	pf1 = (Platform*)scene->AddGo(new Platform("graphics/Stage1/Platform.png"));
	pf1->sprite.setScale(5.0f, 1.0f);
	pf1->SetPosition(400.f, -150.f);
	pf1->SetCookie(cookie);
	pf1->sortLayer = 1;

	pf2 = (Platform*)scene->AddGo(new Platform("graphics/Stage1/Platform.png"));
	pf2->sprite.setScale(5.0f, 1.0f);
	pf2->SetPosition(-300.f, 0.f);
	pf2->SetCookie(cookie);
	pf2->sortLayer = 1;


	// 이펙트 풀
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
	bgSpeed = 300.f;
	pfSpeed = 500.f;
	isSpeedUp = false;
	speedUpTimer = 0.f;

	// 배경
	bg1->SetPosition(0.f, 0.f);
	bg2->SetPosition(0.f, 0.f);
	bg3->SetPosition(2400.f, 0.f);
	bg4->SetPosition(2400.f, 0.f);

	ground1->SetPosition(-300.f, 340.f);
	ground2->SetPosition(1300.f, 340.f);

	pf1->SetPosition(400.f, -150.f);
	pf2->SetPosition(-300.f, 0.f);

	// 아이템 세팅
	itemSpeedUp1 = (ItemSpeedUp*)scene->AddGo(new ItemSpeedUp());
	itemSpeedUp1->SetPosition(0.f, 0.f);
	itemSpeedUp1->SetCookie(cookie);
	itemSpeedUp1->sortLayer = 5;
	itemSpeedUp1->SetScene(scene);
	itemSpeedUp1->SetMap(this);

	// 코인 세팅
	coin1 = (Coin*)scene->AddGo(new Coin());
	coin1->SetPosition(200.f, 0.f);
	coin1->SetCookie(cookie);
	coin1->sortLayer = 5;
	coin1->SetScene(scene);
	coin1->SetMap(this);
	coin1->SetType(CoinTypes::Coin);

}

void Map::Update(float dt)
{
	if (itemSpeedUp1->IsColPlayer() && !isSpeedUp)
	{
		AddSpeedUp();
		isSpeedUp = true;
		speedUpTimer = 0.f;
		cookie->GetPosition();
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

	BackgroundMove(dt);
	PlatformMove(dt);
}

void Map::Draw(sf::RenderWindow& window)
{
	//window.draw();
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

void Map::PlatformMove(float dt)
{
	float movePos1 = pf1->GetPosition().x;
	movePos1 += -pfSpeed * dt;
	pf1->SetPosition(movePos1, pf1->GetPosition().y);

	float movePos2 = pf2->GetPosition().x;
	movePos2 += -pfSpeed * dt;
	pf2->SetPosition(movePos2, pf2->GetPosition().y);	
	
	float movePos3 = ground1->GetPosition().x;
	movePos3 += -pfSpeed * dt;
	ground1->SetPosition(movePos3, ground1->GetPosition().y);

	float movePos4 = ground2->GetPosition().x;
	movePos4 += -pfSpeed * dt;
	ground2->SetPosition(movePos4, ground2->GetPosition().y);


	float movePos5 = itemSpeedUp1->GetPosition().x;
	movePos5 += -pfSpeed * dt;
	itemSpeedUp1->SetPosition(movePos5, itemSpeedUp1->GetPosition().y);
	
	float movePos6 = coin1->GetPosition().x;
	movePos6 += -pfSpeed * dt;
	coin1->SetPosition(movePos6, coin1->GetPosition().y);

	if (pf1->GetPosition().x < -1500.f)
		pf1->SetPosition(1700.f, pf1->GetPosition().y);
	if (pf2->GetPosition().x < -1500.f)
		pf2->SetPosition(1700.f, pf2->GetPosition().y);

	if (ground1->GetPosition().x < -1500.f)
		ground1->SetPosition(1700.f, ground1->GetPosition().y);

	if (ground2->GetPosition().x < -1500.f)
		ground2->SetPosition(1700.f, ground2->GetPosition().y);
	
	if (itemSpeedUp1->GetPosition().x < -1500.f)
		itemSpeedUp1->SetPosition(1700.f, itemSpeedUp1->GetPosition().y);

	if (coin1->GetPosition().x < -1500.f)
		coin1->SetPosition(1700.f, coin1->GetPosition().y);

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
