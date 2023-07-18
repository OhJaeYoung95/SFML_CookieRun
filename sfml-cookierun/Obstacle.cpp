#include "stdafx.h"
#include "Obstacle.h"
#include "Cookie.h"
#include "Scene.h"
#include "SceneGame.h"
#include "ResourceMgr.h"

Obstacle::Obstacle(ObstacleType _type, const std::string& textureId, const std::string& n)
    : SpriteGo(textureId, n), type(_type)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init()
{
    SpriteGo::Init();
    switch (type)
    {
    case ObstacleType::Up:
        SetOrigin(Origins::TC);
        break;

    case ObstacleType::Down:
        SetOrigin(Origins::BC);
        break;
    }

}

void Obstacle::Release()
{
    SpriteGo::Release();

}

void Obstacle::Reset()
{
    SpriteGo::Reset();
    animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Stage1/Obstacle/Pillar.csv"));
    animation.SetTarget(&sprite);

    switch (type)
    {
    case ObstacleType::Up:
        SetOrigin(Origins::TC);
        break;

    case ObstacleType::Down:
        SetOrigin(Origins::BC);
        break;
    }
    sortLayer = 0;
    animation.Play("Pillar");
}

void Obstacle::Update(float dt)
{
    SpriteGo::Update(dt);

    if (IsColPlayer() && !cookie->GetIsHit())
    {
        cookie->SetIsHit(true);
    }

    animation.Update(dt);
}

void Obstacle::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);

}

void Obstacle::SetCookie(Cookie*& cookie)
{
    this->cookie = cookie;
}

bool Obstacle::IsColPlayer()
{
    return sprite.getGlobalBounds().intersects(cookie->rect.getGlobalBounds());
}

void Obstacle::SetScene(SceneGame* scene)
{
    this->scene = scene;

}

void Obstacle::SetMap(Map* map)
{
    this->map = map;

}
