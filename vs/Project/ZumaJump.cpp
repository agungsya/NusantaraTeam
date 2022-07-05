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
	forestTexture = new Texture("forest_ground.png");
	forestSprite = new Sprite(forestTexture, defaultSpriteShader, defaultQuad);
	forestSprite->SetPosition(0, 0);
	forestSprite->SetScale(0.7);
	forestSprite->SetNumXFrames(1);
	forestSprite->SetNumYFrames(1);

	treeTexture = new Texture("forest_hill.png");
	treeSprite = new Sprite(treeTexture, defaultSpriteShader, defaultQuad);
	treeSprite->SetPosition(0, 0);
	treeSprite->SetScale(0.6);
	treeSprite->SetNumXFrames(1);
	treeSprite->SetNumYFrames(2);
	treeSprite->AddAnimation("tree-move", 0, 1);
	treeSprite->PlayAnim("tree-move");
	treeSprite->SetAnimationDuration(100);

	charTexture = new Texture("frog.png");
	charSprite = new Sprite(charTexture, defaultSpriteShader, defaultQuad);
	charSprite->SetPosition(20, 100);
	
	charSprite->SetScale(7);
	charSprite->SetFlipVertical(false);

	charSprite->SetNumXFrames(11);
	charSprite->SetNumYFrames(9);
	charSprite->AddAnimation("run", 11, 21);
	charSprite->AddAnimation("idle", 0, 7);
	charSprite->PlayAnim("run");
	charSprite->SetAnimationDuration(150);

	charSprite->SetBoundingBoxSize(charSprite->GetScaleWidth() - (16 * charSprite->GetScale()),
		charSprite->GetScaleHeight() - (4 * charSprite->GetScale()));

	inputManager->AddInputMapping("Move Up", SDLK_w);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
}

void ZumaJump::Update()
{	

	// Move player sprite using keyboard
	vec2 playerPos = charSprite->GetPosition();

	// Set ground position
	float static groundPos = playerPos.y;

	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}
	charSprite->PlayAnim("run");
	treeSprite->PlayAnim("tree-move");
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
	forestSprite->Update(GetGameTime());
	treeSprite->Update(GetGameTime());

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
	treeSprite->Draw();
	forestSprite->Draw();
	
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
