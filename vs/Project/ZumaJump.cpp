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
	//set Logo
	logoTexture = new Texture("logo.png");
	logoSprite = new Sprite(logoTexture, defaultSpriteShader, defaultQuad);
	logoSprite->SetNumXFrames(1);
	logoSprite->SetNumYFrames(1);
	logoSprite->AddAnimation("logo", 0, 0);
	logoSprite->PlayAnim("logo");
	logoSprite->SetPosition(((setting->screenWidth / 2) - 85), 400);
	logoSprite->SetScale(0.4);

	//add button texture
	buttonTexture = new Texture("button.png");

	//set button play
	playSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	playSprite->SetNumXFrames(4);
	playSprite->SetNumYFrames(1);
	playSprite->AddAnimation("play-normal", 2, 2);
	playSprite->AddAnimation("play-hover", 2, 3);
	playSprite->PlayAnim("play-hover");
	playSprite->SetPosition(((setting->screenWidth / 2) - 100), 300);
	playSprite->SetScale(0.3);
	playSprite->SetAnimationDuration(500);

	//set button exit
	exitSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(4);
	exitSprite->SetNumYFrames(1);
	exitSprite->AddAnimation("exit-normal", 0, 0);
	exitSprite->AddAnimation("exit-hover", 0, 1);
	exitSprite->PlayAnim("exit-normal");
	exitSprite->SetPosition(((setting->screenWidth / 2) - 100), 200);
	exitSprite->SetScale(0.3);
	exitSprite->SetAnimationDuration(500);

	//set forest ground
	forestTexture = new Texture("forest_ground.png");
	forestSprite = new Sprite(forestTexture, defaultSpriteShader, defaultQuad);
	forestSprite->SetPosition(0, 0);
	forestSprite->SetScale(0.7);
	forestSprite->SetNumXFrames(1);
	forestSprite->SetNumYFrames(1);

	//set obstacle
	obstacleTexture = new Texture("obstacle_wood.png");
	obstacleSprite = new Sprite(obstacleTexture, defaultSpriteShader, defaultQuad);
	obstacleSprite->SetPosition(1030, 50);
	obstacleSprite->SetScale(1);
	obstacleSprite->SetNumXFrames(4);
	obstacleSprite->SetNumYFrames(1);
	obstacleSprite->AddAnimation("obstacle-move", 0, 3);
	obstacleSprite->PlayAnim("obstacle-move");
	obstacleSprite->SetAnimationDuration(500);

	//set coin
	coinTexture = new Texture("coin.png");
	coinSprite = new Sprite(coinTexture, defaultSpriteShader, defaultQuad);
	coinSprite->SetPosition(950, 120);
	//coinSprite->SetPosition((obstacleSprite->GetPosition().x + 30), 120);
	coinSprite->SetScale(0.2);
	coinSprite->SetNumXFrames(1);
	coinSprite->SetNumYFrames(1);
	coinSprite->AddAnimation("coin", 0, 0);
	coinSprite->PlayAnim("coin");

	//set tree
	treeTexture = new Texture("tree.png");
	treeSprite = new Sprite(treeTexture, defaultSpriteShader, defaultQuad);
	treeSprite->SetPosition(1030, 90);
	treeSprite->SetScale(2.0);
	treeSprite->SetNumXFrames(1);
	treeSprite->SetNumYFrames(1);
	treeSprite->AddAnimation("tree-move", 0, 0);
	treeSprite->PlayAnim("tree-move");
	treeSprite->SetAnimationDuration(100);

	//set frog character
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
	
	//set bounding box
	charSprite->SetBoundingBoxSize(charSprite->GetScaleWidth() - (16 * charSprite->GetScale()),
		charSprite->GetScaleHeight() - (4 * charSprite->GetScale()));

	//add input mapping 
	inputManager->AddInputMapping("Jump", SDLK_w);
	inputManager->AddInputMapping("Menu Move Up", SDLK_UP);
	inputManager->AddInputMapping("Menu Move Down", SDLK_DOWN);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
	inputManager->AddInputMapping("enter", SDLK_RETURN);

	// Playing music
	music = new Music("cuddle.ogg");
	music->SetVolume(30);
	music->Play(true);

	playButtonIsSelected = true;
	exitButtonIsSelected = false;

	scoreText = new Text("lucon.ttf", 14, defaultTextShader);
	scoreText->SetScale(1.0f);
	scoreText->SetColor(255, 255, 255);
	scoreText->SetPosition((setting->screenWidth - 100), 575);
	//scoreText->SetPosition(875, 575);
}

void ZumaJump::Update()
{	

	vec2 playerPos = charSprite->GetPosition();
	
	float obstacleSpritex = obstacleSprite->GetPosition().x;
	float obstacleSpritey = obstacleSprite->GetPosition().y;

	float coinSpritex = coinSprite->GetPosition().x;
	float coinSpritey = coinSprite->GetPosition().y;

	float charSpritex = charSprite->GetPosition().x;
	float charSpritey = charSprite->GetPosition().y;

	float treeSpritex =treeSprite->GetPosition().x;
	float treeSpritey =treeSprite->GetPosition().y;

	// Set ground position
	float static groundPos = playerPos.y;

	//set state button
	/*if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}*/

	charSprite->PlayAnim("run");
	obstacleSprite->PlayAnim("obstacle-move");
	if (inputManager->IsKeyReleased("Jump")) {
		yspeed = 200.0f;
		bool flip = charSprite->GetFlipHorizontal();

		charSprite->SetPosition(playerPos.x,
			playerPos.y + yspeed + gravity * GetGameTime());
	}

	//set state button main menu
	if (inputManager->IsKeyReleased("Menu Move Up")) {
		playSprite->PlayAnim("play-hover");
		exitSprite->PlayAnim("exit-normal");
		playButtonIsSelected = true;
		exitButtonIsSelected = false;
	}
	if (inputManager->IsKeyReleased("enter")) {
		if (playButtonIsSelected && exitButtonIsSelected == false) {
			inGame = true;
		}
		else {
			inGame = false;
			state = State::EXIT;
			return;
		}
	}

	if (inputManager->IsKeyReleased("Menu Move Down")) {
		exitSprite->PlayAnim("exit-hover");
		playSprite->PlayAnim("play-normal");
		exitButtonIsSelected = true;
		playButtonIsSelected = false;
		if (inputManager->IsKeyReleased("enter")) {
			state = State::EXIT;
			return;
		}
	}

	//set state obstacle
	if (collidedLeft == false) {
		float velocity = -0.5f;

		obstacleSpritex += velocity * GetGameTime();

		obstacleSprite->SetPosition(obstacleSpritex, obstacleSpritey);

		if (obstacleSpritex <= -200) {
			collidedLeft = true;
		}
	}
	else {
		
		obstacleSprite->SetPosition(1030, 50);
		obstacleSprite->PlayAnim("obstacle-move");
		collidedLeft = false;
	}

	//set state coin
	if (coinCollidedLeft == false) {
		float velocity = -0.5f;

		coinSpritex += velocity * GetGameTime();

		coinSprite->SetPosition(coinSpritex, coinSpritey);

		if (coinSpritex <= -200) {
			coinCollidedLeft = true;
		}
	}
	else {

		coinSprite->SetPosition(950, 120);
		//coinSprite->SetPosition((obstacleSprite->GetPosition().x - 40), 120);
		coinSprite->PlayAnim("coin");
		coinCollidedLeft = false;
	}
	
	//set state tree
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

	// Set frog back to ground after jumping
	if (playerPos.y > groundPos) {
		if (counter >= 1000) {
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

	//score
	scoreText->SetText("Score: " + to_string(score++));

	// Update sprite animation
	charSprite->Update(GetGameTime());
	forestSprite->Update(GetGameTime());
	obstacleSprite->Update(GetGameTime());
	coinSprite->Update(GetGameTime());
	treeSprite->Update(GetGameTime());
	playSprite->Update(GetGameTime());
	exitSprite->Update(GetGameTime());
	logoSprite->Update(GetGameTime());

	for (int i = 0; i < 7; i++) {
		if (obstacleSprite->GetBoundingBox()->CollideWith(charSprite->GetBoundingBox())) {
			inGame = false;
		}
	}
}

void ZumaJump::Render()
{
	if (inGame) {
		treeSprite->Draw();
		obstacleSprite->Draw();
		coinSprite->Draw();
		forestSprite->Draw();
		charSprite->Draw();
		scoreText->Draw();
		if (inputManager->IsKeyReleased("Quit")) {
			inGame = false;
			return;
		}
	}
	else {
		logoSprite->Draw();
		exitSprite->Draw();
		playSprite->Draw();
	}	
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
