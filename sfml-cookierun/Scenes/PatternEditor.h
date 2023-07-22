#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class UIButton;

enum class ObjectType
{
	Platform,
	Item,
	Coin,
	Count,
};

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

	TextGo* editorType;

	// Editor Object
	
	// ������ ���� ǥ��
	ObjectType currentType = ObjectType::Platform;
	TextGo* objectType;
	SpriteGo* typeBg;

	// ��ư
	UIButton* buttonBG;
	UIButton* minusButton;
	UIButton* plusButton;
	UIButton* resetButton;
	UIButton* switchButton;


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
};

