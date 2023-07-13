#include "stdafx.h"
#include "Background.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

Background::Background(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{

}

Background::~Background()
{

}

void Background::Init()
{
	SpriteGo::Init();
	//SetPosition(0, 0);
	SetOrigin(Origins::MC);
}

void Background::Release()
{
	SpriteGo::Release();

}

void Background::Reset()
{
	SpriteGo::Reset();

}

void Background::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Background::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
