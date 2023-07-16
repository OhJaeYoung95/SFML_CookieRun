#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "PlayerTest.h"
#include "Framework.h"
#include "UIButton.h"
#include "Pancake.h"
#include "Map.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/sprite_sheet.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button2.png"));

	// ¿¹Á¦
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();

	auto size = FRAMEWORK.GetWindowSize();

	pancake = (Pancake*)AddGo(new Pancake());
	//player = (Player*)AddGo(new Player());


	uiButton = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	uiButton->SetOrigin(Origins::TR);
	uiButton->sortLayer = 100;
	uiButton->SetPosition(size.x, 0.f);
	auto ptr = uiButton;
	uiButton->OnEnter = [ptr]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/button2.png");
		ptr->sprite.setTexture(*tex);
	};
	uiButton->OnExit = [ptr]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/button.png");
		ptr->sprite.setTexture(*tex);
	};
	uiButton->OnClick = [this]() {
		SCENE_MGR.ChangeScene(sceneId);
	};

	Cookie* cookie = dynamic_cast<Cookie*>(pancake);

	map = (Map*)AddGo(new Map());
	map->SetScene(this);
	map->SetCookie(cookie);

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);	

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
