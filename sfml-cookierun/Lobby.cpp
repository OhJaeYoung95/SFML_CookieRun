#include "stdafx.h"
#include "Lobby.h"
#include "ResourceMgr.h"

Lobby::Lobby(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Lobby::~Lobby()
{
}

void Lobby::Init()
{
	SpriteGo::Init();
	sortLayer = 100;
	switch (type)
	{
	case LobbyType::Temple:
		break;
	case LobbyType::WizardryTower:
		break;
	case LobbyType::Cathedral:
		break;
	}

}

void Lobby::Release()
{
	SpriteGo::Release();

}

void Lobby::Reset()
{
	SpriteGo::Reset();
	switch (type)
	{
	case LobbyType::Temple:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Lobby1/Lobby1.csv"));
		animationEffect1.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Lobby1/LobbyEffect1.csv"));
		sprite.setScale(2.8f, 2.7f);
		animSprite1.setScale(1.4f, 1.35f);
		animSprite1.setColor(sf::Color::Color(255,255,255,180));
		animation.SetTarget(&sprite);
		animationEffect1.SetTarget(&animSprite1);
		SetOrigin(Origins::MC);

		animation.Play("Temple");
		animationEffect1.Play("LobbyEffect1");
		break;
	case LobbyType::WizardryTower:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Lobby2/Lobby2.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		animation.Play("WizardryTower");
		break;
	case LobbyType::Cathedral:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Lobby/Lobby3/Lobby3.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::MC);
		animation.Play("Cathedral");
		break;
	}	

}

void Lobby::Update(float dt)
{
	SpriteGo::Update(dt);
	//switch (type)
	//{
	//case LobbyType::Temple:
	//	break;
	//case LobbyType::WizardryTower:
	//	break;
	//case LobbyType::Cathedral:
	//	break;
	//}
	animation.Update(dt);
	animationEffect1.Update(dt);
	SetOrigin(Origins::MC);
}

void Lobby::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
