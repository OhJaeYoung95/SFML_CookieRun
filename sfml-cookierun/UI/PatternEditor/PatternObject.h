#pragma once
#include "UIButton.h"
class PatternObject : public UIButton
{
protected:
	PatternObjectType type = PatternObjectType::None;

public:
	PatternObject(const std::string& textureId = "", const std::string& n = "");
	virtual ~PatternObject() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	PatternObjectType GetType() { return type; }
	void SetType(PatternObjectType type) { this->type = type; }
};

