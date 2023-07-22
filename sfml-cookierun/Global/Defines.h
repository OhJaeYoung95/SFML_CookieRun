#pragma once

#define _USE_MATH_DEFINES

enum class CookieTypes
{
	None = -1,
	Pancake,
	Pirate,
	Moonlighter,
};

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
	AnimationSheetClip,
};

enum class SceneId
{
	None = -1,
	Title,
	Editor,
	Lobby,
	Game,
	Count,
};

#include "AnimationClip.h"