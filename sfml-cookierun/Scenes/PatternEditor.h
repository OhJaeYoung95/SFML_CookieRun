#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class UIButton;
class PatternObject;

class PatternEditor : public Scene
{
protected:



	SpriteGo* currentBg1;
	SpriteGo* currentBg2;
	SpriteGo* nextBg1;
	SpriteGo* nextBg2;

	SpriteGo* currentWindow;
	SpriteGo* nextWindow;

	SpriteGo* cookieGrid;
	SpriteGo* groundGrid;
	SpriteGo* grid;

	UIButton* switchNext;
	UIButton* switchPrevious;

	SpriteGo* editorBg;
	SpriteGo* patternBg;

	TextGo* editorType;

	// Editor Object
	// ���� ����� ����
	TextGo* patternStorage;
	SpriteGo* storageBg;

	int currentPattern = 1;
	
	// ������ ���� ǥ��
	ObjectType currentType = ObjectType::Platform;
	TextGo* objectType;
	SpriteGo* typeBg;


	// ������ ũ�� / ���� ǥ��
	SpriteGo* sizeXBG;
	TextGo* sizeX;
	SpriteGo* sizeYBG;
	TextGo* sizeY;

	float currentSizeX = 1.f;
	float plusSizeX = 0.1f;
	float minusSizeX = -0.1f;

	float currentSizeY = 1.f;
	float plusSizeY = 0.1f;
	float minusSizeY = -0.1f;



	// ��ư
	UIButton* swbuttonBG;
	UIButton* switchButton;

	UIButton* plusButtonXBG;
	UIButton* plusButtonX;

	UIButton* minusButtonXBG;
	UIButton* minusButtonX;

	UIButton* plusButtonYBG;
	UIButton* plusButtonY;

	UIButton* minusButtonYBG;
	UIButton* minusButtonY;

	UIButton* saveButtonBG;
	UIButton* saveButton;

	UIButton* resetButtonBG;
	UIButton* resetButton;

	// ����
	UIButton* ground;
	UIButton* pillar;
	UIButton* platform;
	std::vector<UIButton*> platforms;

	// ������
	UIButton* itemBig;

	UIButton* itemBigHP;
	UIButton* itemBonus1;
	UIButton* itemBonus2;
	UIButton* itemCoin;
	UIButton* itemHP;
	UIButton* itemJelly;
	UIButton* itemMagnet;
	UIButton* itemSpeedUp;
	std::vector<UIButton*> items;

	// ��ȭ
	UIButton* bigCoin;
	UIButton* bigGCoin;
	UIButton* coin;
	UIButton* gCoin;
	UIButton* dia;
	UIButton* diaBox;
	UIButton* luckyBox;
	std::vector<UIButton*> coins;


	//
	std::vector<PatternObject*> patterns;
public:
	PatternEditor();
	virtual ~PatternEditor() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void UIInit(UIButton* object, sf::Vector2f size, sf::Vector2f pos);
	void ButtonEvent(UIButton* object);
	void PatternButtonEvent(UIButton* object);
	void PlusButtonXEvent(UIButton* object);
	void MinusButtonXEvent(UIButton* object);
	void PlusButtonYEvent(UIButton* object);
	void MinusButtonYEvent(UIButton* object);
	void SaveButtonEvent(UIButton* object);
	void ResetButtonEvent(UIButton* object);

	void SavePattern();
};

