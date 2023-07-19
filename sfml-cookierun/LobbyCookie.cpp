#include "stdafx.h"
#include "LobbyCookie.h"
#include "ResourceMgr.h"

LobbyCookie::LobbyCookie(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

LobbyCookie::~LobbyCookie()
{
}

void LobbyCookie::Init()
{
	SpriteGo::Init();

}

void LobbyCookie::Release()
{
	SpriteGo::Release();

}

void LobbyCookie::Reset()
{
	SpriteGo::Reset();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Happy.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Sad.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Turn.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sortLayer = 110;
	animation.Play("Turn");
}

void LobbyCookie::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);
	SetOrigin(Origins::MC);
}

void LobbyCookie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
