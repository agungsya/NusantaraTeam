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

	obstacleTexture = new Texture("plant.png");
	obstacleSprite = new Sprite(obstacleTexture, defaultSpriteShader, defaultQuad);
	obstacleSprite->SetPosition(1030, 100);
	obstacleSprite->SetScale(0.2);
	obstacleSprite->SetNumXFrames(31);
	obstacleSprite->SetNumYFrames(1);
	obstacleSprite->AddAnimation("obstacle-move", 0, 30);
	obstacleSprite->PlayAnim("obstacle-move");
	obstacleSprite->SetAnimationDuration(150);

	treeTexture = new Texture("tree.png");
	treeSprite = new Sprite(treeTexture, defaultSpriteShader, defaultQuad);
	treeSprite->SetPosition(1030, 90);
	treeSprite->SetScale(2.0);
	treeSprite->SetNumXFrames(1);
	treeSprite->SetNumYFrames(1);
	treeSprite->AddAnimation("tree-move", 0, 0);
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

	vec2 playerPos = charSprite->GetPosition();
	
	float obstacleSpritex = obstacleSprite->GetPosition().x;
	float obstacleSpritey = obstacleSprite->GetPosition().y;

	float charSpritex = charSprite->GetPosition().x;
	float charSpritey = charSprite->GetPosition().y;

	float treeSpritex =treeSprite->GetPosition().x;
	float treeSpritey =treeSprite->GetPosition().y;

	// Set ground position
	float static groundPos = playerPos.y;

	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}
	charSprite->PlayAnim("run");
	obstacleSprite->PlayAnim("obstacle-move");
	if (inputManager->IsKeyPressed("Move Up")) {
		yspeed = 200.0f;
		bool flip = charSprite->GetFlipHorizontal();

		charSprite->SetPosition(playerPos.x,
			playerPos.y + yspeed + gravity * GetGameTime());
	
		
	}

	if (collidedLeft == false) {
		float velocity = -0.5f;

		obstacleSpritex += velocity * GetGameTime();


		obstacleSprite->SetPosition(obstacleSpritex, obstacleSpritey);


		if (obstacleSpritex <= -200) {
			collidedLeft = true;
		}
	}
	else {
		
		obstacleSprite->SetPosition(1030, 100);
		obstacleSprite->PlayAnim("obstacle-move");
		collidedLeft = false;
	}
	
	if (treeCollidedLeft == false) {
		float velocity = -0.2f;

		treeSpritex += velocity * GetGameTime();


		treeSprite->SetPosition(treeSpritex, treeSpritey);


		if (treeSpritex <= -400) {
			treeCollidedLeft = true;
		}
	}
	else {

		treeSprite->SetPosition(1030, 90);
		treeSprite->PlayAnim("tree-move");
		treeCollidedLeft = false;
	}

	charSprite->Update(GetGameTime());
	forestSprite->Update(GetGameTime());
	obstacleSprite->Update(GetGameTime());
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
		if (counter >= 500) {
			playerPos.y = groundPos;
			charSprite->SetPosition(playerPos.x,
				playerPos.y);
			counter = 0;
		}
		else {
			counter++;
			charSprite->SetPosition(playerPos.x,
				playerPos.y);
		}
	}
}

void ZumaJump::Render()
{
	treeSprite->Draw();
	obstacleSprite->Draw();
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
