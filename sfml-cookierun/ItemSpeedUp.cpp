#include "stdafx.h"
#include "ItemSpeedUp.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Map.h"

ItemSpeedUp::ItemSpeedUp(const std::string& textureId, const std::string& n)
	: Item(textureId, n)
{
}

ItemSpeedUp::~ItemSpeedUp()
{
}

void ItemSpeedUp::Init()
{
	Item::Init();
}

void ItemSpeedUp::Release()
{
	Item::Release();

}

void ItemSpeedUp::Reset()
{
	Item::Reset();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Item/ItemSpeedUp/ItemSpeedUp.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sortLayer = 5;
	animation.Play("ItemSpeedUp");
}

void ItemSpeedUp::Update(float dt)
{
	Item::Update(dt);
	if (IsColPlayer())
	{
		// 쿠키 효과 이속증가 => 맵 이동속도 증가
		// 아이템 사라짐
		scene->RemoveGo(this);
	}
	animation.Update(dt);
}

void ItemSpeedUp::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);

}
