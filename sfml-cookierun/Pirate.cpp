#include "stdafx.h"
#include "Pirate.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

Pirate::Pirate(const std::string& textureId, const std::string& n)
	: Cookie(textureId, n)
{
}

Pirate::~Pirate()
{

}

void Pirate::Init()
{
	Cookie::Init();
	//SetType(CookieTypes::Pancake);

	// scripts에서 정보를 넣어서 할때는 Enter에서 AddClip을 해줘야한다
	// Init에서 하고 싶을경우는 아래와 같이 해주어야 한다.

	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Pancake/Run/Run.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Pancake/Jump/Jump.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Pancake/Double_Jump/Double_Jump.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Pancake/Landing/Landing.csv");
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Pancake/Sliding/Sliding.csv");

	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Run/Run.csv"));
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Jump/Jump.csv"));
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Double_Jump/Double_Jump.csv"));
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Landing/Landing.csv"));
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Sliding/Sliding.csv"));
	//animation.SetTarget(&sprite);
	//SetOrigin(Origins::BC);
	//sortLayer = 10;
}

void Pirate::Release()
{
	Cookie::Release();

}

void Pirate::Reset()
{
	Cookie::Reset();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Run/Run.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Jump/Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Double_Jump/Double_Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Landing/Landing.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Sliding/Sliding.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Hit/Hit.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pirate/Die/Die.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);
	sortLayer = 10;

	animation.Play("Run");
	SetOrigin(origin);
	SetPosition(-500.f, FRAMEWORK.GetWindowSize().y * 0.5f - 250.f);
	SetOrigin(rect, origin);
}

void Pirate::Update(float dt)
{
	Cookie::Update(dt);

	if (!isAlive)
		dieTimer += dt;

	if (!isAlive && !isDieAnim)
	{
		isDieAnim = true;
		animation.Play("Die");
	}

	if (animation.GetCurrentClipId() == "Run" && isDieAnim)
	{
		animation.Play("Die");
	}


	if (isHit && !isHitAnim)
	{
		isHitAnim = true;
		animation.Play("Hit");
		animation.PlayQueue("Run");
	}

	if ((isGround && animation.GetCurrentClipId() == "Jump")
		|| (isGround && animation.GetCurrentClipId() == "Double_Jump"))
	{
		isLanding = true;
		landingTimer = 0.1f;
		animation.Play("Landing");
	}

	if (isLanding)
	{
		landingTimer -= dt;
	}

	if (landingTimer < 0.f)
	{
		isLanding = false;
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Down) && !isSliding && isGround && !isDieAnim)
	{
		animation.Play("Sliding");
		isSliding = true;
	}

	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Down) && !isDieAnim)
	{
		isSliding = false;
		animation.PlayQueue("Run");
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount == 1 && !isDieAnim)
	{
		animation.Play("Jump");
		isSliding = false;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount == 0 && !isDouble && !isDieAnim)
	{
		isDouble = true;
		animation.Play("Double_Jump");
	}

	if (isGround && animation.GetCurrentClipId() != "Run"
		&& !isLanding && !isSliding && !isHitAnim && !isDieAnim)
	{
		animation.Play("Run");
	}

	animation.Update(dt);
}

void Pirate::Draw(sf::RenderWindow& window)
{
	Cookie::Draw(window);
}
