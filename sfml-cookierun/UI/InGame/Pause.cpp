#include "stdafx.h"
#include "Pause.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "UIButton.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "StringTable.h"
#include "DataTableMgr.h"

Pause::Pause(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Pause::~Pause()
{
}

void Pause::Init()
{
	SpriteGo::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSize();


	bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	bg.setSize({ 1920, 1080 });
	bg.setOrigin(0, 0);

	// 버튼과 Text 간격 설정 변수
	float buttonW = 3.7f;
	float buttonH = 3.7f;
	float offset = 100.f;
	float offsetCen = -50.f;

	// 계속하기
	continueButton = (UIButton*)scene->AddGo(new UIButton("graphics/UI/InGame/PauseButton.png"));
	continueButton->sprite.setScale(buttonW, buttonH);
	continueButton->SetOrigin(Origins::MC);
	continueButton->sortLayer = 102;
	continueButton->SetPosition(size.x * 0.5f, size.y * 0.36f + offset + offsetCen);
	auto ptr1 = continueButton;

	//sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/button.png");
	//ptr1->sprite.setTexture(*tex);

	continueButton->OnEnter = [ptr1]() {
		// 이펙트 넣기 SetActive(true)
	};
	continueButton->OnExit = [this]() {
		// 이펙트 빼기 SetActive(false)
		continueButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	continueButton->OnClick = [this]() {
		continueButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		AllSetActive(false);
		this->SetActive(false);
		scene->SetIsPlaying(true);
	};
	continueButton->OnClicking = [this]() {
		continueButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	// 그만하기
	exitButton = (UIButton*)scene->AddGo(new UIButton("graphics/UI/InGame/PauseButton.png"));
	exitButton->sprite.setScale(buttonW, buttonH);
	exitButton->SetOrigin(Origins::MC);
	exitButton->sortLayer = 102;
	exitButton->SetPosition(size.x * 0.5f, size.y * 0.48f + offset + offsetCen);

	auto ptr2 = exitButton;
	exitButton->OnEnter = [ptr2]() {
	};
	exitButton->OnExit = [this]() {
		exitButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	exitButton->OnClick = [this]() {
		AllSetActive(false);
		this->SetActive(false);
		Variables::coin += scene->GetCoin();
		Variables::diamond += scene->GetDia();
		exitButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		scene->IsChangeScene(true);
		//SCENE_MGR.ChangeScene(SceneId::Title);
	};
	exitButton->OnClicking = [this]() {
		exitButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	// 다시하기
	redoButton = (UIButton*)scene->AddGo(new UIButton("graphics/UI/InGame/PauseButton.png"));
	redoButton->sprite.setScale(buttonW, buttonH);
	redoButton->SetOrigin(Origins::MC);
	redoButton->sortLayer = 102;
	redoButton->SetPosition(size.x * 0.5f, size.y * 0.6f + offset + offsetCen);
	auto ptr3 = redoButton;
	redoButton->OnEnter = [ptr3]() {
	};
	redoButton->OnExit = [this]() {
		redoButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	};
	redoButton->OnClick = [this]() {
		redoButton->sprite.setColor(sf::Color::Color(255, 255, 255, 255));
		AllSetActive(false);
		this->SetActive(false);
		scene->IsActiveGameOver(false);
		//scene->IsActiveGameOver(false);
		SCENE_MGR.ChangeScene(SceneId::Game);
	};
	redoButton->OnClicking = [this]() {
		redoButton->sprite.setColor(sf::Color::Color(255, 255, 255, 150));
	};

	StringTable* stringTable = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	pauseText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	pauseText->SetPosition({ size.x * 0.5f, size.y * 0.33f + offsetCen });
	pauseText->text.setString(stringTable->GetUni("PAUSE", Languages::KOR));
	pauseText->text.setCharacterSize(60);
	pauseText->text.setFillColor(sf::Color::Color(255, 165, 0, 255));
	pauseText->text.setOutlineThickness(4);
	pauseText->text.setOutlineColor(sf::Color::Black);
	pauseText->SetOrigin(Origins::MC);
	pauseText->sortLayer = 102;


	// 버튼 텍스트
	continueText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	continueText->text.setScale(1.1f, 1.0f);
	continueText->SetPosition({ continueButton->GetPosition().x, continueButton->GetPosition().y - 10.f });
	continueText->text.setString(stringTable->GetUni("CONTINUE", Languages::KOR));
	continueText->text.setCharacterSize(45);
	continueText->text.setFillColor(sf::Color::Black);
	continueText->SetOrigin(Origins::MC);
	continueText->sortLayer = 102;

	exitText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	exitText->text.setScale(1.1f, 1.0f);
	exitText->SetPosition({ exitButton->GetPosition().x, exitButton->GetPosition().y - 10.f });
	exitText->text.setString(stringTable->GetUni("EXIT", Languages::KOR));
	exitText->text.setCharacterSize(45);
	exitText->text.setFillColor(sf::Color::Black);
	exitText->SetOrigin(Origins::MC);
	exitText->sortLayer = 102;

	redoText = (TextGo*)scene->AddGo(new TextGo("fonts/CookieRun Black.otf"));
	redoText->text.setScale(1.1f, 1.0f);
	redoText->SetPosition({ redoButton->GetPosition().x, redoButton->GetPosition().y - 10.f });
	redoText->text.setString(stringTable->GetUni("REDO", Languages::KOR));
	redoText->text.setCharacterSize(45);
	redoText->text.setFillColor(sf::Color::Black);
	redoText->SetOrigin(Origins::MC);
	redoText->sortLayer = 102;

	scene->AddNPGo(continueButton);
	scene->AddNPGo(exitButton);
	scene->AddNPGo(redoButton);

	AllSetActive(false);
}

void Pause::Release()
{
	SpriteGo::Release();
}

void Pause::Reset()
{
	SpriteGo::Reset();
}

void Pause::Update(float dt)
{
	SpriteGo::Update(dt);

}

void Pause::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(bg);
}

void Pause::AllSetActive(bool isActive)
{
	//bg.setFillColor(sf::Color::Color(0, 0, 0, 150));
	continueButton->SetActive(isActive);
	exitButton->SetActive(isActive);
	redoButton->SetActive(isActive);
	pauseText->SetActive(isActive);
	continueText->SetActive(isActive);
	exitText->SetActive(isActive);
	redoText->SetActive(isActive);
}
