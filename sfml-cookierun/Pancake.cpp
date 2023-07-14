#include "stdafx.h"
#include "Pancake.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

Pancake::Pancake(const std::string& textureId, const std::string& n)
	: Cookie(textureId, n), hp(100)
{
}

Pancake::~Pancake()
{

}

void Pancake::Init()
{
	Cookie::Init();

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

void Pancake::Release()
{    
	Cookie::Release();

}

void Pancake::Reset()
{
	Cookie::Reset();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Run/Run.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Jump/Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Double_Jump/Double_Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Landing/Landing.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Pancake/Sliding/Sliding.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);
	sortLayer = 10;

	animation.Play("Run");
	SetOrigin(origin);
	SetPosition(-500.f, FRAMEWORK.GetWindowSize().y * 0.5f -250.f);
	SetOrigin(rect, origin);
}

void Pancake::Update(float dt)
{
	Cookie::Update(dt);

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

	if (INPUT_MGR.GetKey(sf::Keyboard::Down) && !isSliding && isGround)
	{
		animation.Play("Sliding");
		isSliding = true;
	}

	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Down))
	{
		isSliding = false;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount == 1)
	{
		animation.Play("Jump");
		isSliding = false;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount == 0 && !isDouble)
	{
		isDouble = true;
		animation.Play("Double_Jump");
	}

	if (isGround && animation.GetCurrentClipId() != "Run" 
		&& !isLanding && !isSliding)
	{
		animation.Play("Run");
	}

	animation.Update(dt);
}

void Pancake::Draw(sf::RenderWindow& window)
{
	Cookie::Draw(window);
}
