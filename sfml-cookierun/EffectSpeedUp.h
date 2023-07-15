#pragma once
#include "SpriteEffect.h"
#include "AnimationController.h"
class EffectSpeedUp : public SpriteEffect
{
protected:
	AnimationController animation;
private:
	EffectSpeedUp(const std::string& textureId = "", const std::string& n = "");
	virtual ~EffectSpeedUp() override { };

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

