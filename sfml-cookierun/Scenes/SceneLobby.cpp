#include "stdafx.h"
#include "SceneLobby.h"
#include "SceneGame.h"
#include "GameObject.h"
#include "Lobby.h"
#include "Framework.h"
#include "UIButton.h"
#include "SceneMgr.h"
#include "LobbyCookie.h"
#include "TextGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"

SceneLobby::SceneLobby() : Scene(SceneId::Lobby)
{
	resourceListPath = "scripts/SceneLobbyResourceList.csv";
}

void SceneLobby::Init()
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	// Enter에 하면 매 순간 로비가 Temple로 설정되는거 생각 currentType(?) 생각

	// Type에 따른 쿠키 애니메이션 변화 필요
	// 랜덤값에 따른 (enum형으로) 애니메이션 행동 패턴 변화
	cookie = (LobbyCookie*)AddGo(new LobbyCookie());
	cookie->SetOrigin(Origins::MC);
	cookie->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.6f);

	lobby = (Lobby*)AddGo(new Lobby());
	lobby->SetType(LobbyType::Temple);
	lobby->SetPosition(windowSize * 0.5f);

	// 그만하기
	playButton = (UIButton*)AddGo(new UIButton("graphics/Lobby/PlayButton.png"));
	playButton->SetPosition(windowSize.x - 80.f , windowSize.y - 20.f);
	playButton->sprite.setScale(3.7f, 5.0f);
	playButton->SetOrigin(Origins::BR);
	playButton->sprite.setColor(sf::Color::Color(255, 170, 0, 255));
	playButton->sortLayer = 101;

	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	playText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	playText->SetPosition(windowSize.x - 280.f, windowSize.y - 120.f);
	playText->text.setString("PLAY!");
	playText->text.setCharacterSize(60);
	playText->text.setFillColor(sf::Color::White);
	playText->text.setOutlineThickness(4);
	playText->text.setOutlineColor(sf::Color::Black);
	playText->SetOrigin(Origins::MC);
	playText->sortLayer = 102;


	auto ptr1 = playButton;
	playButton->OnEnter = [ptr1]() {

	};
	playButton->OnExit = [this]() {
		playButton->sprite.setColor(sf::Color::Color(255, 170, 0, 255));
		playText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		playText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	};
	playButton->OnClick = [this]() {
		//scene->IsChangeTitle(true);
		//AllSetActive(false);
		//this->SetActive(false);
		playButton->sprite.setColor(sf::Color::Color(255, 170, 0, 255));
		playText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		playText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		SCENE_MGR.ChangeScene(SceneId::Game);
	};
	playButton->OnClicking = [this]() {
		playButton->sprite.setColor(sf::Color::Color(255, 170, 0, 180));
		playText->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
		playText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	};

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
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);


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
