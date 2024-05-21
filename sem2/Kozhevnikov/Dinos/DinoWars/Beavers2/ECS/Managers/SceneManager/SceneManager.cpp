#include "SceneManager.h"
void CreateScene1(std::vector<Entity*>&);
void CreateScene2(std::vector<Entity*>&);
void CreateScene3(std::vector<Entity*>&);

int SceneManager::nowScene;
std::vector<Entity*> SceneManager::currentEntities;
std::vector<void (*)(std::vector<Entity*>&)> SceneManager::scenesFuncs;

void SceneManager::init()
{
	nowScene = 0;

	scenesFuncs.push_back(CreateScene1);
	scenesFuncs.push_back(CreateScene2);
	scenesFuncs.push_back(CreateScene3);
}

void SceneManager::LoadScene(int n)
{
	nowScene = n;

	SaveManager::SaveData();
	ClearScene();
	scenesFuncs[nowScene](currentEntities); //spawn scenes and give entities
	SaveManager::LoadData();
}


void SceneManager::LoadNextScene()
{
	nowScene++;
	LoadScene(nowScene);
}


void SceneManager::ReloadScene()
{
	ClearScene();
	LoadScene(nowScene);
}

void SceneManager::ClearScene()
{
	for (auto entity : currentEntities)
	{
		entity->destroy();
	}
	currentEntities.clear();
}

////////////////////////////////////////////////////////////////////////////////////scenes////////////////////////////////////////////////////////////////////////////////////
void CreateScene1(std::vector<Entity*>& vec)
{
	Entity* title(&Manager::addEntity());
	Entity* txtNewGame(&Manager::addEntity());
	Entity* txtLoadGame(&Manager::addEntity());
	Entity* txtSettings(&Manager::addEntity());
	Entity* settingsWindow(&Manager::addEntity());
	
	////////////////
	title->AddComponent<UIText>("dino wars", glm::vec2(-0.5f, 0.7f), 0.08f, 0.1f);
	////////////////

	////////////////
	UIButton* buttonNewGame = txtNewGame->AddComponent<UIButton>(glm::vec2(-0.0f, 0.3f), 
																"res/Textures/UI/button.png", 0.03f * 8, 0.05f);
	auto lamNewGame = []()
	{
		SaveManager::ClearData();
		SceneManager::LoadNextScene();
	};
	buttonNewGame->AddCall(lamNewGame);

	UIText* texNew = txtNewGame->AddComponent<UIText>("new game", glm::vec2(-0.15f, 0.3f), 0.03f);
	texNew->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	////////////////


	////////////////
	UIButton* buttonLoadGame = txtLoadGame->AddComponent<UIButton>(glm::vec2(-0.0f, 0.1f),
																  "res/Textures/UI/button.png", 0.03f * 8, 0.05f);
	auto lamLoadGame = []()
	{
		SceneManager::LoadNextScene();
	};
	buttonLoadGame->AddCall(lamLoadGame);

	UIText* texLoad = txtLoadGame->AddComponent<UIText>("load game", glm::vec2(-0.18f, 0.1f), 0.03f);
	texLoad->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	////////////////


	////////////////
	UIIcon* uiOptines = settingsWindow->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/Beaver1.jpg", 1.0f, 1.0f);
	uiOptines->Disable();
	uiOptines->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.6f));

	UIText* texSettings = txtSettings->AddComponent<UIText>("settings", glm::vec2(-0.15f, -0.1f), 0.03f);
	texSettings->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	UIButton* buttonOptines = txtNewGame->AddComponent<UIButton>(glm::vec2(-0.0f, -0.1f),
																  "res/Textures/UI/button.png", 0.03f * 8, 0.05f);
	auto lamOptiones = [uiOptines]()
	{
		if (uiOptines->IsEnabled())
			uiOptines->Disable();
		else
			uiOptines->Enable();
	};
	buttonOptines->AddCall(lamOptiones);
	////////////////

	///////////////////////////////////////////////////////////////////
	vec.push_back(txtNewGame);
	vec.push_back(txtLoadGame);
	vec.push_back(settingsWindow);
	vec.push_back(txtSettings);
	vec.push_back(title);
}

void CreateScene2(std::vector<Entity*>& vec)
{
	Entity* shop(&Manager::addEntity());
	Entity* inventory(&Manager::addEntity());
	Entity* toFight(&Manager::addEntity());

	shop->AddComponent<ShopManager>();
	inventory->AddComponent<HeroInventory>(true);
	

	UIButton* button = toFight->AddComponent<UIButton>(glm::vec2(0.0f, 0.9f), "res/Textures/UI/button.png", 0.3f, 0.05f);
	auto lamNextScene = []()
	{
		SceneManager::LoadNextScene();
	};
	button->AddCall(lamNextScene);

	UIText* fightText = toFight->AddComponent<UIText>("to fight", glm::vec2(0.0f - 0.03f * 5, 0.9f), 0.03f);
	fightText->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));


	vec.push_back(toFight);
	vec.push_back(shop);
	vec.push_back(inventory);
}

void CreateScene3(std::vector<Entity*>& vec)
{
	Entity* battleManager(&Manager::addEntity());

	battleManager->AddComponent<BattleManager>();

	vec.push_back(battleManager);
}

