#include "stdafx.h"
#include "Cookie.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "SceneGame.h"
#include "Map.h"

Cookie::Cookie(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

Cookie::~Cookie()
{
}

void Cookie::Init()
{
	// 전역으로 타입 설정
	type = Variables::CurrentCookieType;

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

	isDieAnim = false;
	jumpCount = 2;

	hp = maxHp;
	hitTimer = 0.f;
}

void Cookie::Update(float dt)
{
	SpriteGo::Update(dt);
	rect.setPosition(GetPosition());
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		rect.setFillColor(sf::Color::Color(255, 255, 255, 0));
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		rect.setFillColor(sf::Color::Green);

	if (GetPosition().y > 960)
	{
		isAlive = false;

	}

	if (!isAlive)
	{
		Die();
	}

	//if (!isAlive && !isDieAnim)
	//	return;
	if (isAlive)
	{
		if (hp <= 0)
		{
			isAlive = false;
		}

		if (isHit)
		{
			hitTimer += dt;
		}

		if (hitTimer > hitDuration)
		{
			hitTimer = 0.f;
			isHit = false;
			isHitAnim = false;
		}


		if (INPUT_MGR.GetKey(sf::Keyboard::Down) && isGround)
		{
			rect.setSize(sf::Vector2f(100.f, 90.f));
			SetOrigin(rect, origin);
			scene->SlideUIDown(true);
		}
		if (INPUT_MGR.GetKeyUp(sf::Keyboard::Down))
		{
			rect.setSize(sf::Vector2f(100.f, 120.f));
			SetOrigin(rect, origin);
			scene->SlideUIDown(false);
		}
		if (isHit)
		{
			rect.setSize(sf::Vector2f(100.f, 120.f));
			SetOrigin(rect, origin);
		}

		if (INPUT_MGR.GetKey(sf::Keyboard::Down) && !isGround)
		{
			rect.setSize(sf::Vector2f(100.f, 120.f));
			SetOrigin(rect, origin);
		}


		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && jumpCount > 0)
		{
			scene->JumpUIDown(true);
			scene->SlideUIDown(false);

			if (jumpCount == 2)
				velocity += jumpForce;

			if (jumpCount == 1)
			{
				velocity = 0;
				velocity += doubleJumpForce;
			}

			isGround = false;
			jumpCount--;
		}

		if (INPUT_MGR.GetKeyUp(sf::Keyboard::Space))
		{
			scene->JumpUIDown(false);
		}
		velocity += gravity * (jumpSpeed - 0.7f) * dt;
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
}

void Cookie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(rect);
}

void Cookie::Die()
{
	hp = 0;
	isAlive = false;
	Variables::coin += scene->GetCoin();
	Variables::diamond += scene->GetDia();
	map->MoveStop();
  	map->SetGameOver(true);
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

	if (sum < 0)
	{
		hp = 0;
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