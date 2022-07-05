#include "ZumaJump.h"

using namespace Engine;

ZumaJump::ZumaJump(Setting* setting) :Game(setting)
{

}


ZumaJump::~ZumaJump()
{
	
}

void ZumaJump::Init()
{
	charTexture = new Texture("frog.png");
	charSprite = new Sprite(charTexture, defaultSpriteShader, defaultQuad);
	charSprite->SetPosition((setting->screenWidth * 0.5f) - (charSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (charSprite->GetScaleHeight() * 0.5f));
	charSprite->SetPosition(0, 0);
	//charSprite->SetRotation(0);
	charSprite->SetScale(10);
	charSprite->SetFlipVertical(false);

	charSprite->SetNumXFrames(11);
	charSprite->SetNumYFrames(9);
	charSprite->AddAnimation("run", 11, 21);
	charSprite->AddAnimation("idle", 0, 7);
	charSprite->PlayAnim("run");
	charSprite->SetAnimationDuration(150);

	inputManager->AddInputMapping("Move Up", SDLK_w);

	SetBackgroundColor(23, 23, 23);

}

void ZumaJump::Update()
{	

	// Move player sprite using keyboard
	vec2 playerPos = charSprite->GetPosition();

	// Set ground position
	float static groundPos = playerPos.y;


	charSprite->PlayAnim("run");
	if (inputManager->IsKeyPressed("Move Up")) {
		yspeed = 200.0f;
		/*charSprite->SetPosition(charSprite->GetPosition().x + xspeed * GetGameTime(),
			charSprite->GetPosition().y + yspeed * GetGameTime());
		charSprite->PlayAnim("idle");
		if (charSprite->GetPosition().x == charSprite->GetPosition().x + xspeed * GetGameTime() && charSprite->GetPosition().y == charSprite->GetPosition().y + yspeed * GetGameTime()) {
			charSprite->SetPosition(0, 0);
		}*/
		bool flip = charSprite->GetFlipHorizontal();

		charSprite->SetPosition(playerPos.x,
			playerPos.y + yspeed + gravity * GetGameTime());
	}


	charSprite->Update(GetGameTime());

	// Move player to right side after moving out the left screen
	if (playerPos.x < 0) {
		charSprite->SetPosition(setting->screenWidth - charSprite->GetScaleWidth(),
			playerPos.y);
	}

	// Move player to left side  after moving out the right screen
	if (playerPos.x > setting->screenWidth - charSprite->GetScaleWidth()) {
		charSprite->SetPosition(0,
			playerPos.y);
	}

	// Set Player back to ground after jumping
	if (playerPos.y > groundPos) {
		SDL_Delay(100);
		playerPos.y = groundPos;
		charSprite->SetPosition(playerPos.x,
			playerPos.y);
	}
}

void ZumaJump::Render()
{
	charSprite->Draw();
}


int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Project Example";
	setting->screenWidth = 1024;
	setting->screenHeight = 600;
	setting->windowFlag = WindowFlag::WINDOWED;
	Game* game = new ZumaJump(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
