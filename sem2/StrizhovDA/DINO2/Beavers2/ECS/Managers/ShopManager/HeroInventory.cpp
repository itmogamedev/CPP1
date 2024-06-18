#include "HeroInventory.h"
#include "fstream"
#include "Funcs.h"

std::vector<Dino*> HeroInventory::dinos;
float HeroInventory::cardX = 0.1f;
float HeroInventory::cardY = 0.2f;

glm::vec2 HeroInventory::startCoords;
int HeroInventory::nowMoney;
std::vector<Entity*> HeroInventory::buttons;

HeroInventory::HeroInventory(bool inShopState)
{
	inShop = inShopState;
	
}

void HeroInventory::init()
{
	startCoords = glm::vec2(-0.5f, -0.5f);

	nowMoney = 300;

	Entity* entity(&Manager::addEntity());

	moneyCount = entity->AddComponent<UIText>("money " + std::to_string(nowMoney), glm::vec2(0.6f, 0.9f), 0.02f);
}

void HeroInventory::draw()
{
	moneyCount->ChangeText("money " + std::to_string(nowMoney));
}

void HeroInventory::AddDino(Dino* dino)
{
	dinos.push_back(dino);
	buttons.push_back(CreateDinoCard(*dino, startCoords));

	startCoords += glm::vec2(cardX * 2 + 0.2f, 0.0f);
}

Entity* HeroInventory::CreateDinoCard(Dino& dino, glm::vec2 pos)
{
	Entity* card(&Manager::addEntity());

	card->AddComponent<UIText>("price " + std::to_string(dino.GetPrice()),
		pos + glm::vec2(-cardX, -cardY * (3.0f / 6.0f)),
		0.02f);

	card->AddComponent<UIText>("int " + std::to_string(dino.GetINT()),
		pos + glm::vec2(-cardX, -cardY * (4.0f / 6.0f)),
		0.02f);

	card->AddComponent<UIText>("dex " + std::to_string(dino.GetDEX()),
		pos + glm::vec2(-cardX, -cardY * (5.0f / 6.0f)),
		0.02f);

	card->AddComponent<UIText>("str " + std::to_string(dino.GetSTR()),
		pos + glm::vec2(-cardX, -cardY),
		0.02f);



	UIButton* button = card->AddComponent<UIButton>(pos + glm::vec2(0.0f, cardY / 4.0f),
		dino.GetTexture(),
		cardX, cardY / 2.0f);

	return card;
}

HeroInventory::~HeroInventory()
{
	moneyCount->entity->destroy();

	for (auto button : buttons)
	{
		button->destroy();
	}

	for (auto dino : dinos)
	{
		dino->entity->destroy();
	}

	buttons.clear();
	dinos.clear();
}

void HeroInventory::SaveData()
{
	std::ofstream out;
	out.open(SaveManager::nameOfFile, std::ofstream::out);

	std::string changes = "";
	if (out.is_open())
	{
		for (auto dino : dinos)
		{
			changes += "D: " + dino->GetSaveLog() + "\n";
		}

		changes += "M: " + std::to_string(nowMoney) + "\n";
		out << changes;
	}
	out.close();
}

void HeroInventory::LoadData()
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

				dino = DinoCreator::CreateDino(str, dex, intt, Area::None);


				AddDino(dino);
				break;
			case 'M':
				stats = Func::SplitLine(line);

				nowMoney = std::atoi(stats[1].c_str());
				break;
			default:
				break;
			}
		}
	}
	in.close();
}