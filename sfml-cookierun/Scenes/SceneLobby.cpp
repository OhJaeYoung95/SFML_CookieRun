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
#include "SpriteGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"
#include "StorageBox.h"
#include "InputMgr.h"

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


	float offsetCoinUI = 25.f;

	// 코인 정보
	currentCoin = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/CoinIcon.png"));
	currentCoin->SetPosition(windowSize.x * 0.68f + offsetCoinUI, 40.f);
	currentCoin->sprite.setScale(1.3f, 1.28f);
	currentCoin->SetOrigin(Origins::MC);
	currentCoin->sortLayer = 103;

	coinBg = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/PlayButton.png"));
	coinBg->SetPosition(windowSize.x * 0.68f + offsetCoinUI, 40.f);
	coinBg->sprite.setScale(1.6f, 1.3f);
	coinBg->sprite.setColor(sf::Color::Color(0, 0, 0, 180));
	coinBg->SetOrigin(Origins::ML);
	coinBg->sortLayer = 102;

	coinText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	coinText->SetPosition({ windowSize.x * 0.78f - 6.f, 35.f });
	coinText->text.setCharacterSize(26);
	coinText->text.setFillColor(sf::Color::White);
	coinText->text.setOutlineThickness(3);
	coinText->text.setOutlineColor(sf::Color::Black);
	coinText->SetOrigin(Origins::MR);
	coinText->sortLayer = 102;

	// 다이아 정보
	currentDia = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/DiamondIcon.png"));
	currentDia->SetPosition(windowSize.x * 0.58f, 40.f);
	currentDia->sprite.setScale(1.3f, 1.3f);
	currentDia->SetOrigin(Origins::MC);
	currentDia->sortLayer = 103;

	diaBg = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/PlayButton.png"));
	diaBg->SetPosition(windowSize.x * 0.575f, 40.f);
	diaBg->sprite.setScale(1.6f, 1.3f);
	diaBg->sprite.setColor(sf::Color::Color(0, 0, 0, 180));
	diaBg->SetOrigin(Origins::ML);
	diaBg->sortLayer = 102;

	diaText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	diaText->SetPosition({ windowSize.x * 0.65f + 17.f, 35.f });
	diaText->text.setCharacterSize(26);
	diaText->text.setFillColor(sf::Color::White);
	diaText->text.setOutlineThickness(3);
	diaText->text.setOutlineColor(sf::Color::Black);
	diaText->SetOrigin(Origins::MR);
	diaText->sortLayer = 102;



	// PLAY!버튼
	playButton = (UIButton*)AddGo(new UIButton("graphics/Lobby/PlayButton.png"));
	playButton->SetPosition(windowSize.x - 80.f, windowSize.y - 20.f);
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

		isEnterPlay = true;
	};
	playButton->OnClicking = [this]() {
		playButton->sprite.setColor(sf::Color::Color(255, 170, 0, 180));
		playText->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
		playText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	};

	// 내쿠키들 버튼
	cookieStorageBox = (UIButton*)AddGo(new UIButton("graphics/Lobby/Button.png"));
	cookieStorageBox->SetPosition(100.f, windowSize.y - 35.f);
	cookieStorageBox->sprite.setScale(4.7f, 3.5f);
	cookieStorageBox->SetOrigin(Origins::BL);
	cookieStorageBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
	cookieStorageBox->sortLayer = 101;

	storageImage = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/CookieStorageBox/StorageIcon.png"));
	storageImage->SetPosition(180.f, windowSize.y - 115.f);
	storageImage->SetOrigin(Origins::MC);
	storageImage->sortLayer = 102;

	storageText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	storageText->SetPosition(335.f, windowSize.y - 115.f);
	storageText->text.setString(stringTable->GetUni("STORAGE", Languages::KOR));
	storageText->text.setCharacterSize(45);
	storageText->text.setFillColor(sf::Color::White);
	storageText->text.setOutlineThickness(4);
	storageText->text.setOutlineColor(sf::Color::Black);
	storageText->SetOrigin(Origins::MC);
	storageText->sortLayer = 102;


	auto ptr2 = cookieStorageBox;
	cookieStorageBox->OnEnter = [ptr2]() {

	};
	cookieStorageBox->OnExit = [this]() {
		cookieStorageBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
		storageImage->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		storageText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		storageText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	};
	cookieStorageBox->OnClick = [this]() {
		//scene->IsChangeTitle(true);
		//AllSetActive(false);
		//this->SetActive(false);
		// 활성화

		cookieStorageBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
		storageImage->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		storageText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		storageText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
		storageUI->AllSetActive(true);
		storageUI->SetActive(true);
	};
	cookieStorageBox->OnClicking = [this]() {
		cookieStorageBox->sprite.setColor(sf::Color::Color(100, 200, 100, 180));
		storageImage->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		storageText->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
		storageText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	};

	// 스킨 버튼
	cookieSkinBox = (UIButton*)AddGo(new UIButton("graphics/Lobby/Button.png"));
	cookieSkinBox->SetPosition(470.f, windowSize.y - 35.f);
	cookieSkinBox->sprite.setScale(2.8f, 3.5f);
	cookieSkinBox->SetOrigin(Origins::BL);
	cookieSkinBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
	cookieSkinBox->sortLayer = 101;

	skinImage = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/CookieSkinBox/SkinIcon2.png"));
	skinImage->SetPosition(520.f, windowSize.y - 115.f);
	skinImage->sprite.setScale(1.3f, 1.3f);
	skinImage->SetOrigin(Origins::MC);
	skinImage->sortLayer = 102;

	skinText = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	skinText->SetPosition(610.f, windowSize.y - 115.f);
	skinText->text.setString(stringTable->GetUni("SKIN", Languages::KOR));
	skinText->text.setCharacterSize(45);
	skinText->text.setFillColor(sf::Color::White);
	skinText->text.setOutlineThickness(4);
	skinText->text.setOutlineColor(sf::Color::Black);
	skinText->SetOrigin(Origins::MC);
	skinText->sortLayer = 102;


	auto ptr3 = cookieSkinBox;
	cookieSkinBox->OnEnter = [ptr3]() {

	};
	cookieSkinBox->OnExit = [this]() {
		cookieSkinBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
		skinImage->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		skinText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		skinText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	};
	cookieSkinBox->OnClick = [this]() {
		//scene->IsChangeTitle(true);
		//AllSetActive(false);
		//this->SetActive(false);
		cookieSkinBox->sprite.setColor(sf::Color::Color(100, 200, 100, 255));
		skinImage->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		skinText->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		skinText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));

		// 씬 변환 변수
		isEnterPlay = true;
	};
	cookieSkinBox->OnClicking = [this]() {
		cookieSkinBox->sprite.setColor(sf::Color::Color(100, 200, 100, 180));
		skinImage->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		skinText->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
		skinText->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	};

	storageUI = (StorageBox*)AddGo(new StorageBox());
	storageUI->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
	storageUI->SetScene(this);
	storageUI->sortLayer = 102;


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
	Scene::Enter();
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	// Scene::Enter(); 맨 밑이였음
	storageUI->SetActive(false);
	isEnterPlay = false;
}

void SceneLobby::Exit()
{
	//isEnterPlay = false;
	Scene::Exit();
}

void SceneLobby::Update(float dt)
{
	Scene::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter) && storageUI->GetActive())
	{
		storageUI->AllSetActive(false);
		storageUI->SetActive(false);
	}

	std::stringstream coinS;
	coinS << Variables::coin;
	coinText->text.setString(coinS.str());
	coinText->SetOrigin(Origins::MR);

	std::stringstream diaS;
	diaS << Variables::diamond;
	diaText->text.setString(diaS.str());
	diaText->SetOrigin(Origins::MR);

	if(isEnterPlay)
		SCENE_MGR.ChangeScene(SceneId::Game);
}

void SceneLobby::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
