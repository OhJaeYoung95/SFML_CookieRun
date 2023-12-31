#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneTitle.h"
#include "SceneLobby.h"
#include "SceneGame.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "PatternEditor.h"

void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		Release();
	}
	scenes.push_back(new SceneTitle());
	scenes.push_back(new PatternEditor());
	scenes.push_back(new SceneLobby());
	scenes.push_back(new SceneGame());

	for (auto scene : scenes)
	{
		scene->Init();
	}

	// Ÿ��
	//SceneLobby* sceneLobby = dynamic_cast<SceneLobby*>(scenes[(int)SceneId::Lobby]);
	//sceneLobby->LobbyHi();

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();


}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		//scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::UpdateEvent(float dt)
{
	currentScene->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentScene->Draw(window);
}

void SceneMgr::ChangeScene(SceneId id)
{
	currentScene->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

Scene* SceneMgr::GetCurrScene() const
{
	return currentScene;
}
