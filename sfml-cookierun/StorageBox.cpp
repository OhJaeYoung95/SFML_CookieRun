#include "stdafx.h"
#include "StorageBox.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "UIButton.h"
#include "SceneLobby.h"
#include "TextGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"

StorageBox::StorageBox(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

StorageBox::~StorageBox()
{
}

void StorageBox::Init()
{
	SpriteGo::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSize();


	bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	bg.setSize({ 1920, 1080 });
	bg.setOrigin(0, 0);

	storageBoxBG = (SpriteGo*)scene->AddGo(new SpriteGo("graphics/Lobby/CookieStorageBox/StorageBoxBG.png"));
	storageBoxBG->SetPosition(size * 0.5f);
	storageBoxBG->SetOrigin(Origins::MC);
	storageBoxBG->sortLayer = 101;


	// 버튼과 Text 간격 설정 변수
	float buttonW = 1.0f;
	float buttonH = 1.0f;
	float offset = 100.f;
	float offsetCen = -50.f;

	// 팬케이크
	pancakeButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/CookieStorageBox/PancakeIcon.png"));
	pancakeButton->sprite.setScale(buttonW, buttonH);
	pancakeButton->SetOrigin(Origins::MC);
	pancakeButton->sortLayer = 102;
	pancakeButton->SetPosition(size.x * 0.3f, size.y * 0.38f);
	auto ptr1 = pancakeButton;

	//sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/button.png");
	//ptr1->sprite.setTexture(*tex);

	pancakeButton->OnEnter = [ptr1]() {
		// 이펙트 넣기 SetActive(true)
	};
	pancakeButton->OnExit = [this]() {
		// 이펙트 빼기 SetActive(false)
		pancakeButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	pancakeButton->OnClick = [this]() {
		pancakeButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		Variables::CurrentCookieType = CookieTypes::Pancake;
		SCENE_MGR.ChangeScene(SceneId::Lobby);
		AllSetActive(false);
		this->SetActive(false);

	};
	pancakeButton->OnClicking = [this]() {
		pancakeButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	// 해적
	pirateButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/CookieStorageBox/PirateIcon.png"));
	pirateButton->sprite.setScale(buttonW, buttonH);
	pirateButton->SetOrigin(Origins::MC);
	pirateButton->sortLayer = 102;
	pirateButton->SetPosition(size.x * 0.5f, size.y * 0.38f);

	auto ptr2 = pirateButton;
	pirateButton->OnEnter = [ptr2]() {
	};
	pirateButton->OnExit = [this]() {
		pirateButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	pirateButton->OnClick = [this]() {
		//scene->IsChangeTitle(true);
		pirateButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		Variables::CurrentCookieType = CookieTypes::Pirate;
		SCENE_MGR.ChangeScene(SceneId::Lobby);
		AllSetActive(false);
		this->SetActive(false);
	};
	pirateButton->OnClicking = [this]() {
		pirateButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	// 달빛술사
	moonlighterButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/CookieStorageBox/MoonlighterIcon.png"));
	moonlighterButton->sprite.setScale(buttonW, buttonH);
	moonlighterButton->SetOrigin(Origins::MC);
	moonlighterButton->sortLayer = 102;
	moonlighterButton->SetPosition(size.x * 0.7f, size.y * 0.38f);
	auto ptr3 = moonlighterButton;
	moonlighterButton->OnEnter = [ptr3]() {
	};
	moonlighterButton->OnExit = [this]() {
		moonlighterButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	moonlighterButton->OnClick = [this]() {
		moonlighterButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		Variables::CurrentCookieType = CookieTypes::Moonlighter;
		SCENE_MGR.ChangeScene(SceneId::Lobby);
		AllSetActive(false);
		this->SetActive(false);
	};
	moonlighterButton->OnClicking = [this]() {
		moonlighterButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	//pauseText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	//pauseText->SetPosition({ size.x * 0.5f, size.y * 0.33f + offsetCen });
	//pauseText->text.setString(stringTable->GetUni("PAUSE", Languages::KOR));
	//pauseText->text.setCharacterSize(60);
	//pauseText->text.setFillColor(sf::Color::Color(255, 165, 0, 255));
	//pauseText->text.setOutlineThickness(4);
	//pauseText->text.setOutlineColor(sf::Color::Black);
	//pauseText->SetOrigin(Origins::MC);
	//pauseText->sortLayer = 102;


	// 버튼 잠금 텍스트
	pancakeLockText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	pancakeLockText->text.setScale(1.1f, 1.0f);
	pancakeLockText->SetPosition({ pancakeLockText->GetPosition().x, pancakeLockText->GetPosition().y - 10.f });
	pancakeLockText->text.setString(stringTable->GetUni("CONTINUE", Languages::KOR));
	pancakeLockText->text.setCharacterSize(45);
	pancakeLockText->text.setFillColor(sf::Color::Black);
	pancakeLockText->SetOrigin(Origins::MC);
	pancakeLockText->sortLayer = 102;

	pirateLockText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	pirateLockText->text.setScale(1.1f, 1.0f);
	pirateLockText->SetPosition({ pirateLockText->GetPosition().x, pirateLockText->GetPosition().y - 10.f });
	pirateLockText->text.setString(stringTable->GetUni("EXIT", Languages::KOR));
	pirateLockText->text.setCharacterSize(45);
	pirateLockText->text.setFillColor(sf::Color::Black);
	pirateLockText->SetOrigin(Origins::MC);
	pirateLockText->sortLayer = 102;

	moonlighterLockText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	moonlighterLockText->text.setScale(1.1f, 1.0f);
	moonlighterLockText->SetPosition({ moonlighterLockText->GetPosition().x, moonlighterLockText->GetPosition().y - 10.f });
	moonlighterLockText->text.setString(stringTable->GetUni("REDO", Languages::KOR));
	moonlighterLockText->text.setCharacterSize(45);
	moonlighterLockText->text.setFillColor(sf::Color::Black);
	moonlighterLockText->SetOrigin(Origins::MC);
	moonlighterLockText->sortLayer = 102;

	//scene->AddNPGo(continueButton);
	//scene->AddNPGo(exitButton);
	//scene->AddNPGo(redoButton);
	AllSetActive(false);
}

void StorageBox::Release()
{
	SpriteGo::Release();
}

void StorageBox::Reset()
{
	SpriteGo::Reset();
}

void StorageBox::Update(float dt)
{
	SpriteGo::Update(dt);

}

void StorageBox::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(bg);
}

void StorageBox::AllSetActive(bool isActive)
{
	//bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	pancakeButton->SetActive(isActive);
	pirateButton->SetActive(isActive);
	moonlighterButton->SetActive(isActive);
	//pauseText->SetActive(isActive);
	pancakeLockText->SetActive(isActive);
	pirateLockText->SetActive(isActive);
	moonlighterLockText->SetActive(isActive);
	storageBoxBG->SetActive(isActive);

}
