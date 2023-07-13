#include "stdafx.h"
#include "Map.h"
#include "Background.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneGame.h"

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
	bg1 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background1.png"));
	bg2 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background2.png"));
	bg1->sprite.setScale(3.0f, 3.f);
	bg1->sortLayer = 0;
	bg2->sprite.setScale(3.0f, 3.f);
	bg2->sortLayer = -1;

	bg3 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background1.png"));
	bg4 = (Background*)scene->AddGo(new Background("graphics/Stage1/Background2.png"));
	bg3->sprite.setScale(3.0f, 3.f);
	bg3->SetPosition(bg1->sprite.getScale().x + bg1->GetPosition().x, 0.f);
	bg3->sortLayer = 0;

	bg4->sprite.setScale(3.0f, 3.f);
	bg3->SetPosition(bg1->sprite.getScale().x + bg1->GetPosition().x, 0.f);
	bg4->sortLayer = -1;
}
void Map::Release()
{

}

void Map::Reset()
{


}

void Map::Update(float dt)
{
	float bgPosX = bg1->GetPosition().x;
	bgPosX += -bgSpeed * dt;
	bg1->SetPosition({ bgPosX,bg1->GetPosition().y});
	bg2->SetPosition({ bg1->GetPosition().x,bg1->GetPosition().y });
}

void Map::Draw(sf::RenderWindow& window)
{
	//window.draw();
}

void Map::SetScene(SceneGame* scene)
{
	this->scene = scene;
}
