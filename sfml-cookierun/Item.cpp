#include "stdafx.h"
#include "Item.h"
#include "Cookie.h"
#include "Scene.h"
#include "SceneGame.h"

Item::Item(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n), cookie(nullptr)
{
}

Item::~Item()
{
}

void Item::Init()
{
	SpriteGo::Init();
	isUsed = false;
}

void Item::Release()
{
	SpriteGo::Release();

}

void Item::Reset()
{
	SpriteGo::Reset();
}

void Item::Update(float dt)
{
	SpriteGo::Update(dt);
	if (IsColPlayer()/* && !isUsed*/)
	{
		//isUsed = true;
		this->SetActive(false);
		scene->RemoveGo(this);
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

void Item::SetCookie(Cookie*& cookie)
{
	this->cookie = cookie;
}

bool Item::IsColPlayer()
{
	return sprite.getGlobalBounds().intersects(cookie->rect.getGlobalBounds());
}

void Item::SetScene(SceneGame* scene)
{
	this->scene = scene;
}

void Item::SetMap(Map* map)
{
	this->map = map;
}
