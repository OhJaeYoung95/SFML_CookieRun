#include "stdafx.h"
#include "Platform.h"
#include "Cookie.h"

Platform::Platform(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Platform::~Platform()
{
}

void Platform::Init()
{
	SpriteGo::Init();
}

void Platform::Release()
{
	SpriteGo::Release();
}

void Platform::Reset()
{
	SpriteGo::Reset();
	SetPosition(GetPosition());
	SetOrigin(Origins::MC);
}

void Platform::Update(float dt)
{
	SpriteGo::Update(dt);
	ColCookie();
}

void Platform::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Platform::SetCookie(Cookie*& cookie)
{
	this->cookie = cookie;
}

void Platform::ColCookie()
{
	sf::FloatRect compare;
	bool isCol = sprite.getGlobalBounds().intersects(cookie->rect.getGlobalBounds(), compare);
	if (isCol)
	{
  		//std::cout << compare.top << std::endl;
  		//std::cout << cookie->rect.getGlobalBounds().top << std::endl;
   	//	std::cout << sprite.getGlobalBounds().top + sprite.getGlobalBounds().height << std::endl;

		// Á¶°Ç Ãß°¡ÇØ¾ßÇÔ ÄíÅ°ÀÇ ¾Æ·§¸é°ú, ÇÃ·§ÆûÀÇ À­¸é °Ë»ç ÇØ¾ßÇÔ
		if (compare.top > cookie->rect.getGlobalBounds().top && cookie->GetVelocity() > 0)
		{
			cookie->SetIsDouble(false);
			cookie->SetJumpCount();
			cookie->SetIsGround(true);
			cookie->SetPosition(cookie->GetPosition().x, sprite.getGlobalBounds().top);
			cookie->SetGravity();
		}
	}
}
