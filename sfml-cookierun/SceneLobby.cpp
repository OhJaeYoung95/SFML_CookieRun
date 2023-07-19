#include "stdafx.h"
#include "SceneLobby.h"
#include "GameObject.h"
#include "Lobby.h"

SceneLobby::SceneLobby()
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneLobby::Init()
{
	Release();

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneLobby::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneLobby::Enter()
{
	lobby = (Lobby*)AddGo(new Lobby());
	lobby->SetType(LobbyType::Temple);

	Scene::Enter();
}

void SceneLobby::Exit()
{
	Scene::Exit();

}

void SceneLobby::Update(float dt)
{
	Scene::Update(dt);
}

void SceneLobby::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
