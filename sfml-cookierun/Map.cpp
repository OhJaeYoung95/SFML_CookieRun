#include "stdafx.h"
#include "Map.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Background.h"
#include "Platform.h"

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
	bg1->sprite.setScale(3.001f, 3.0f);
	bg1->sortLayer = 0;

	bg2->SetPosition(0.f, 0.f);
	bg2->sprite.setScale(3.02f, 3.f);
	bg2->sortLayer = -1;

	bg3 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background1.png"));
	bg4 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background2.png"));
	bg3->SetPosition(2400.f, 0.f);
	bg3->sprite.setScale(3.001f, 3.0f);
	bg3->sortLayer = 0;

	bg4->SetPosition(2400.f, 0.f);
	bg4->sprite.setScale(3.02f, 3.f);
	bg4->sortLayer = -1;

	// 발판
	pf1 = (Platform*)scene->AddGo(new Platform("graphics/Stage1/Platform.png"));
	pf1->SetPosition(300, 0);
	pf1->sortLayer = 1;

}
void Map::Release()
{

}

void Map::Reset()
{
	// 배경
	bg1->SetPosition(0.f, 0.f);
	bg2->SetPosition(0.f, 0.f);
	bg3->SetPosition(2400.f, 0.f);
	bg4->SetPosition(2400.f, 0.f);



}

void Map::Update(float dt)
{
	BackgroundMove(dt);
}

void Map::Draw(sf::RenderWindow& window)
{
	//window.draw();
}

void Map::SetScene(SceneGame* scene)
{
	this->scene = scene;
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
