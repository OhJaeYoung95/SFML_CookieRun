#include "stdafx.h"
#include "Platform.h"

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
	SetOrigin(Origins::MC);
}

void Platform::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Platform::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
