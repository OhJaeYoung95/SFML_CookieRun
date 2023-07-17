#include "stdafx.h"
#include "UIHp.h"
#include "Cookie.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "AnimationClip.h"

UIHp::UIHp(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

UIHp::~UIHp()
{
}

void UIHp::Init()
{
	SpriteGo::Init();
}

void UIHp::Release()
{
	SpriteGo::Release();
}

void UIHp::Reset()
{
	SpriteGo::Reset();
	hpBack.setTexture(*RESOURCE_MGR.GetTexture("graphics/UI/HpBar/HpBack.png"));
	Utils::SetOrigin(hpBack, origin);
	//hpEnd.setTexture(*RESOURCE_MGR.GetTexture("graphics/UI/HpBar/HpEndEffect.png"));
	//Utils::SetOrigin(hpEnd, Origins::MC);
	//hpEnd.setScale({ 1.0f, 1.5f });

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sprite.setScale({ cookie->GetHp() / cookie->GetMaxHp() * 1.7f, 1.3f });
	hpBack.setScale({ sprite.getScale().x , 1.3f});
	SetPosition(145.f, 100.f);
	hpBack.setPosition({ GetPosition().x, GetPosition().y - 2.f});
	SetOrigin(Origins::TL);
	sortLayer = 102;
	
	animSprite1.setPosition({ 75.f, 75.f });
	animation1.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/UI/HpUI/HpImage.csv"));
	animation1.SetTarget(&animSprite1);
	animation1.Play("HpImage");

	animation2.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/UI/HpUI/HpEndEffect.csv"));
	animation2.SetTarget(&animSprite2);
	animation2.Play("HpEndEffect");

	animSprite2.setScale(0.7f, 1.35f);
	Utils::SetOrigin(animSprite2, Origins::MC);

	decreaseHp = decreaseMaxHp;

}

void UIHp::Update(float dt)
{
	SpriteGo::Update(dt);

	timer += dt;

	if (timer > duration)
	{
		timer = 0.f;
 		cookie->SetHp(-10);
	}
	AnimationClip* clip = animation2.GetCurrentClip();
	clip->frames[0].action = [this]() {
		animSprite2.setScale(1.1f, 1.4f);
	};	
	
	clip->frames[1].action = [this]() {
		animSprite2.setScale(0.5f, 1.4f);
	};
	//std::cout << cookie->GetHp() << " / " << cookie->GetMaxHp() << std::endl;
	sprite.setScale({ cookie->GetHp() / cookie->GetMaxHp() * 1.7f, 1.3f });
	animSprite2.setPosition(GetPosition().x + sprite.getGlobalBounds().width - 13.f, 132.f);

	animation1.Update(dt);
	animation2.Update(dt);
}

void UIHp::Draw(sf::RenderWindow& window)
{
	window.draw(hpBack);
	SpriteGo::Draw(window);
}
