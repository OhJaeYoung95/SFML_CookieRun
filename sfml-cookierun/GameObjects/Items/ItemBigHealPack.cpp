#include "stdafx.h"
#include "ItemBigHealPack.h"
#include "ResourceMgr.h"

ItemBigHealPack::ItemBigHealPack(const std::string& textureId, const std::string& n)
	: Item(textureId, n)
{
}

ItemBigHealPack::~ItemBigHealPack()
{
}

void ItemBigHealPack::Init()
{
	Item::Init();

}

void ItemBigHealPack::Release()
{
	Item::Release();

}

void ItemBigHealPack::Reset()
{
	Item::Reset();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Item/ItemBigHealPack/ItemBigHealPack.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sortLayer = 5;
	animation.Play("ItemBigHealPack");
}

void ItemBigHealPack::Update(float dt)
{
	Item::Update(dt);
	animation.Update(dt);
}

void ItemBigHealPack::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);

}
