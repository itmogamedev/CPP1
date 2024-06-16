#include "Graphics.h"

Graphics::Graphics()
{
	font.loadFromFile("CyrilicOld.ttf");

	punchSound.openFromFile("punchSound.mp3");
	deathSound.openFromFile("deathSound.mp3");

	SetText(playerHPText, "", 50, Color::White, 410, 800);
	SetText(enemyHPText, "", 50, Color::White, 1250, 800);

	SetText(battleLocationText, "", 50, Color::White, 270, 50);
	SetText(enemyDinosCountText, "", 50, Color::White, 270, 150);
	SetText(chooseYourDinosText, "Choose your dinos:", 50, Color::White, 1070, 50);
	SetText(playerMoneyShopText, "", 50, Color::Black, 800, 170);

	SetText(yourDinosText, "Your dinos: ", 50, Color::Black, 270, 50);
	SetText(dinosListText, "", 50, Color::Black, 270, 150);
	SetText(dinosListBattleText, "", 50, Color::White, 1070, 150);
	
	for (int i = 0; i < 15; ++i)
	{
		selectedDinos[i] = false;
	}

	for (int i = 0; i < 15; ++i)
	{
		SetImage(selectDinoButton[i], selectDinoButtonTexture, "images/selectDinoButton.png", 0.4f, 0.4f, 1470, 165 + 45 * i);
	}
	unselectDinoButtonTexture.loadFromFile("images/unselectDinoButton.png");

	for (int i = 0; i < 5; ++i)
	{
		dinoTexture[i].loadFromFile("images/dino" + std::to_string(i + 1) + ".png");
	}

	for (int i = 0; i < 6; ++i)
	{
		SetImage(getDamageSprite[i], getDamageTexture, "images/getDamageEffect.png", 0.1f, 0.1f, 0, 0);
	}

	for (int i = 0; i < 10; ++i)
	{
		SetImage(damageSprite[i], damageTexture, "images/damageSprite.png", 0.3f, 0.3f, 0, 0);
	}

	damageSprite[0].setPosition(300, 500);
	damageSprite[1].setPosition(300, 550);
	damageSprite[2].setPosition(450, 400);
	damageSprite[3].setPosition(400, 450);
	damageSprite[4].setPosition(500, 450);
	damageSprite[5].setPosition(1350, 500);
	damageSprite[6].setPosition(1300, 450);
	damageSprite[7].setPosition(1200, 550);
	damageSprite[8].setPosition(1250, 450);
	damageSprite[9].setPosition(1350, 400);

	getDamageSprite[0].setPosition(300, 400);
	getDamageSprite[1].setPosition(400, 600);
	getDamageSprite[2].setPosition(450, 500);
	getDamageSprite[3].setPosition(1200, 500);
	getDamageSprite[4].setPosition(1300, 450);
	getDamageSprite[5].setPosition(1350, 400);

	SetImage(startBattleButton, battleButtonTexture, "images/startBattleButton.png", 0.8f, 0.8f, 1400, 800);

	SetText(enemy1DinoText, "", 50, Color::White, 270, 250);
	SetText(enemy2DinoText, "", 50, Color::White, 270, 350);
	SetText(enemy3DinoText, "", 50, Color::White, 270, 450);

	SetText(winText, "You won!  +500 money", 100, Color::Cyan, 400, 400);
	SetText(loseText, "You lost!", 100, Color::Red, 600, 400);
	SetText(drawText, "Draw!", 100, Color::Yellow, 800, 400);

	SetImage(dino1BuySprite, dino1BuyTexture, "images/dino1Buy.png", 0.4f, 0.4f, 200, 300);
	SetImage(dino2BuySprite, dino2BuyTexture, "images/dino2Buy.png", 0.4f, 0.4f, 500, 300);
	SetImage(dino3BuySprite, dino3BuyTexture, "images/dino3Buy.png", 0.4f, 0.4f, 800, 300);
	SetImage(dino4BuySprite, dino4BuyTexture, "images/dino4Buy.png", 0.4f, 0.4f, 1100, 300);
	SetImage(dino5BuySprite, dino5BuyTexture, "images/dino5Buy.png", 0.4f, 0.4f, 1400, 300);

	SetImage(plainBGSprite, plainBGTexture, "images/plainBG.png", 1.0f, 1.0f, 0, 0);
	SetImage(mountainBGSprite, mountainBGTexture, "images/mountainBG.png", 1.0f, 1.0f, 0, 0);
	SetImage(riverBGSprite, riverBGTexture, "images/riverBG.png", 1.0f, 1.0f, 0, 0);

	SetImage(mainMenuBackgroundSprite, mainMenuBackgroundTexture, "images/image1.jpg", 1.0f, 1.0f, 0, 0);
	SetImage(battleBackgroundSprite, battleBackgroundTexture, "images/image3.jpg", 1.0f, 1.0f, 0, 0);
	SetImage(shopMenuBackgroundSprite, shopMenuBackgroundTexture, "images/image2.jpg", 1.0f, 1.0f, 0, 0);

	SetImage(buy1Button, buyButton, "images/buyButton.png", 0.4f, 0.4f, 200, 700);
	SetImage(buy2Button, buyButton, "images/buyButton.png", 0.4f, 0.4f, 500, 700);
	SetImage(buy3Button, buyButton, "images/buyButton.png", 0.4f, 0.4f, 800, 700);
	SetImage(buy4Button, buyButton, "images/buyButton.png", 0.4f, 0.4f, 1100, 700);
	SetImage(buy5Button, buyButton, "images/buyButton.png", 0.4f, 0.4f, 1400, 700);

	SetImage(battleButton, battleButtonTexture, "images/startBattleButton.png", 1.0f, 1.0f, 710, 190);
	SetImage(shopButton, shopButtonTexture, "images/dinoShopButton.png", 1.0f, 1.0f, 710, 390);
	SetImage(dinoListButton, dinoListButtonTexture, "images/dinoListButton.png", 1.0f, 1.0f, 710, 590);
	SetImage(quitButton, quitButtonTexture, "images/exitGameButton.png", 1.0f, 1.0f, 710, 790);
	SetImage(backToMainMenuButton, backToMainMenuButtonTexture, "images/backToMenuButton.png", 0.5f, 0.5f, 1650, 50);
}