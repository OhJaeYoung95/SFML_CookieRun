#include "stdafx.h"
#include "LobbyCookie.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "InputMgr.h"

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
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

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
				SetPosition(880, 600);
				sprite.setScale(0.7f, 0.7f);
				break;
			case 1:
				animation.Play("Sad");
				SetPosition(880, 600);
				sprite.setScale(0.7f, 0.7f);

				break;
			case 2:
				animation.Play("Turn");
				SetPosition(800, 400);
				sprite.setScale(1.f, 1.f);

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
				SetPosition(880, 600);
				sprite.setScale(0.7f, 0.7f);
				break;
			case 1:
				animation.Play("Sad");
				SetPosition(880, 600);
				sprite.setScale(0.7f, 0.7f);
				break;
			case 2:
				animation.Play("Turn");
				SetPosition(800, 400);
				sprite.setScale(1.f, 1.f);
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
				SetPosition(800, 400);
				sprite.setScale(1.f, 1.f);
				break;
			case 1:
				animation.Play("Moon");
				SetPosition(800, 400);
				sprite.setScale(1.f, 1.f);
				break;
			case 2:
				break;
			}
		}
		break;
	}

	//SetOrigin(Origins::MC);
	sortLayer = 101;
}

void LobbyCookie::Update(float dt)
{
	SpriteGo::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		Reset();
	}
	animation.Update(dt);
}

void LobbyCookie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
