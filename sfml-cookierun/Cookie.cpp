#include "stdafx.h"
#include "Cookie.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

Cookie::Cookie(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Cookie::~Cookie()
{
}

void Cookie::Init()
{
	SpriteGo::Init();
}

void Cookie::Release()
{
	SpriteGo::Release();
}

void Cookie::Reset()
{
	SpriteGo::Reset();
	isAlive = true;
	isGround = true;
	isDouble = false;
	isSliding = false;
	isLanding = false;
	jumpCount = 2;
}

void Cookie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount > 0)
	{
		if(jumpCount == 2)
			velocity += jumpForce;

		if (jumpCount == 1)
		{
			velocity = 0;
			velocity += doubleJumpForce;
		}

		isGround = false;
		jumpCount--;
	}
	velocity += gravity * (jumpSpeed -0.7f )* dt;
	position.y += velocity * jumpSpeed * dt;

	//std::cout << position.y << std::endl;
	//std::cout << jumpCount << std::endl;
	if (position.y > 290.f)
	{
		isDouble = false;
		jumpCount = 2;
		isGround = true;
		position.y = 290.f;
		velocity = 0.f;
	}

	SetPosition(position);
}

void Cookie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

void Cookie::Die()
{
	isAlive = false;
}

//void Cookie::PickUpItem()
//{
//}