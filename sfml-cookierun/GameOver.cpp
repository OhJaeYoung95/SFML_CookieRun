#include "stdafx.h"
#include "GameOver.h"
#include "UIButton.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "Framework.h"
#include "StringTable.h"
#include "DataTableMgr.h"
#include "SceneMgr.h"

GameOver::GameOver(const std::string& textureId, const std::string& n)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	SpriteGo::Init();
	bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	bg.setSize({ 1920, 1080 });
	bg.setOrigin(0, 0);

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

	
	gameOverText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	gameOverText->text.setString(stringTable->GetUni("GAME_OVER", Languages::KOR));
	TextInit(gameOverText, { windowSize.x * 0.5f, windowSize.y * 0.3f }, 80);

	bestScore = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	TextInit(bestScore, { windowSize.x * 0.42f, windowSize.y * 0.4f }, 50);

	currentScore = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	TextInit(currentScore, { windowSize.x * 0.42f, windowSize.y * 0.5f }, 50);


	gameOverBg = (SpriteGo*)scene->AddGo(new SpriteGo("graphics/Lobby/CookieStorageBox/StorageBoxBG.png"));
	gameOverBg->SetPosition(windowSize * 0.5f);
	gameOverBg->SetOrigin(Origins::MC);
	gameOverBg->sortLayer = 100;
	gameOverBg->SetActive(false);

	restartButton = (UIButton*)scene->AddGo(new UIButton("graphics/UI/InGame/PauseButton.png"));
	UIInit(restartButton, { windowSize.x * 0.5f, windowSize.y * 0.64f }, { 3.7f, 3.7f });
	restartButton->text.setString(stringTable->GetUni("REDO", Languages::KOR));
	restartButton->text.setPosition(restartButton->GetPosition().x, restartButton->GetPosition().y - 10.f);
	ButtonEvent(restartButton);
	restartButton->OnClick = [this]() {
		IsActiveGameOver(false);
		SCENE_MGR.ChangeScene(SceneId::Game);
	};

	exitButton = (UIButton*)scene->AddGo(new UIButton("graphics/UI/InGame/PauseButton.png"));
	UIInit(exitButton, { windowSize.x * 0.5f, windowSize.y * 0.77f }, { 3.7f, 3.7f });
	exitButton->text.setString(stringTable->GetUni("EXIT", Languages::KOR));
	exitButton->text.setPosition(restartButton->GetPosition().x, restartButton->GetPosition().y - 10.f);
	ButtonEvent(exitButton);
	exitButton->OnClick = [this]() {
		Variables::coin += scene->GetCoin();
		Variables::diamond += scene->GetDia();
		IsActiveGameOver(false);
		scene->IsChangeScene(true);
		//SCENE_MGR.ChangeScene(SceneId::Lobby);
	};

}


void GameOver::Release()
{
	SpriteGo::Release();

}

void GameOver::Reset()
{
	SpriteGo::Reset();

}

void GameOver::Update(float dt)
{
	SpriteGo::Update(dt);

	std::stringstream scoreS;
	scoreS << "Score: " << scene->GetScore();
	currentScore->text.setString(scoreS.str());
	currentScore->SetOrigin(Origins::ML);

	std::stringstream bestScoreS;
	bestScoreS << "Best Score: " << scene->GetBestScore();
	bestScore->text.setString(bestScoreS.str());
	bestScore->SetOrigin(Origins::ML);

}

void GameOver::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(bg);
}

void GameOver::IsActiveGameOver(bool isActive)
{
	SetActive(isActive);
	gameOverText->SetActive(isActive);
	bestScore->SetActive(isActive);
	currentScore->SetActive(isActive);
	gameOverBg->SetActive(isActive);
	restartButton->SetActive(isActive);
	exitButton->SetActive(isActive);
}

void GameOver::TextInit(TextGo* text, sf::Vector2f pos, int size)
{
	text->SetPosition(pos);
	text->text.setCharacterSize(size);
	text->text.setFillColor(sf::Color::White);
	text->text.setOutlineThickness(4);
	text->text.setOutlineColor(sf::Color::Black);
	text->SetOrigin(Origins::MC);
	text->sortLayer = 102;
	text->SetActive(false);
}

void GameOver::UIInit(UIButton* button, sf::Vector2f pos, sf::Vector2f size)
{
	button->text.setCharacterSize(40);
	button->text.setFillColor(sf::Color::Color(255, 165, 0, 255));
	button->text.setOutlineThickness(4);
	button->text.setOutlineColor(sf::Color::Black);
	button->SetPosition(pos);
	button->sprite.setScale(size);
	button->SetOrigin(Origins::MC);
	button->sortLayer = 101;
	button->SetActive(false);
}

void GameOver::ButtonEvent(UIButton* button)
{
	button->OnEnter = [this, button]() {

	};
	button->OnExit = [this, button]() {
		button->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		button->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		button->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	};
	button->OnClick = [this, button]() {
		button->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		button->text.setFillColor(sf::Color::Color(255, 255, 255, 255));
		button->text.setOutlineColor(sf::Color::Color(0, 0, 0, 255));
	};
	button->OnClicking = [this, button]() {
		button->sprite.setColor(sf::Color::Color(255, 255, 255, 180));
		button->text.setFillColor(sf::Color::Color(255, 255, 255, 180));
		button->text.setOutlineColor(sf::Color::Color(0, 0, 0, 180));
	};
}
