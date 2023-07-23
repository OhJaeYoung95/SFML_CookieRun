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
#include "PatternObject.h"
#include <rapidcsv.h>

PatternEditor::PatternEditor() : Scene(SceneId::Editor)
{
	resourceListPath = "scripts/SceneEditorResourceList.csv";
}

void PatternEditor::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f editor = { 1030.f, 0.f };
	currentType = ObjectType::Platform;

	//PatternObject* obj = (PatternObject*)AddGo(new PatternObject("graphics/Stage1/Ground.png"));
	//obj->SetPosition(500, 500);
	//obj->SetOrigin(Origins::MC);
	//obj->sortLayer = 101;

	// 게임 오브젝트(0~99)는 가운데서 생성 / UI 오브젝트 ( 100 ~ )는 화면의 좌측 상단(TL)에서 생성
	
	// 배경
	editorBg = (SpriteGo*)AddGo(new SpriteGo());
	editorBg->rect.setSize({ 400.f, 1050.f });
	editorBg->rect.setFillColor(sf::Color::Color(255, 255, 255, 50));
	editorBg->SetOrigin(Origins::MC);
	editorBg->SetPosition(editor.x * 0.25f, windowSize.y * 0.5f);
	editorBg->sortLayer = 100;

	patternBg = (SpriteGo*)AddGo(new SpriteGo());
	patternBg->rect.setSize({ 400.f, 1050.f });
	patternBg->rect.setFillColor(sf::Color::Color(255, 255, 255, 50));
	patternBg->SetOrigin(Origins::MC);
	patternBg->SetPosition(editor.x * 0.75f, windowSize.y * 0.5f);
	patternBg->sortLayer = 100;

	// 화면
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
	cookieGrid->SetPosition(-500.f + editor.x * 0.5f, windowSize.y * 0.5f - 250.f);
	cookieGrid->sortLayer = 10;

	groundGrid = (SpriteGo*)AddGo(new SpriteGo());
	groundGrid->rect.setSize({ (1920.f * 2.0f) + editor.x , 5.f } );
	groundGrid->rect.setFillColor(sf::Color::Green);
	groundGrid->SetOrigin(Origins::ML);
	groundGrid->SetPosition(0.f + editor.x, 825.f);
	groundGrid->sortLayer = 100;
 
	// 표기
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




	// 지형
	ground = (UIButton*)AddGo(new UIButton("graphics/Stage1/Ground.png"));
	pillar = (UIButton*)AddGo(new UIButton("graphics/Stage1/Pillar1.png"));
	platform = (UIButton*)AddGo(new UIButton("graphics/Stage1/Platform.png"));
	
	UIInit(ground, { 1, 1 }, { 170, 300 });
	UIInit(pillar, { 0.5, 0.5 }, { 340, 330 });
	UIInit(platform, { 1, 1 }, { 170, 500 });
	
	ButtonEvent(ground);
	ButtonEvent(pillar);
	ButtonEvent(platform);
	
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
	
	float offset = -50;
	UIInit(itemBig, { 1, 1 }, { 150, 250 + offset });
	UIInit(itemBigHP, { 1, 1 }, { 350, 230 });
	UIInit(itemBonus1, { 1, 1 }, { 150, 370 + offset });
	UIInit(itemBonus2, { 1, 1 }, { 350, 370 });
	UIInit(itemCoin, { 1, 1 }, { 150, 490 + offset });
	UIInit(itemHP, { 1, 1 }, { 350, 520 });
	UIInit(itemJelly, { 1, 1 }, { 150, 610 + offset });
	UIInit(itemMagnet, { 1, 1 }, { 350, 670 });
	UIInit(itemSpeedUp, { 1, 1 }, { 150, 730 + offset });

	ButtonEvent(itemBig);
	ButtonEvent(itemBigHP);
	ButtonEvent(itemBonus1);
	ButtonEvent(itemBonus2);
	ButtonEvent(itemCoin);
	ButtonEvent(itemHP);
	ButtonEvent(itemJelly);
	ButtonEvent(itemMagnet);
	ButtonEvent(itemSpeedUp);

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
	
	ButtonEvent(bigCoin);
	ButtonEvent(bigGCoin);
	ButtonEvent(coin);
	ButtonEvent(gCoin);
	ButtonEvent(dia);
	ButtonEvent(diaBox);
	ButtonEvent(luckyBox);

	coins.push_back(bigCoin);
	coins.push_back(bigGCoin);
	coins.push_back(coin);
	coins.push_back(gCoin);
	coins.push_back(dia);
	coins.push_back(diaBox);
	coins.push_back(luckyBox);

	// 버튼
	{
		sizeX = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
		sizeX->SetPosition({ 160, 900 });
		sizeX->text.setCharacterSize(25);
		sizeX->text.setFillColor(sf::Color::White);
		sizeX->text.setOutlineThickness(3);
		sizeX->text.setOutlineColor(sf::Color::Black);
		sizeX->sortLayer = 110;

		sizeXBG = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/PlayButton.png"));
		sizeXBG->SetPosition({ 160, 900 });
		sizeXBG->sprite.setScale(1.5f, 2.2f);
		sizeXBG->sprite.setColor(sf::Color::Color(0, 0, 0, 255));
		sizeXBG->SetOrigin(Origins::MC);
		sizeXBG->sortLayer = 101;

		sizeY = (TextGo*)AddGo(new TextGo("fonts/CookieRun Black.otf"));
		sizeY->SetPosition({ 160, 1000 });
		sizeY->text.setCharacterSize(25);
		sizeY->text.setFillColor(sf::Color::White);
		sizeY->text.setOutlineThickness(3);
		sizeY->text.setOutlineColor(sf::Color::Black);
		sizeY->sortLayer = 102;

		sizeYBG = (SpriteGo*)AddGo(new SpriteGo("graphics/Lobby/PlayButton.png"));
		sizeYBG->SetPosition({ 160, 1000 });
		sizeYBG->sprite.setScale(1.5f, 2.2f);
		sizeYBG->sprite.setColor(sf::Color::Color(0, 0, 0, 255));
		sizeYBG->SetOrigin(Origins::MC);
		sizeYBG->sortLayer = 101;

		swbuttonBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		swbuttonBG->sortLayer = 101;
		switchButton = (UIButton*)AddGo(new UIButton("graphics/Editor/SwitchButton.png"));
		switchButton->sortLayer = 101;
		UIInit(swbuttonBG, { 1.5, 1.5 }, { 400, 80 });
		UIInit(switchButton, { 1, 1 }, { 400, 80 });

		plusButtonXBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		plusButtonXBG->sortLayer = 101;
		plusButtonX = (UIButton*)AddGo(new UIButton("graphics/Editor/PlusButton.png"));
		plusButtonX->sortLayer = 101;
		UIInit(plusButtonXBG, { 1.5, 1.5 }, { 300, 900 });
		UIInit(plusButtonX, { 1, 1 }, { 300, 900 });
		PlusButtonXEvent(plusButtonXBG);

		minusButtonXBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		minusButtonXBG->sortLayer = 101;
		minusButtonX = (UIButton*)AddGo(new UIButton("graphics/Editor/MinusButton.png"));
		minusButtonX->sortLayer = 101;
		UIInit(minusButtonXBG, { 1.5, 1.5 }, { 400, 900 });
		UIInit(minusButtonX, { 1, 1 }, { 400, 900 });
		MinusButtonXEvent(minusButtonXBG);

		plusButtonYBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		plusButtonYBG->sortLayer = 101;
		plusButtonY = (UIButton*)AddGo(new UIButton("graphics/Editor/PlusButton.png"));
		plusButtonY->sortLayer = 101;
		UIInit(plusButtonYBG, { 1.5, 1.5 }, { 300, 1000 });
		UIInit(plusButtonY, { 1, 1 }, { 300, 1000 });
		PlusButtonYEvent(plusButtonYBG);

		minusButtonYBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		minusButtonYBG->sortLayer = 101;
		minusButtonY = (UIButton*)AddGo(new UIButton("graphics/Editor/MinusButton.png"));
		minusButtonY->sortLayer = 101;
		UIInit(minusButtonYBG, { 1.5, 1.5 }, { 400, 1000 });
		UIInit(minusButtonY, { 1, 1 }, { 400, 1000 });
		MinusButtonYEvent(minusButtonYBG);



		saveButtonBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		saveButtonBG->sortLayer = 101;
		saveButton = (UIButton*)AddGo(new UIButton("graphics/Editor/SaveButton.png"));
		saveButton->sortLayer = 101;
		UIInit(saveButtonBG, { 1.5, 1.5 }, { 750, 1000 });
		UIInit(saveButton, { 0.8, 0.8 }, { 750, 1000 });
		SaveButtonEvent(saveButtonBG);

		resetButtonBG = (UIButton*)AddGo(new UIButton("graphics/Editor/ButtonBG.png"));
		resetButtonBG->sortLayer = 101;
		resetButton = (UIButton*)AddGo(new UIButton("graphics/Editor/ResetButton.png"));
		resetButton->sortLayer = 101;
		UIInit(resetButtonBG, { 1.5, 1.5 }, { 650, 1000 });
		UIInit(resetButton, { 1, 1 }, { 650, 1000 });
		ResetButtonEvent(resetButtonBG);

	}


	auto ptr1 = switchButton;
	switchButton->OnEnter = [ptr1]() {

	};
	switchButton->OnExit = [this]() {
		switchButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		swbuttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
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
		swbuttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

	};
	switchButton->OnClicking = [this]() {
		switchButton->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		swbuttonBG->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};

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

	// 화면 크기 그리드
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
	sf::Vector2f editor = {1030.f, 0.f};
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
	std::stringstream sizeXS;
	sizeXS << "X Scale : " << currentSizeX;
	sizeX->text.setString(sizeXS.str());
	sizeX->SetOrigin(Origins::MC);

	std::stringstream sizeYS;
	sizeYS << "Y Scale : " << currentSizeY;
	sizeY->text.setString(sizeYS.str());
	sizeY->SetOrigin(Origins::MC);

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

void PatternEditor::ButtonEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {
		
	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		PatternObject* obj = (PatternObject*)AddGo(new PatternObject(object->textureId));
		obj->Reset();
		obj->sprite.setScale(currentSizeX, currentSizeY);
		obj->SetPosition(500, 500);
		obj->SetOrigin(Origins::MC);
		obj->sortLayer = 101;
		PatternButtonEvent(obj);
		patterns.push_back(obj);
		currentSizeX = 1.f;
		currentSizeY = 1.f;
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};
}

void PatternEditor::PatternButtonEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		// pos어떻게 해야할지
	};
	object->OnClicking = [this, object]() {
		sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
		sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		object->SetPosition(uiMousePos);
	};
}
void PatternEditor::PlusButtonXEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		plusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		plusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		currentSizeX += plusSizeX;
		std::cout << currentSizeX << std::endl;

	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		plusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};

}
void PatternEditor::MinusButtonXEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		minusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		minusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		currentSizeX += minusSizeX;
		std::cout << currentSizeX << std::endl;
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		minusButtonX->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};
}
void PatternEditor::PlusButtonYEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		plusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		plusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		currentSizeY += plusSizeY;
		std::cout << currentSizeY << std::endl;
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		plusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};
}
void PatternEditor::MinusButtonYEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		minusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		minusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		currentSizeY += minusSizeY;
		std::cout << currentSizeY << std::endl;
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		minusButtonY->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};
}
void PatternEditor::SaveButtonEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		saveButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		saveButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		SavePattern();
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		saveButton->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};

}

void PatternEditor::ResetButtonEvent(UIButton* object)
{
	object->OnEnter = [this, object]() {

	};
	object->OnExit = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		resetButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

	};
	object->OnClick = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		resetButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));

		for (auto pattern : patterns)
		{
			RemoveGo(pattern);
		}
		patterns.clear();
	};
	object->OnClicking = [this, object]() {
		object->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		resetButton->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
	};

}

void PatternEditor::SavePattern()
{
	rapidcsv::Document doc;

	std::string fileName = "Pattern" + std::to_string(currentPattern) + ".csv";

	doc.SetColumnName({ "Type", ""});

	doc.Save(fileName);
}
