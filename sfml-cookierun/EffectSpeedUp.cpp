#include "stdafx.h"
#include "EffectSpeedUp.h"
#include "ResourceMgr.h"

EffectSpeedUp::EffectSpeedUp(const std::string& textureId, const std::string& n)
{
}

void EffectSpeedUp::Init()
{
	SpriteEffect::Init();
}

void EffectSpeedUp::Reset()
{
	SpriteEffect::Reset();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Effect/EffectSpeedUp.csv"));
	animation.SetTarget(&sprite);
}

void EffectSpeedUp::Update(float dt)
{
	SpriteEffect::Update(dt);

}
