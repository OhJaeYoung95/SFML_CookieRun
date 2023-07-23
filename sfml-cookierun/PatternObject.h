#pragma once
#include "UIButton.h"
class PatternObject : public UIButton
{
protected:
	ObjectType type = ObjectType::None;

public:
	PatternObject(const std::string& textureId = "", const std::string& n = "");
	virtual ~PatternObject() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

