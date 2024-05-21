#include "BattleManager.h"
#include "random"
#include "SceneManager.h"
#include "string"

float BattleManager::cardX = 0.2f;
float BattleManager::cardY = 0.3f;

void BattleManager::init()
{
	winMoney = 0;

	lastTimeChoosed_Enemy = Time::GetCurrentTime();
	lastTimeChoosedToAttack_Enemy = Time::GetCurrentTime();

	activeDino = nullptr;
	activeEnemyDino = nullptr;
	lowHPDino = nullptr;

	SettedCards = false;

	inFight = false;

	Entity* back(&Manager::addEntity());
	Entity* nowTurn(&Manager::addEntity());
	
	nowTurnText = nowTurn->AddComponent<UIText>("hero turn", glm::vec2(-0.8f, 0.0f), 0.1f, 0.12f);
	nowTurnText->Disable();

	heroTurn = true;
	srand(time(0));
	
	int n = rand() % 3;
	if (n == 0)
	{
		nowArea = Area::Mountain;
		background = back->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/mountain.jpg", 1.0f, 1.0f);
	}
	else if (n == 1)
	{
		nowArea = Area::River;
		background = back->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/river.jpeg", 1.0f, 1.0f);
	}
	else if (n == 2)
	{
		nowArea = Area::Plain;
		background = back->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/plain.jpg", 1.0f, 1.0f);
	}
	background->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	srand(time(0));

	enemyDinos.push_back(DinoCreator::CreateDEXDino(nowArea));
	enemyDinos.push_back(DinoCreator::CreateINTDino(nowArea));
	enemyDinos.push_back(DinoCreator::CreateSTRDino(nowArea));
} 

void BattleManager::update()
{
	if (!SettedCards)
	{
		SetChooseDino();
	}
	if (enemyDinos.size() == 0 || (toFightDino.size() == 0 && inFight))
	{
		if (toFightDino.size() == 0)
		{
			winMoney = 100;
		}
		SceneManager::LoadScene(1);
	}

	if (!heroTurn)
	{
		nowTurnText->ChangeText("enemy turn");
		EnemyLogic();
	}
	else 
	{
		nowTurnText->ChangeText("hero turn");
	}
}

void BattleManager::draw()
{

}

void BattleManager::EnemyLogic()
{
	activeDino = nullptr;

	//choose attack dino (with max damage)
	if (activeEnemyDino == nullptr)
	{
		lastTimeChoosed_Enemy = Time::GetCurrentTime();
		int m = 0;
		for (auto dino : enemyDinos)
		{
			if (m < dino->GetDamageVal())
			{
				m = dino->GetDamageVal();
				activeEnemyDino = dino;
			}
		}
	}
	Entity* card;
	int ind = std::distance(enemyDinos.begin(), std::find(enemyDinos.begin(), enemyDinos.end(), activeEnemyDino));
	card = cardEnemy[ind];
	UIButton* button = card->GetComponent<UIButton>();
	button->SetColor(glm::vec4(0.6f, 0.1f, 0.1f, 1.0f));

	if (Time::GetCurrentTime() - lastTimeChoosed_Enemy < 2.0f) // some time between
		return;

	//choose hero dino to attack (with the lowest hp)
	if (lowHPDino == nullptr)
	{
		lastTimeChoosedToAttack_Enemy = Time::GetCurrentTime();
		int min = 1 << 30;
		for (auto dino : toFightDino)
		{
			HP* hp = dino->entity->GetComponent<HP>();
			if (min > hp->GetCurrentHP())
			{
				min = hp->GetCurrentHP();
				lowHPDino = dino;
			}
		}
	}

	Entity* cardHero;
	int ind2 = std::distance(toFightDino.begin(), std::find(toFightDino.begin(), toFightDino.end(), lowHPDino));
	cardHero = cardHeroToFight[ind2];
	UIButton* buttonHero = cardHero->GetComponent<UIButton>();
	buttonHero->SetColor(glm::vec4(0.1, 0.6f, 0.1f, 1.0f));

	if (Time::GetCurrentTime() - lastTimeChoosedToAttack_Enemy < 2.0f) //some time between
		return;

	//attack hero
	HP* hp = lowHPDino->entity->GetComponent<HP>();
	hp->GetDamage(activeEnemyDino->GetDamageVal());

	//give turn to hero
	buttonHero->SetColor(glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
	button->SetColor(glm::vec4(1.0, 0.5f, 0.5f, 1.0f));
	heroTurn = true;

	//check death
	if (hp->isDead()) 
	{
		auto it = std::find(toFightDino.begin(), toFightDino.end(), lowHPDino);
		toFightDino.erase(it);

		auto it2 = std::find(cardHeroToFight.begin(), cardHeroToFight.end(), buttonHero->entity);
		cardHeroToFight.erase(it2);
		buttonHero->entity->destroy();

		lowHPDino->entity->destroy();
	}

	//Update text if not dead
	UIText* txt = cardHero->GetComponent<UIText>(); //works because i defined text hp last
	txt->ChangeText("hp " + std::to_string(hp->GetCurrentHP()) );

	lowHPDino = nullptr;
	activeEnemyDino = nullptr;
}

void BattleManager::HeroLogic()
{
	//
}

void BattleManager::StartFight()
{
	inFight = true;

	SetHeroDinos();
	SetEnemyDinos();
}

void BattleManager::SetHeroDinos()
{
	glm::vec2 startCoords = glm::vec2(-0.6f, -0.6f);

	for (auto dino : toFightDino)
	{
		cardHeroToFight.push_back(CreateDinoCardFight(dino, startCoords));
		startCoords.x += 0.6f;
	}
}

void BattleManager::SetEnemyDinos()
{
	glm::vec2 startCoords = glm::vec2(-0.6f, 0.6f);
	for (Dino* dino : enemyDinos)
	{
		cardEnemy.push_back(CreateEnemyDinoCard(dino, startCoords));
		startCoords.x += 0.6f;
	}
}


void BattleManager::SetChooseDino()
{
	Entity* buttonSF(&Manager::addEntity());

	UIButton* buttonStartFight = buttonSF->AddComponent<UIButton>(glm::vec2(0.0f, -0.5f), "res/Textures/button.png", 0.3f, 0.1f);
	
	auto lam = [this, buttonStartFight]()
	{
		for (auto button : cardHero)
		{
			button->destroy();
		}
		buttonStartFight->entity->destroy();
		nowTurnText->Enable();
		this->StartFight();
	};
	buttonStartFight->AddCall(lam);

	SettedCards = true;

	glm::vec2 startCoords = glm::vec2(-0.5f, 0.0f);

	for (auto dino : heroDinos)
	{
		cardHero.push_back(CreateDinoCard(dino, startCoords));
		
		startCoords += glm::vec2(0.5f, 0.0f);
	}
}


Entity* BattleManager::CreateDinoCard(Dino* dino, glm::vec2 pos)
{
	Entity* card(&Manager::addEntity());


	UIText* txt1 = card->AddComponent<UIText>("int " + std::to_string(dino->GetINT()),
		pos + glm::vec2(-cardX, -cardY * (4.0f / 6.0f)),
		0.02f);
	txt1->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt2 = card->AddComponent<UIText>("dex " + std::to_string(dino->GetDEX()),
		pos + glm::vec2(-cardX, -cardY * (5.0f / 6.0f)),
		0.02f);
	txt2->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt3 = card->AddComponent<UIText>("str " + std::to_string(dino->GetSTR()),
		pos + glm::vec2(-cardX, -cardY),
		0.02f);
	txt3->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIButton* button = card->AddComponent<UIButton>(pos + glm::vec2(0.0f, cardY / 4.0f),
		dino->GetTexture(),
		cardX, cardY / 2.0f, true);
	auto lamAddDino = [this, dino, button]()
	{	
		auto it = std::find(toFightDino.begin(), toFightDino.end(), dino);
		auto it2 = std::find(heroDinos.begin(), heroDinos.end(), dino);
		if (it != toFightDino.end() && toFightDino.size() <= 3)
		{
			heroDinos.push_back(dino);
			toFightDino.erase(it);
		}
		else if(toFightDino.size() <= 3)
		{
			heroDinos.erase(it2);
			toFightDino.push_back(dino);
		}
	};
	button->AddCall(lamAddDino);

	return card;
}

Entity* BattleManager::CreateDinoCardFight(Dino* dino, glm::vec2 pos)
{
	Entity* card(&Manager::addEntity());

	HP* curHP = dino->entity->GetComponent<HP>();


	UIText* txt1 = card->AddComponent<UIText>("int " + std::to_string(dino->GetINT()),
		pos + glm::vec2(-cardX, -cardY * (4.0f / 6.0f)),
		0.02f);
	txt1->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt2 = card->AddComponent<UIText>("dex " + std::to_string(dino->GetDEX()),
		pos + glm::vec2(-cardX, -cardY * (5.0f / 6.0f)),
		0.02f);
	txt2->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt3 = card->AddComponent<UIText>("str " + std::to_string(dino->GetSTR()),
		pos + glm::vec2(-cardX, -cardY),
		0.02f);
	txt3->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	std::string txtHP = "hp " + std::to_string(curHP->GetCurrentHP());
	UIText* txt = card->AddComponent<UIText>(txtHP.c_str(), pos + glm::vec2(-cardX, -cardY * (3.0f / 6.0f)), 0.02f);
	txt->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	UIButton* button = card->AddComponent<UIButton>(pos + glm::vec2(0.0f, cardY / 4.0f),
		dino->GetTexture(),
		cardX, cardY / 2.0f);
	
	button->SetColor(glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));

	auto lamAddDino = [this, dino, card, button]()
	{
		if (heroTurn && activeDino != dino)
		{
			activeDino = dino;
			SetOtherCardsUnactive(card);
		}
		else
		{
			activeDino = nullptr;
			button->SetColor(glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
		}
	};
	button->AddCall(lamAddDino);

	return card;
}

Entity* BattleManager::CreateEnemyDinoCard(Dino* dino, glm::vec2 pos)
{
	Entity* card(&Manager::addEntity());
	HP* curHP = dino->entity->GetComponent<HP>();

	std::string txtHP = "hp " + std::to_string(curHP->GetCurrentHP());
	UIText* txt = card->AddComponent<UIText>(txtHP.c_str(), pos + glm::vec2(-cardX, -cardY * (3.0f / 6.0f)), 0.02f);

	UIText* txt1 = card->AddComponent<UIText>("int " + std::to_string(dino->GetINT()),
		pos + glm::vec2(-cardX, -cardY * (4.0f / 6.0f)),
		0.02f);
	txt1->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt2 = card->AddComponent<UIText>("dex " + std::to_string(dino->GetDEX()),
		pos + glm::vec2(-cardX, -cardY * (5.0f / 6.0f)),
		0.02f);
	txt2->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIText* txt3 = card->AddComponent<UIText>("str " + std::to_string(dino->GetSTR()),
		pos + glm::vec2(-cardX, -cardY),
		0.02f);
	txt3->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	UIButton* button = card->AddComponent<UIButton>(pos + glm::vec2(0.0f, cardY / 4.0f),
		dino->GetTexture(),
		cardX, cardY / 2.0f);

	button->SetColor(glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));




	auto lamAddDino = [this, dino, card, button, txt]()
	{
		if (activeDino != nullptr && heroTurn)
		{
			HP* dinoHP = dino->entity->GetComponent<HP>();
			dinoHP->GetDamage(activeDino->GetDamageVal());

			std::string txtHP = "hp " + std::to_string(dinoHP->GetCurrentHP());
			txt->ChangeText(txtHP.c_str());

			heroTurn = false;
			SetAllCardUnactive();
			if (dinoHP->isDead())
			{
				winMoney += dino->GetPrice();

				auto it = std::find(cardEnemy.begin(), cardEnemy.end(), card);
				cardEnemy.erase(it);
				card->destroy();

				auto it2 = std::find(enemyDinos.begin(), enemyDinos.end(), dino);
				enemyDinos.erase(it2);
				dino->entity->destroy();
			}
		}
	};
	button->AddCall(lamAddDino);


	return card;
}

void BattleManager::SaveData()
{
	std::ofstream out;
	out.open(SaveManager::nameOfFile, std::ofstream::out);

	std::string changes = "";
	if (out.is_open())
	{
		for (auto dino : heroDinos)
		{
			changes += "D: " + dino->GetSaveLog() + "\n";
		}
		for (auto dino : toFightDino)
		{
			changes += "D: " + dino->GetSaveLog() + "\n";
		}

		changes += "M: " + std::to_string(winMoney) + "\n";
		out << changes;
	}

	out.close();
}

void BattleManager::LoadData()
{
	std::string line;
	std::ifstream in(SaveManager::nameOfFile);


	if (in.is_open())
	{
		std::string aa;
		DinoType dinoType;
		int dex;
		int intt;
		int str;

		Dino* dino;
		std::vector<std::string> stats;
		while (std::getline(in, line))
		{
			switch (line[0])
			{
			case 'D':
				stats = Func::SplitLine(line);
				str = std::atoi(stats[1].c_str());
				dex = std::atoi(stats[2].c_str());
				intt = std::atoi(stats[3].c_str());

				dino = DinoCreator::CreateDino(str, dex, intt, nowArea);
				
				heroDinos.push_back(dino);
				break;
			default:
				break;
			}
		}
	}

	in.close();
}

void BattleManager::SetOtherCardsUnactive(Entity* button)
{
	for (auto cur_button : cardHeroToFight)
	{
		UIButton* buttonUI = cur_button->GetComponent<UIButton>();
		if (cur_button == button)
		{
			buttonUI->SetColor(glm::vec4(0.1, 0.6f, 0.1f, 1.0f));
			continue;
		}
			
		buttonUI->SetColor(glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
	}
}
void BattleManager::SetAllCardUnactive()
{
	for (auto cur_button : cardHeroToFight)
	{
		UIButton* buttonUI = cur_button->GetComponent<UIButton>();

		buttonUI->SetColor(glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
	}
}
BattleManager::~BattleManager()
{
	for (auto dino : heroDinos)
	{
		dino->entity->destroy();
	}
	for (auto card : cardHeroToFight)
	{
		card->destroy();
	}
	for (auto dino : enemyDinos)
	{
		dino->entity->destroy();
	}
	for (auto card : cardEnemy)
	{
		card->destroy();
	}

	heroDinos.clear();
	cardHero.clear();
	toFightDino.clear();
	cardHeroToFight.clear();
	enemyDinos.clear();
	cardEnemy.clear();

	nowTurnText->entity->destroy();
	background->entity->destroy();
}