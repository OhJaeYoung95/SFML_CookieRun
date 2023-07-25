#pragma once
#include "SpriteGo.h"
class UIButton;
class SceneLobby;
class TextGo;

class StorageBox : public SpriteGo
{
protected:
	sf::RectangleShape bg;	// ���
	SpriteGo* storageBoxBG;	// BG

	SceneLobby* scene;

	// ĳ���� ���� ��ư
	UIButton* pancakeButton;
	UIButton* pirateButton;
	UIButton* moonlighterButton;	
	
	// �κ� ���� ��ư
	UIButton* templeButton;
	UIButton* wizardryTowerButton;
	UIButton* cathedralButton;
	
	// ��Ų ���� ��ư
	//UIButton* pancakeButton;
	//UIButton* pirateButton;
	//UIButton* moonlighterButton;

	// ��� / �ر� ����
	// ĳ����
	SpriteGo* piratePrice;
	SpriteGo* moonlighterPrice;
	TextGo* piratePriceText;
	TextGo* moonlighterPriceText;	
	
	// �κ�
	SpriteGo* wizardryTowerPrice;
	SpriteGo* cathedralPrice;
	TextGo* wizardryTowerPriceText;
	TextGo* cathedralPriceText;

	// ��Ų
	//SpriteGo* piratePrice;
	//SpriteGo* moonlighterPrice;
	//TextGo* piratePriceText;
	//TextGo* moonlighterPriceText;


	// ���� ���� ����
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


	// ���丮�� ���� ��ư
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
	void ButtonInit(UIButton* btn, sf::Vector2f pos, sf::Vector2f size);

	void LockCookie(UIButton* cookie);
	void SetFailed();
	void IsFailedSet(bool isActive) { isFailed = isActive;  }

	void SelectCookieStorage();
	void SelectSkinStorage();
	void SelectLobbyStorage();

	void ReleaseCookieStorage();
	void ReleaseSkinStorage();
	void ReleaseLobbyStorage();
};

