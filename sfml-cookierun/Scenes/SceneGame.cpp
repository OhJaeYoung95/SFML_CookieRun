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
#include "Pirate.h"
#include "Moonlighter.h"
#include "Map.h"
#include "UIHp.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "Pause.h"
#include "SceneLobby.h"

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

	// 쿠키 생성
	pancake = (Pancake*)AddGo(new Pancake());
	pancake->SetType(CookieTypes::Pancake);
	pancake->SetScene(this);

	pirate = (Pirate*)AddGo(new Pirate());
	pirate->SetType(CookieTypes::Pirate);
	pirate->SetScene(this);

	moonlighter = (Moonlighter*)AddGo(new Moonlighter());
	moonlighter->SetType(CookieTypes::Moonlighter);
	moonlighter->SetScene(this);

	map = (Map*)AddGo(new Map());
	map->SetScene(this);
	hpUI = (UIHp*)AddGo(new UIHp("graphics/UI/HpBar/Hp.png"));

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
	scoreText->SetOrigin(Origins::TR);
	scoreText->sortLayer = 102;

	// UI
	jumpUpUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/JumpUp.png"));
	jumpUpUI->SetPosition(size.x * 0.02f, size.y * 0.92f);
	jumpUpUI->sprite.setScale(1.2f, 1.2f);
	jumpUpUI->SetOrigin(Origins::BL);
	jumpUpUI->sortLayer = 102;
	jumpUpUI->sortOrder = 1;

	jumpDownUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/JumpDown.png"));
	jumpDownUI->SetPosition(size.x * 0.02f, size.y * 0.92f);
	jumpDownUI->sprite.setScale(1.2f, 1.2f);
	jumpDownUI->SetOrigin(Origins::BL);
	jumpDownUI->sortLayer = 102;
	jumpDownUI->sortOrder = 2;
	JumpUIDown(false);

	slideUpUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/SlideUp.png"));
	slideUpUI->SetPosition(size.x * 0.98f, size.y * 0.92f);
	slideUpUI->sprite.setScale(1.2f, 1.2f);
	slideUpUI->SetOrigin(Origins::BR);
	slideUpUI->sortLayer = 102;
	slideUpUI->sortOrder = 1;
	
	slideDownUI = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/SlideDown.png"));
	slideDownUI->SetPosition(size.x * 0.98f, size.y * 0.92f);
	slideDownUI->sprite.setScale(1.2f, 1.2f);
	slideDownUI->SetOrigin(Origins::BR);
	slideDownUI->sortLayer = 102;
	slideDownUI->sortOrder = 2;
	SlideUIDown(false);

	pauseUIButton = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/Pause.png"));
	pauseUIButton->SetPosition(size.x * 0.97f, 50.f);
	pauseUIButton->sprite.setScale(1.2f, 1.2f);
	pauseUIButton->SetOrigin(Origins::MC);
	pauseUIButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	pauseUIButton->sortLayer = 102;


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

	// Effect
	hitEffect = (SpriteGo*)AddGo(new SpriteGo("graphics/UI/InGame/HitEffect2.png"));
	hitEffect->SetPosition(0, size.y);
	hitEffect->sprite.setScale(1.f, 1.f);
	hitEffect->sprite.setColor(sf::Color::Color(255.f, 255.f, 255.f, 200.f));
	hitEffect->SetOrigin(Origins::BL);
	hitEffect->sortLayer = 102;
	hitEffect->SetActive(false);

	pauseUI = (Pause*)AddGo(new Pause());
	pauseUI->SetPosition(size.x * 0.5f, size.y * 0.5f);
	pauseUI->SetScene(this);
	pauseUI->sortLayer = 102;


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

	isPlaying = true;
	currentCookieType = Variables::CurrentCookieType;


	// 캐릭터 바꾸고 SetScene에서 죽음
	// Init()부분에서 캐릭터 생성할떄 문제가 있는거 같다.

	switch (currentCookieType)
	{
	case CookieTypes::Pancake:
	{
		pancake->SetMap(map);
		pancake->SetPosition(-500.f, FRAMEWORK.GetWindowSize().y * 0.5f - 250.f);
		Cookie* cookie = dynamic_cast<Cookie*>(pancake);
		map->SetCookie(cookie);
		hpUI->SetCookie(cookie);
	}
		break;

	case CookieTypes::Pirate:
	{
		pirate->SetMap(map);
		pirate->SetPosition(-500.f, FRAMEWORK.GetWindowSize().y * 0.5f - 250.f);
		Cookie* cookie = dynamic_cast<Cookie*>(pirate);
		map->SetCookie(cookie);
		hpUI->SetCookie(cookie);
	}
		break;

	case CookieTypes::Moonlighter:
	{
		moonlighter->SetMap(map);
		moonlighter->SetPosition(-500.f, FRAMEWORK.GetWindowSize().y * 0.5f - 250.f);
		Cookie* cookie = dynamic_cast<Cookie*>(moonlighter);
		map->SetCookie(cookie);
		hpUI->SetCookie(cookie);
	}
		break;
	}



	coin = 0;
	score = 0;
	diamond = 0;

	pauseUIButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	pauseUI->SetActive(false);
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (INPUT_MGR.GetKey(sf::Keyboard::P))
	{
		pauseUIButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::P))
	{
		pauseUIButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		pauseUI->AllSetActive(true);
		pauseUI->SetActive(true);
		isPlaying = false;
	}

	Scene::Update(dt);	

	//std::cout << pancake->GetPosition().y << std::endl;

	if(jumpDownUI->GetActive())
		jumpUIDownTimer += dt;
	if (jumpUIDownTimer > jumpUIDownDuration)
	{
		JumpUIDown(false);
		jumpUIDownTimer = 0.f;
	}


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		hitEffect->SetActive(true);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		hitEffect->SetActive(false);
	}

	switch (currentCookieType)
	{
	case CookieTypes::Pancake:
		if (pancake->GetIsHit())
		{
			hitEffect->SetActive(true);
		}
		if (!pancake->GetIsHit())
		{
			hitEffect->SetActive(false);
		}

		break;
	case CookieTypes::Pirate:
		if (pirate->GetIsHit())
		{
			hitEffect->SetActive(true);
		}
		if (!pirate->GetIsHit())
		{
			hitEffect->SetActive(false);
		}

		break;
	case CookieTypes::Moonlighter:
		if (moonlighter->GetIsHit())
		{
			hitEffect->SetActive(true);
		}
		if (!moonlighter->GetIsHit())
		{
			hitEffect->SetActive(false);
		}

		break;
	}

	std::stringstream coinS;
	coinS << coin;
	coinText->text.setString(coinS.str());
	
	std::stringstream scoreS;
	scoreS << score;
	scoreText->text.setString(scoreS.str());
	scoreText->SetOrigin(Origins::TR);
	scoreJellyUI->SetPosition(scoreText->text.getGlobalBounds().left - 40.f, 25.f);

	if (isChange)
	{
		isChange = false;
		SCENE_MGR.ChangeScene(SceneId::Lobby);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::JumpUIDown(bool isActive)
{
	jumpDownUI->SetActive(isActive);
}

void SceneGame::SlideUIDown(bool isActive)
{
	slideDownUI->SetActive(isActive);
}
