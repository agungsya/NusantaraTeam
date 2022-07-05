#ifndef ZUMAJUMP_H
#define ZUMAJUMP_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"

namespace Engine {
	class ZumaJump :
		public Engine::Game
	{
	public:
		ZumaJump(Setting* setting);
		~ZumaJump();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		/*Texture* crateTexture = NULL;
		Texture* monsterTexture = NULL;
		Texture* dotTexture = NULL;
		Sprite* crateSprite = NULL;
		Sprite* crateSprite2 = NULL;
		Sprite* monsterSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Music* music = NULL;;
		Sound* sound = NULL;
		Text* text = NULL;*/
		Texture* charTexture = NULL;
		Sprite* charSprite = NULL;
		float yspeed = 0;
		float xspeed = 0;
		float gravity = 0.1;
	};
}
#endif
