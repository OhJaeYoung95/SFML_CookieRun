#include "stdafx.h"
#include "PatternEditor.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "StringTable.h"
#include "DataTableMgr.h"
#include "UIButton.h"
PatternEditor::PatternEditor() : Scene(SceneId::Editor)
{
	resourceListPath = "scripts/SceneEditorResourceList.csv";
}

void PatternEditor::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f editor = { 500.f, 0.f };
	currentType = ObjectType::Platform;

	// 게임 오브젝트(0~99)는 가운데서 생성 / UI 오브젝트 ( 100 ~ )는 화면의 좌측 상단(TL)에서 생성
	
	editorBg = (SpriteGo*)AddGo(new SpriteGo());
	editorBg->rect.setSize({ 400.f, 1050.f });
	editorBg->rect.setFillColor(sf::Color::Color(255, 255, 255, 50));
	editorBg->SetOrigin(Origins::MC);
	editorBg->SetPosition(editor.x * 0.5f, windowSize.y * 0.5f);
	editorBg->sortLayer = 100;

	currentBg1 = (SpriteGo*)AddGo(new SpriteGo("graphics/Stage1/Background1.png"));
	currentBg1->sortLayer = 1;
	currentBg2 = (SpriteGo*)AddGo(new SpriteGo("graphics/Stage1/Background2.png"));
	currentBg2->sortLayer = 0;

	
	nextBg1 = (SpriteGo*)AddGo(new SpriteGo("graphics/Stage1/Background1.png"));
	nextBg1->sortLayer = 0;
	nextBg2 = (SpriteGo*)AddGo(new SpriteGo("graphics/Stage1/Background2.png"));
	nextBg2->sortLayer = 0;

	cookieGrid = (SpriteGo*)AddGo(new SpriteGo());
	cookieGrid->rect.setSize({ 100.f, 120.f });
	cookieGrid->rect.setOutlineColor(sf::Color::Cyan);
	cookieGrid->rect.setOutlineThickness(5);
	cookieGrid->rect.setFillColor(sf::Color::Transparent);
	cookieGrid->SetOrigin(Origins::BC);
	cookieGrid->SetPosition(-500.f, windowSize.y * 0.5f - 250.f);
	cookieGrid->sortLayer = 10;

	groundGrid = (SpriteGo*)AddGo(new SpriteGo());
	groundGrid->rect.setSize({ (1920.f * 2.0f) + editor.x , 5.f } );
	groundGrid->rect.setFillColor(sf::Color::Green);
	groundGrid->SetOrigin(Origins::ML);
	groundGrid->SetPosition(0.f + editor.x, 825.f);
	groundGrid->sortLayer = 100;
 
	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);
	objectType = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
	objectType->SetPosition({ 220, 80 });
	objectType->text.setCharacterSize(40);
	objectType->text.setFillColor(sf::Color::White);
	objectType->text.setOutlineThickness(3);
	objectType->text.setOutlineColor(sf::Color::Black);
	objectType->sortLayer = 102;

	typeBg = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/PlayButton.png"));
	typeBg->SetPosition({ 220, 85 });
	typeBg->sprite.setScale(1.8f, 2.5f);
	typeBg->sprite.setColor(sf::Color::Color(0, 0, 0, 255));
	typeBg->SetOrigin(Origins::MC);
	typeBg->sortLayer = 101;


	buttonBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
	switchButton = (UIButton*)AddGo(new UIButton("graphics/Editor/SwitchButton.png"));
	UIInit(buttonBG, { 1.5, 1.5 }, { 400, 80 });
	UIInit(switchButton, { 1, 1 }, { 400, 80 });


	auto ptr1 = switchButton;
	switchButton->OnEnter = [ptr1]() {

	};
	switchButton->OnExit = [this]() {
		switchButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		buttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	switchButton->OnClick = [this, stringTable]() {
		int type = ((int)currentType + 1) % (int)ObjectType::Count;
		currentType = (ObjectType)type;

		switch (currentType)
		{
		case ObjectType::Platform:
			objectType->text.setString(stringTable->GetUni("GROUND", Languages::KOR));
			objectType->SetOrigin(Origins::MC);
			for (auto platform : platforms)
				platform->SetActive(true);
			for (auto coin : coins)
				coin->SetActive(false);
			break;
		case ObjectType::Item:
			objectType->text.setString(stringTable->GetUni("ITEM", Languages::KOR));
			objectType->SetOrigin(Origins::MC);
			for (auto item : items)
				item->SetActive(true);
			for (auto platform : platforms)
				platform->SetActive(false);

			break;
		case ObjectType::Coin:
			objectType->text.setString(stringTable->GetUni("COIN", Languages::KOR));
			objectType->SetOrigin(Origins::MC);
			for (auto item : items)
				item->SetActive(false);
			for (auto coin : coins)
				coin->SetActive(true);
			break;
		}
		switchButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		buttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

	};
	switchButton->OnClicking = [this]() {
		switchButton->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		buttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};

	// 지형
	ground = (UIButton*)AddGo(new UIButton("graphics/Stage1/Ground.png"));
	pillar = (UIButton*)AddGo(new UIButton("graphics/Stage1/Pillar1.png"));
	platform = (UIButton*)AddGo(new UIButton("graphics/Stage1/Platform.png"));
	UIInit(ground, { 1, 1 }, { 170, 300 });
	UIInit(pillar, { 0.5, 0.5 }, { 340, 330 });
	UIInit(platform, { 1, 1 }, { 170, 500 });
	platforms.push_back(ground);
	platforms.push_back(pillar);
	platforms.push_back(platform);

	// 아이템
	itemBig = (UIButton*)AddGo(new UIButton("graphics/Item/ItemBig1.png"));
	itemBigHP = (UIButton*)AddGo(new UIButton("graphics/Item/ItemBigHealPack1.png"));
	itemBonus1 = (UIButton*)AddGo(new UIButton("graphics/Item/ItemBonus1.png"));
	itemBonus2 = (UIButton*)AddGo(new UIButton("graphics/Item/ItemBonusTime.png"));
	itemCoin = (UIButton*)AddGo(new UIButton("graphics/Item/ItemCoin1.png"));
	itemHP = (UIButton*)AddGo(new UIButton("graphics/Item/ItemHealPack1.png"));
	itemJelly = (UIButton*)AddGo(new UIButton("graphics/Item/ItemJelly1.png"));
	itemMagnet = (UIButton*)AddGo(new UIButton("graphics/Item/ItemMagnet1.png"));
	itemSpeedUp = (UIButton*)AddGo(new UIButton("graphics/Item/ItemSpeedUp1.png"));

	float offset = -30;
	UIInit(itemBig, { 1, 1 }, { 150, 250 + offset});
	UIInit(itemBigHP, { 1, 1 }, { 350, 230 });
	UIInit(itemBonus1, { 1, 1 }, { 150, 400 + offset });
	UIInit(itemBonus2, { 1, 1 }, { 350, 370 });
	UIInit(itemCoin, { 1, 1 }, { 150, 550 + offset });
	UIInit(itemHP, { 1, 1 }, { 350, 520 });
	UIInit(itemJelly, { 1, 1 }, { 150, 700 + offset });
	UIInit(itemMagnet, { 1, 1 }, { 350, 670 });
	UIInit(itemSpeedUp, { 1, 1 }, { 150, 850 + offset });

	items.push_back(itemBig);
	items.push_back(itemBigHP);
	items.push_back(itemBonus1);
	items.push_back(itemBonus2);
	items.push_back(itemCoin);
	items.push_back(itemHP);
	items.push_back(itemJelly);
	items.push_back(itemMagnet);
	items.push_back(itemSpeedUp);

	// 재화
	bigCoin = (UIButton*)AddGo(new UIButton("graphics/Jelly/Coin/BigCoin1.png"));
	bigGCoin = (UIButton*)AddGo(new UIButton("graphics/Jelly/Coin/BigGoldCoin1.png"));
	coin = (UIButton*)AddGo(new UIButton("graphics/Jelly/Coin/Coin1.png"));
	gCoin = (UIButton*)AddGo(new UIButton("graphics/Jelly/Coin/GoldCoin1.png"));
	dia = (UIButton*)AddGo(new UIButton("graphics/Jelly/Diamond/Diamond.png"));
	diaBox = (UIButton*)AddGo(new UIButton("graphics/Jelly/Diamond/DiamondBox.png"));
	luckyBox = (UIButton*)AddGo(new UIButton("graphics/Jelly/Diamond/LuckyBox.png"));
	UIInit(bigCoin, { 1, 1 }, { 150, 250 });
	UIInit(bigGCoin, { 1, 1 }, { 350, 250 });
	UIInit(coin, { 1, 1 }, { 150, 400 });
	UIInit(gCoin, { 1, 1 }, { 350, 400 });
	UIInit(dia, { 1, 1 }, { 150, 500 });
	UIInit(diaBox, { 1, 1 }, { 350, 500 });
	UIInit(luckyBox, { 1, 1 }, { 150, 650 });

	coins.push_back(bigCoin);
	coins.push_back(bigGCoin);
	coins.push_back(coin);
	coins.push_back(gCoin);
	coins.push_back(dia);
	coins.push_back(diaBox);
	coins.push_back(luckyBox);

	// 버튼
	buttonBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
	minusButton = (UIButton*)AddGo(new UIButton("graphics/Editor/MinusButton.png"));
	plusButton = (UIButton*)AddGo(new UIButton("graphics/Editor/PlusButton.png"));
	resetButton = (UIButton*)AddGo(new UIButton("graphics/Editor/ResetButton.png"));	
	switchButton = (UIButton*)AddGo(new UIButton("graphics/Editor/SwitchButton.png"));

	int gridSizeCol = windowSize.y / 100;
	for (int i = 0; i < 2; i++)
	{
		grid = (SpriteGo*)AddGo(new SpriteGo());
		grid->rect.setSize({ (1920.f * 2.0f) + editor.x , 5.f });
		grid->rect.setFillColor(sf::Color::Color(255, 255, 255, 180));
		grid->SetOrigin(Origins::ML);
		grid->SetPosition(editor.x, 100 * (i+1));
		grid->sortLayer = 100;
	}

	int gridSizeRow = windowSize.x / 100;
	for (int i = 0; i < 2; i++)
	{
		grid = (SpriteGo*)AddGo(new SpriteGo());
		grid->rect.setSize({ 5.f , 1080.f});
		grid->rect.setFillColor(sf::Color::Color(255, 255, 255, 180));
		grid->SetOrigin(Origins::TC);
		grid->SetPosition((100 * (i + 1)) + editor.x,0);
		grid->sortLayer = 100;
	}

	currentWindow = (SpriteGo*)AddGo(new SpriteGo());
	currentWindow->rect.setSize({1910.f, 1070.f});
	currentWindow->rect.setOutlineColor(sf::Color::Red);
	currentWindow->rect.setOutlineThickness(10);
	currentWindow->rect.setFillColor(sf::Color::Transparent);
	currentWindow->SetOrigin(Origins::MC);
	currentWindow->SetPosition(windowSize.x * 0.5f + 10.f + editor.x, windowSize.y * 0.5f + 10.f + editor.y);
	currentWindow->sortLayer = 100;


	nextWindow = (SpriteGo*)AddGo(new SpriteGo());


	for (auto platform : platforms)
		platform->SetActive(true);
	for (auto item : items)
		item->SetActive(false);
	for (auto coin : coins)
		coin->SetActive(false);

	switch (currentType)
	{
	case ObjectType::Platform:
		objectType->text.setString(stringTable->GetUni("GROUND", Languages::KOR));
		objectType->SetOrigin(Origins::MC);
		break;
	case ObjectType::Item:
		objectType->text.setString(stringTable->GetUni("ITEM", Languages::KOR));
		objectType->SetOrigin(Origins::MC);
		break;
	case ObjectType::Coin:
		objectType->text.setString(stringTable->GetUni("COIN", Languages::KOR));
		objectType->SetOrigin(Origins::MC);
		break;
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}

}

void PatternEditor::Release()
{	
	// 이 부분 생각하기 / Enter? Release? / 안에 내용물들은 어떻게 처리해야하나
	coins.clear();
	items.clear();
	platforms.clear();
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void PatternEditor::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	sf::Vector2f editor = { 500.f, 0.f};
	worldView.setSize(size);
	worldView.setCenter(0, 0);

	uiView.setSize(size + editor);
	uiView.setCenter((size + editor) * 0.5f);
	Scene::Enter();
}

void PatternEditor::Exit()
{
	Scene::Exit();

}

void PatternEditor::Update(float dt)
{
	Scene::Update(dt);
}

void PatternEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void PatternEditor::UIInit(UIButton* object, sf::Vector2f size, sf::Vector2f pos)
{
	object->SetPosition(pos);
	object->sprite.setScale(size);
	object->SetOrigin(Origins::MC);
	object->sortLayer = 101;
}
