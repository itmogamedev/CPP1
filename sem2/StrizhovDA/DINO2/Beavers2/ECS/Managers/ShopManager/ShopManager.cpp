#include "ShopManager.h"
#include "HeroInventory.h"


float ShopManager::cardX = 0.1f;
float ShopManager::cardY = 0.3f;

void ShopManager::init()
{
	srand(time(0));

	dinos.push_back(DinoCreator::CreateDEXDino(Area::None));
	dinos.push_back(DinoCreator::CreateINTDino(Area::None));
	dinos.push_back(DinoCreator::CreateSTRDino(Area::None));

	startCoords = glm::vec2(-0.6f, 0.3f);
	for (Dino* dino : dinos)
	{
		cards.push_back(CreateDinoCard(dino, startCoords)); 
		startCoords.x += 0.6f;
	}
}



void ShopManager::update()
{

}


ShopManager::~ShopManager()
{
	for (auto dino : dinos)
	{
		dino->entity->destroy();
	}

	for (auto card : cards)
	{
		card->destroy();
	}
}

Entity* ShopManager::CreateDinoCard(Dino* dino, glm::vec2 pos)
{
	Entity* card(&Manager::addEntity());

	card->AddComponent<UIText>("price " + std::to_string(dino->GetPrice()),
								pos + glm::vec2(-cardX, -cardY * (3.0f / 6.0f)),
								0.02f);

	card->AddComponent<UIText>("int " + std::to_string(dino->GetINT()),
							   pos + glm::vec2(-cardX, -cardY * (4.0f / 6.0f)),
							   0.02f);

	card->AddComponent<UIText>("dex " + std::to_string(dino->GetDEX()),
							   pos + glm::vec2(-cardX, -cardY * (5.0f/6.0f)),
							   0.02f);

	card->AddComponent<UIText>("str " + std::to_string(dino->GetSTR()), 
							  pos + glm::vec2(-cardX, -cardY), 
							  0.02f);



	UIButton* button = card->AddComponent<UIButton>(pos + glm::vec2(0.0f, cardY / 4.0f),
													dino->GetTexture(),
													cardX, cardY / 2.0f);
	
	auto lamSellDino = [button, dino, this]()
	{
		if (dino->GetPrice() <= HeroInventory::nowMoney)
		{
			HeroInventory::nowMoney -= dino->GetPrice();

			auto it = std::find(dinos.begin(), dinos.end(), dino);
			dinos.erase(it);

			HeroInventory::AddDino(dino);

			auto it2 = std::find(cards.begin(), cards.end(), button->entity);
			cards.erase(it2);
			button->entity->destroy();
		}
	};
	button->AddCall(lamSellDino);
	
	return card;
}