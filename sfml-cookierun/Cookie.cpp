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
	rect.setSize(sf::Vector2f(100.f, 120.f));
	rect.setFillColor(sf::Color::Green);
	SetOrigin(rect, origin);

	switch (type)
	{
	case CookieTypes::Pancake:
		maxHp = 100;
		break;
	case CookieTypes::Pirate:
		maxHp = 130;
		break;
	case CookieTypes::Moonlighter:
		maxHp = 150;
		break;
	}
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

	hp = maxHp;
}

void Cookie::Update(float dt)
{
	SpriteGo::Update(dt);
	rect.setPosition(GetPosition());
		
	if(INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		rect.setFillColor(sf::Color::Color(255, 255, 255, 0));
	if(INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		rect.setFillColor(sf::Color::Green);

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
	//if (position.y > 290.f)
	//{
	//	isDouble = false;
	//	jumpCount = 2;
	//	isGround = true;
	//	position.y = 290.f;
	//	velocity = 0.f;
	//}

	SetPosition(position);
}

void Cookie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(rect);
}

void Cookie::Die()
{
	isAlive = false;
}

float Cookie::GetVelocity()
{
	return velocity;
}

bool Cookie::GetIsGround()
{
	return isGround;
}


void Cookie::SetHp(int value)
{
	int sum = hp + value;
	if (sum > maxHp)
	{
		hp = maxHp;
		return;
	}
	 hp += value; 
}

void Cookie::SetScale(sf::Vector2f value)
{
	sprite.setScale(value);
}

void Cookie::SetIsGround(bool isGround)
{
	this->isGround = isGround;
}

void Cookie::SetGravity()
{
	velocity = 0.f;
}

void Cookie::SetJumpCount()
{
	jumpCount = 2;
}

void Cookie::SetIsDouble(bool isDobule)
{
	this->isDouble = false;
}

//void Cookie::PickUpItem()
//{
//}