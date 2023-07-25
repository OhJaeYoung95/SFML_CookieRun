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
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();


	bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	bg.setSize({ 1920, 1080 });
	bg.setOrigin(0, 0);

	storageBoxBG = (SpriteGo*)scene->AddGo(new SpriteGo("graphics/Lobby/CookieStorageBox/StorageBoxBG.png"));
	storageBoxBG->SetPosition(windowSize * 0.5f);
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
	pancakeButton->SetPosition(windowSize.x * 0.3f, windowSize.y * 0.38f);
	pancakeButton->isLock = isPancakeLock;
	pancakeButton->cookieType = CookieTypes::Pancake;
	LockCookie(pancakeButton);
	SelectCookieButtonEvent(pancakeButton);


	// 해적
	pirateButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/CookieStorageBox/PirateIcon.png"));
	pirateButton->sprite.setScale(buttonW, buttonH);
	pirateButton->SetOrigin(Origins::MC);
	pirateButton->sortLayer = 102;
	pirateButton->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.38f);
	pirateButton->isLock = isPirateLock;
	pirateButton->price = 1000;
	pirateButton->cookieType = CookieTypes::Pirate;
	LockCookie(pirateButton);
	SelectCookieButtonEvent(pirateButton);

	// 달빛술사
	moonlighterButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/CookieStorageBox/MoonlighterIcon.png"));
	moonlighterButton->sprite.setScale(buttonW, buttonH);
	moonlighterButton->SetOrigin(Origins::MC);
	moonlighterButton->sortLayer = 102;
	moonlighterButton->SetPosition(windowSize.x * 0.7f, windowSize.y * 0.38f);
	moonlighterButton->isLock = isMoonlighterLock;
	moonlighterButton->price = 5000;
	moonlighterButton->cookieType = CookieTypes::Moonlighter;
	LockCookie(moonlighterButton);
	SelectCookieButtonEvent(moonlighterButton);

	// 로비
	templeButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/Lobby1/Lobby1.png"));
	templeButton->sprite.setScale(0.5f, 0.5f);
	templeButton->SetOrigin(Origins::MC);
	templeButton->sortLayer = 102;
	templeButton->SetPosition(windowSize.x * 0.3f, windowSize.y * 0.38f);
	templeButton->isLock = isTempleLock;
	templeButton->lobbyType = LobbyType::Temple;
	LockCookie(templeButton);
	// 수정 필요
	SelectLobbyButtonEvent(pancakeButton);

	wizardryTowerButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/Lobby2/Lobby1.png"));
	wizardryTowerButton->sprite.setScale(0.25f, 0.25f);
	wizardryTowerButton->SetOrigin(Origins::MC);
	wizardryTowerButton->sortLayer = 102;
	wizardryTowerButton->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.38f);
	wizardryTowerButton->isLock = isWizardryTowerLock;
	wizardryTowerButton->lobbyType = LobbyType::WizardryTower;
	LockCookie(wizardryTowerButton);
	// 수정 필요
	SelectLobbyButtonEvent(wizardryTowerButton);

	cathedralButton = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/Lobby3/Lobby1.png"));
	cathedralButton->sprite.setScale(0.25f, 0.28f);
	cathedralButton->SetOrigin(Origins::MC);
	cathedralButton->sortLayer = 102;
	cathedralButton->SetPosition(windowSize.x * 0.7f, windowSize.y * 0.38f);
	cathedralButton->isLock = isCathedralLock;
	cathedralButton->lobbyType = LobbyType::Cathedral;
	LockCookie(cathedralButton);
	// 수정 필요
	SelectLobbyButtonEvent(cathedralButton);



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
	piratePrice = (SpriteGo*)scene->AddGo(new SpriteGo("graphics/Lobby/CoinIcon.png"));
	piratePrice->SetPosition(windowSize.x * 0.5f - 100.f, windowSize.y * 0.38f);
	piratePrice->sprite.setScale(1.5f, 1.5f);
	piratePrice->SetOrigin(Origins::MC);
	piratePrice->sortLayer = 102;
	piratePrice->SetActive(false);

	moonlighterPrice = (SpriteGo*)scene->AddGo(new SpriteGo("graphics/Lobby/CoinIcon.png"));
	moonlighterPrice->SetPosition(windowSize.x * 0.7f - 100.f, windowSize.y * 0.38f);
	moonlighterPrice->sprite.setScale(1.5f, 1.5f);
	moonlighterPrice->SetOrigin(Origins::MC);
	moonlighterPrice->sortLayer = 102;
	moonlighterPrice->SetActive(false);

	piratePriceText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	piratePriceText->text.setString("1000");
	piratePriceText->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.38f);
	piratePriceText->SetOrigin(Origins::BC);
	piratePriceText->sortLayer = 102;
	piratePriceText->SetActive(false);

	moonlighterPriceText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	moonlighterPriceText->text.setString("5000");
	moonlighterPriceText->SetPosition(windowSize.x * 0.7f, windowSize.y * 0.38f);
	moonlighterPriceText->SetOrigin(Origins::BC);
	moonlighterPriceText->sortLayer = 102;
	moonlighterPriceText->SetActive(false);

	failedToBuy = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	failedToBuy->text.setString(stringTable->GetUni("FAILED_TO_BUY", Languages::KOR));
	failedToBuy->text.setCharacterSize(65);
	failedToBuy->text.setOutlineThickness(5);
	failedToBuy->text.setFillColor(sf::Color::Color(255, 255, 255, 0));
	failedToBuy->text.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
	failedToBuy->SetPosition(windowSize.x * 0.5f, windowSize.y * 0.7f);
	failedToBuy->SetOrigin(Origins::MC);
	failedToBuy->sortLayer = 102;


	sf::Vector2f btnSize = { 1.0f, 2.8f };
	sf::Vector2f startBtnPos = { windowSize.x * 0.18f, windowSize.y * 0.18f };

	selectCookieBtn = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/PlayButton.png"));
	selectCookieBtn->text.setString(stringTable->GetUni("COOKIE_STORAGE", Languages::KOR));
	ButtonInit(selectCookieBtn, startBtnPos, btnSize);
	selectCookieBtn->OnClick = [this]() {
		SelectCookieStorage();
	};

	selectSkinBtn = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/PlayButton.png"));
	selectSkinBtn->text.setString(stringTable->GetUni("SKIN_STORAGE", Languages::KOR));
	ButtonInit(selectSkinBtn, startBtnPos + sf::Vector2f(110.f, 0.f), btnSize);
	selectSkinBtn->OnClick = [this]() {
		SelectSkinStorage();
	};

	selectLobbyBtn = (UIButton*)scene->AddGo(new UIButton("graphics/Lobby/PlayButton.png"));
	selectLobbyBtn->text.setString(stringTable->GetUni("LOBBY_STORAGE", Languages::KOR));
	ButtonInit(selectLobbyBtn, startBtnPos + sf::Vector2f(265.f, 0.f), btnSize + sf::Vector2f(0.8f, 0.0f));
	selectLobbyBtn->OnClick = [this]() {
		SelectLobbyStorage();
	};

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
	
	if (isFailed)
	{
		fadeTimer += dt;
	}
	if (fadeTimer > fadeDuration)
	{
		fadeTimer = 0.f;
		isFailed = false;
	}

	if (isFailed)
	{
		UINT8 a = Utils::Lerp(255, 0, (fadeTimer / fadeDuration));
		failedToBuy->text.setFillColor({ 255, 255, 255, a });
		failedToBuy->text.setOutlineColor({ 0, 0, 0, a });
	}

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

	templeButton->SetActive(isActive);
	wizardryTowerButton->SetActive(isActive);
	cathedralButton->SetActive(isActive);


	storageBoxBG->SetActive(isActive);

	selectCookieBtn->SetActive(isActive);
	selectSkinBtn->SetActive(isActive);
	selectLobbyBtn->SetActive(isActive);
	failedToBuy->SetActive(isActive);
}

void StorageBox::SelectCookieButtonEvent(UIButton* cookie)
{
	cookie->OnEnter = []() {
		// 이펙트 넣기 SetActive(true)
	};
	cookie->OnExit = [this, cookie]() {
		// 이펙트 빼기 SetActive(false)
		if (!cookie->isLock)
		{
			cookie->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		}
	};
	cookie->OnClick = [this, cookie]() {
		if (!cookie->isLock)
		{
			cookie->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
			Variables::CurrentCookieType = cookie->cookieType;
			AllSetActive(false);
			this->SetActive(false);
			ReleaseCookieStorage();
			ReleaseSkinStorage();
			ReleaseLobbyStorage();
			SCENE_MGR.ChangeScene(SceneId::Lobby);

		}
		if(cookie->isLock)
		{
			std::cout << scene->GetCoin();
			if (scene->GetCoin() < cookie->price)
			{
				isFailed = true;
				failedToBuy->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
				failedToBuy->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
			}
			if(scene->GetCoin() >= cookie->price)
			{
				cookie->isLock = false;
				cookie->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
				Variables::coin -= cookie->price;
				scene->SetCoin(-cookie->price);

				if (cookie->cookieType == CookieTypes::Pirate)
				{
					isPirateLock = cookie->isLock;
					piratePrice->SetActive(false);
					piratePriceText->SetActive(false);
				}
				if (cookie->cookieType == CookieTypes::Moonlighter)
				{
					isMoonlighterLock = cookie->isLock;
					moonlighterPrice->SetActive(false);
					moonlighterPriceText->SetActive(false);
				}
			}
		}
	};
	cookie->OnClicking = [this, cookie]() {
		if (!cookie->isLock)
		{
			cookie->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
		}
	};
}

void StorageBox::SelectLobbyButtonEvent(UIButton* lobby)
{
	lobby->OnEnter = []() {
		// 이펙트 넣기 SetActive(true)
	};
	lobby->OnExit = [this, lobby]() {
		// 이펙트 빼기 SetActive(false)
		if (!lobby->isLock)
		{
			lobby->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		}
	};
	lobby->OnClick = [this, lobby]() {
		if (!lobby->isLock)
		{
			lobby->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
			Variables::CurrentLobbyType = lobby->lobbyType;
			AllSetActive(false);
			this->SetActive(false);
			ReleaseCookieStorage();
			ReleaseSkinStorage();
			ReleaseLobbyStorage();
			SCENE_MGR.ChangeScene(SceneId::Lobby);

		}
		if (lobby->isLock)
		{
			std::cout << scene->GetCoin();
			if (scene->GetDia() < lobby->price)
			{
				isFailed = true;
				failedToBuy->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
				failedToBuy->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
			}
			if (scene->GetDia() >= lobby->price)
			{
				lobby->isLock = false;
				lobby->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
				Variables::coin -= lobby->price;
				scene->SetDia(-lobby->price);

				if (lobby->lobbyType == LobbyType::WizardryTower)
				{
					isWizardryTowerLock = lobby->isLock;
					wizardryTowerPrice->SetActive(false);
					wizardryTowerPriceText->SetActive(false);
				}
				if (lobby->lobbyType == LobbyType::Cathedral)
				{
					isCathedralLock = lobby->isLock;
					cathedralPrice->SetActive(false);
					cathedralPriceText->SetActive(false);
				}
			}
		}
	};
	lobby->OnClicking = [this, lobby]() {
		if (!lobby->isLock)
		{
			lobby->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
		}
	};

}

void StorageBox::ButtonInit(UIButton* btn, sf::Vector2f pos, sf::Vector2f size)
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	//btn->sprite.setColor(sf::Color::Color(255, 30, 0, 255));
	btn->SetPosition(pos);
	btn->sprite.setScale(size);
	btn->SetOrigin(Origins::MC);
	btn->sortLayer = 102;
	btn->text.setPosition(btn->text.getPosition().x, btn->text.getPosition().y - 8.f);

	//btn->OnEnter = [this, btn]() {
	//};
	//btn->OnExit = [this, btn]() {
	//		btn->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	//		btn->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
	//		btn->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	//};
	//btn->OnClick = [this, btn]() {
	//		btn->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	//		btn->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
	//		btn->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	//};
	//btn->OnClicking = [this, btn]() {
	//		btn->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	//		btn->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
	//		btn->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	//};

}

void StorageBox::LockCookie(UIButton* cookie)
{
	if (cookie->isLock)
		cookie->sprite.setColor(sf::Color::Color(0, 0, 0, 255));
	else
		cookie->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
}

void StorageBox::SetFailed()
{
	fadeTimer = 0.f;
	isFailed = false;
	failedToBuy->text.setFillColor(sf::Color::Color(255, 255, 255, 0));
	failedToBuy->text.setOutlineColor(sf::Color::Color(0, 0, 0, 0));
}

void StorageBox::SelectCookieStorage()
{
	selectCookieBtn->sprite.setColor({ 255, 255, 255, 255 });
	selectCookieBtn->text.setFillColor({ 255, 255, 255, 255 });
	selectCookieBtn->text.setOutlineColor({ 0, 0, 0, 255 });

	pancakeButton->SetActive(true);
	pirateButton->SetActive(true);
	moonlighterButton->SetActive(true);

	if (isPirateLock)
	{
		piratePrice->SetActive(true);
		piratePriceText->SetActive(true);
	}

	if (isMoonlighterLock)
	{
		moonlighterPrice->SetActive(true);
		moonlighterPriceText->SetActive(true);
	}

	ReleaseSkinStorage();
	ReleaseLobbyStorage();
}

void StorageBox::SelectSkinStorage()
{
	selectSkinBtn->sprite.setColor({ 255, 255, 255, 255 });
	selectSkinBtn->text.setFillColor({ 255, 255, 255, 255 });
	selectSkinBtn->text.setOutlineColor({ 0, 0, 0, 255 });


	ReleaseCookieStorage();
	ReleaseLobbyStorage();
}

void StorageBox::SelectLobbyStorage()
{
	selectLobbyBtn->sprite.setColor({ 255, 255, 255, 255 });
	selectLobbyBtn->text.setFillColor({ 255, 255, 255, 255 });
	selectLobbyBtn->text.setOutlineColor({ 0, 0, 0, 255 });

	templeButton->SetActive(true);
	wizardryTowerButton->SetActive(true);
	cathedralButton->SetActive(true);

	ReleaseCookieStorage();
	ReleaseSkinStorage();
}

void StorageBox::ReleaseCookieStorage()
{
	selectCookieBtn->sprite.setColor({ 255, 255, 255, 180 });
	selectCookieBtn->text.setFillColor({ 255, 255, 255, 180 });
	selectCookieBtn->text.setOutlineColor({ 0, 0, 0, 180 });

	pancakeButton->SetActive(false);
	pirateButton->SetActive(false);
	moonlighterButton->SetActive(false);

	piratePrice->SetActive(false);
	moonlighterPrice->SetActive(false);
	piratePriceText->SetActive(false);
	moonlighterPriceText->SetActive(false);

}

void StorageBox::ReleaseSkinStorage()
{
	selectSkinBtn->sprite.setColor({ 255, 255, 255, 180 });
	selectSkinBtn->text.setFillColor({ 255, 255, 255, 180 });
	selectSkinBtn->text.setOutlineColor({ 0, 0, 0, 180 });
}

void StorageBox::ReleaseLobbyStorage()
{
	selectLobbyBtn->sprite.setColor({ 255, 255, 255, 180 });
	selectLobbyBtn->text.setFillColor({ 255, 255, 255, 180 });
	selectLobbyBtn->text.setOutlineColor({ 0, 0, 0, 180 });

	templeButton->SetActive(false);
	wizardryTowerButton->SetActive(false);
	cathedralButton->SetActive(false);

}
