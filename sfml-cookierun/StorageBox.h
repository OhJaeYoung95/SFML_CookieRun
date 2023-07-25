#pragma once
#include "SpriteGo.h"
class UIButton;
class SceneLobby;
class TextGo;

class StorageBox : public SpriteGo
{
protected:
	sf::RectangleShape bg;	// 흑백
	SpriteGo* storageBoxBG;	// BG

	SceneLobby* scene;

	// 캐릭터 선택 버튼
	UIButton* pancakeButton;
	UIButton* pirateButton;
	UIButton* moonlighterButton;	
	
	// 로비 선택 버튼
	UIButton* templeButton;
	UIButton* wizardryTowerButton;
	UIButton* cathedralButton;
	
	// 스킨 선택 버튼
	UIButton* moonSkin1;		// 문 캐릭터 해금 + 해금
	//UIButton* pirateButton;
	//UIButton* moonlighterButton;

	// 해금 목적 비용
	// 캐릭터
	SpriteGo* piratePrice;
	SpriteGo* moonlighterPrice;
	TextGo* piratePriceText;
	TextGo* moonlighterPriceText;	
	
	// 로비
	SpriteGo* wizardryTowerPrice;
	SpriteGo* cathedralPrice;
	TextGo* wizardryTowerPriceText;
	TextGo* cathedralPriceText;

	// 스킨
	//SpriteGo* piratePrice;
	//SpriteGo* moonlighterPrice;
	//TextGo* piratePriceText;
	//TextGo* moonlighterPriceText;


	// 구입 실패 문구 (잔액 부족)
	TextGo* failedToBuy;
	bool isFailed = false;

	float fadeTimer = 0.f;
	float fadeDuration = 0.7f;

	bool isPancakeLock = false;
	bool isPirateLock = true;
	bool isMoonlighterLock = true;	
	
	bool isTempleLock = false;
	bool isWizardryTowerLock = true;
	bool isCathedralLock = true;

	bool isMoonSkinLock1 = true;


	// 스토리지 선택 버튼
	UIButton* selectCookieBtn;
	UIButton* selectSkinBtn;
	UIButton* selectLobbyBtn;



public:
	StorageBox(const std::string& textureId = "", const std::string& n = "");
	virtual ~StorageBox() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetScene(SceneLobby* scene) { this->scene = scene; }
	void AllSetActive(bool isActive);


	void SelectCookieButtonEvent(UIButton* cookie);
	void SelectLobbyButtonEvent(UIButton* lobby);
	void SelectSkinButtonEvent(UIButton* lobby);
	void ButtonInit(UIButton* btn, sf::Vector2f pos, sf::Vector2f size);

	void LockCookie(UIButton* cookie);
	void LockSkin(UIButton* cookie);

	void FailedClear();
	void IsFailedSet(bool isActive) { isFailed = isActive;  }

	void SelectCookieStorage();
	void SelectSkinStorage();
	void SelectLobbyStorage();

	void ReleaseCookieStorage();
	void ReleaseSkinStorage();
	void ReleaseLobbyStorage();
};

