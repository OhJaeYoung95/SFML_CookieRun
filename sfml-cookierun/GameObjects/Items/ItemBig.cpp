#include "stdafx.h"
#include "ItemBig.h"
#include "ResourceMgr.h"

ItemBig::ItemBig(const std::string& textureId, const std::string& n)
	: Item(textureId, n)
{

}

ItemBig::~ItemBig()
{

}

void ItemBig::Init()
{
	Item::Init();
}

void ItemBig::Release()
{
	Item::Release();

}

void ItemBig::Reset()
{
	Item::Reset();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Item/ItemBig/ItemBig.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sortLayer = 5;
	animation.Play("ItemBig");

}

void ItemBig::Update(float dt)
{
	Item::Update(dt);
	animation.Update(dt);
}

void ItemBig::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);

}
