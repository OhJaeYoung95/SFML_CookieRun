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
	type = Variables::CurrentCookieType;
}

void LobbyCookie::Release()
{
	SpriteGo::Release();

}

void LobbyCookie::Reset()
{
	SpriteGo::Reset();
	type = Variables::CurrentCookieType;
	animation.ResetClip();

	switch(type)
	{
	case CookieTypes::Pancake:

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Happy.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Sad.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pancake/Turn.csv"));
		animation.SetTarget(&sprite);
		{
			int ranAnim = Utils::RandomRange(0, 3);
			switch (ranAnim)
			{
			case 0:
				animation.Play("Happy");
				break;
			case 1:
				animation.Play("Sad");
				break;
			case 2:
				animation.Play("Turn");
				break;
			}
		}

		break;
	case CookieTypes::Pirate:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pirate/Happy.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pirate/Sad.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Pirate/Turn.csv"));
		animation.SetTarget(&sprite);
		{
			int ranAnim = Utils::RandomRange(0, 3);
			switch (ranAnim)
			{
			case 0:
				animation.Play("Happy");
				break;
			case 1:
				animation.Play("Sad");
				break;
			case 2:
				animation.Play("Turn");
				break;
			}
		}

		break;
	case CookieTypes::Moonlighter:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Moonlighter/Moon.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Moonlighter/Turn.csv"));
		animation.SetTarget(&sprite);
		{
			int ranAnim = Utils::RandomRange(0, 2);
			switch (ranAnim)
			{
			case 0:
				animation.Play("Turn");
				break;
			case 1:
				animation.Play("Moon");
				break;
			case 2:
				break;
			}
		}
		break;
	}

	SetOrigin(Origins::MC);
	sortLayer = 110;
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
