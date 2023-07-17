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
#include "UIHp.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/sprite_sheet.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button.png"));
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button2.png"));

	// 예제
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();
	auto size = FRAMEWORK.GetWindowSize();


	pancake = (Pancake*)AddGo(new Pancake());
	pancake->SetType(CookieTypes::Pancake);

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

	hpUI = (UIHp*)AddGo(new UIHp("graphics/UI/HpBar/Hp.png"));
	hpUI->SetCookie(cookie);

	// Text

	// Reset에서 SetOrigin()을 해줘야한다.
	coinText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	coinText->SetPosition({ size.x * 0.5f + 60.f, 20.f });
	coinText->text.setCharacterSize(50);
	coinText->text.setFillColor(sf::Color::White);
	coinText->text.setOutlineThickness(4);
	coinText->text.setOutlineColor(sf::Color::Black);
	coinText->SetOrigin(Origins::TL);
	coinText->sortLayer = 102;

	scoreText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	scoreText->SetPosition({ size.x * 0.92f, 20.f });
	scoreText->text.setCharacterSize(50);
	scoreText->text.setFillColor(sf::Color::White);
	scoreText->text.setOutlineThickness(4);
	scoreText->text.setOutlineColor(sf::Color::Black);
	scoreText->SetOrigin(Origins::TL);
	scoreText->sortLayer = 102;

	// UI
	scoreJellyUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/Score/ScoreJellyUI.png"));
	scoreCoinUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/Coin/ScoreCoinUI.png"));

	scoreJellyUI->SetOrigin(Origins::TC);
	//scoreJellyUI->SetPosition(size.x * 0.85f, 25.f);
	scoreJellyUI->SetPosition(scoreText->text.getGlobalBounds().left - 40.f, 25.f);
	scoreJellyUI->sprite.setScale(1.5f, 1.5f);
	scoreJellyUI->sortLayer = 102;

	scoreCoinUI->SetPosition(size.x * 0.5f, 25.f);
	scoreCoinUI->sprite.setScale(1.5f, 1.5f);
	scoreCoinUI->SetOrigin(Origins::TC);
	scoreCoinUI->sortLayer = 102;

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

	coin = 99;


	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);	

	std::stringstream coinS;
	coinS << coin;
	coinText->text.setString(coinS.str());

	std::stringstream scoreS;
	scoreS << score;
	scoreText->text.setString(scoreS.str());

	scoreJellyUI->SetPosition(scoreText->text.getGlobalBounds().left - 40.f, 25.f);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
