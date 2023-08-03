#include "stdafx.h"
#include "PatternObject.h"

PatternObject::PatternObject(const std::string& textureId, const std::string& n)
	: UIButton(textureId, n)
{
}

PatternObject::~PatternObject()
{
}

void PatternObject::Init()
{
	UIButton::Init();
}

void PatternObject::Release()
{
	UIButton::Release();

}

void PatternObject::Reset()
{
	UIButton::Reset();

}

void PatternObject::Update(float dt)
{
	UIButton::Update(dt);

}

void PatternObject::Draw(sf::RenderWindow& window)
{
	UIButton::Draw(window);

}
