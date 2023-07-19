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
		animation.Play("Temple");
		break;
	case LobbyType::WizardryTower:
		animation.Play("WizardryTower");
		break;
	case LobbyType::Cathedral:
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
}

void Lobby::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
