#include "stdafx.h"
#include "Item.h"
#include "Cookie.h"

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

}

void Item::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

bool Item::IsColPlayer()
{
	return sprite.getGlobalBounds().intersects(cookie->sprite.getGlobalBounds());
}
