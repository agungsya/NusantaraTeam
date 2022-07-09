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
		Texture* charTexture = NULL;
		Sprite* charSprite = NULL;
		float yspeed = 0;
		float xspeed = 0;
		float gravity = 0.06;

		Texture* forestTexture = NULL;
		Sprite* forestSprite = NULL;
		Texture* obstacleTexture = NULL;
		Sprite* obstacleSprite = NULL;

		Texture* treeTexture = NULL;
		Sprite* treeSprite = NULL;

		Texture* logoTexture = NULL;
		Sprite* logoSprite = NULL;

		Texture* buttonTexture = NULL;
		Sprite* playSprite = NULL;
		Sprite* exitSprite = NULL;

		Music* music = NULL;;

		bool collidedLeft = false;
		bool treeCollidedLeft = false;
		bool inGame = false;
		bool playButtonIsSelected = false;
		bool exitButtonIsSelected = false;

		float counter = 0;
	};
}
#endif
