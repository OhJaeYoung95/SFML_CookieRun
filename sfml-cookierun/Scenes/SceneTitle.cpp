#include "stdafx.h"
#include "SceneTitle.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "StringTable.h"
#include "DataTableMgr.h"


SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	resourceListPath = "scripts/SceneTitleResourceList.csv";
}

void SceneTitle::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	bg = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/Title.png"));
	bg->SetPosition(windowSize * 0.5f);
	bg->sprite.setScale(0.48f, 0.52f);
	bg->SetOrigin(Origins::MC);
	bg->sortLayer = 100;

	//frame = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/Frame1.png"));
	//frame = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/Frame2.png"));
	frame = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/Frame3.png"));
	//frame->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.61f);
	frame->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.575f);
	//frame->sprite.setScale(0.38f, 0.16f);
	//frame->sprite.setScale(1.4f, 1.8f);
	frame->sprite.setScale(0.45f, 0.55f);
	frame->SetOrigin(Origins::MC);
	frame->sortLayer = 100;


	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	// 노랑색 (R: 255, G: 255, B: 0)
	sf::Color yellow(255, 255, 0);

	// 주황색 (R: 255, G: 165, B: 0)
	sf::Color orange(255, 165, 0);

	title1 = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	title1->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.6f});
	title1->text.setCharacterSize(60);
	title1->text.setString(stringTable->GetUni("TITLE1", Languages::KOR));
	//title1->text.setFillColor(sf::Color::Color(255, 255, 0, 255));
	title1->text.setFillColor(sf::Color::Color(255, 165, 0, 255));
	title1->text.setOutlineThickness(4);
	//title1->text.setOutlineColor(sf::Color::Color(255, 165, 0, 255));
	title1->text.setOutlineColor(sf::Color::Color(255, 255, 0, 255));
	title1->SetOrigin(Origins::MC);
	title1->sortLayer = 102;	
	
	title2 = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	title2->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.69f});
	title2->text.setCharacterSize(80);
	title2->text.setString(stringTable->GetUni("TITLE2", Languages::KOR));
	//title1->text.setFillColor(sf::Color::Color(255, 255, 0, 255));
	title2->text.setFillColor(sf::Color::Color(255, 165, 0, 255));
	title2->text.setOutlineThickness(4);
	//title1->text.setOutlineColor(sf::Color::Color(255, 165, 0, 255));
	title2->text.setOutlineColor(sf::Color::Color(255, 255, 0, 255));
	title2->SetOrigin(Origins::MC);
	title2->sortLayer = 102;

	info = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	info->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.8f});
	info->text.setCharacterSize(80);
	info->text.setString("Press Enter To Start Game");
	info->text.setFillColor(sf::Color::White);
	info->text.setOutlineThickness(5);
	info->text.setOutlineColor(sf::Color::Black);
	info->SetOrigin(Origins::MC);
	info->sortLayer = 102;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{

	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();

}

void SceneTitle::Exit()
{
	Scene::Exit();

}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}	
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}

	Blink(info);
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	//	info->SetActive(false);
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	//	info->SetActive(true);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
