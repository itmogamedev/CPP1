#include "SceneManager.h"
void CreateScene1(std::vector<Entity*>&);
void CreateScene2(std::vector<Entity*>&);
void CreateScene3(std::vector<Entity*>&);
void CreateScene4(std::vector<Entity*>&);

int SceneManager::nowScene;
std::vector<Entity*> SceneManager::currentEntities;
std::vector<void (*)(std::vector<Entity*>&)> SceneManager::scenesFuncs;

std::string animalText;
void SceneManager::init()
{
	nowScene = 0;

	scenesFuncs.push_back(CreateScene1);
	scenesFuncs.push_back(CreateScene2);
	scenesFuncs.push_back(CreateScene3);
	scenesFuncs.push_back(CreateScene4);
}

void SceneManager::LoadScene(int n)
{
	nowScene = n;

	ClearScene();
	scenesFuncs[nowScene](currentEntities); //spawn scenes and give entities
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
	Entity* background(&Manager::addEntity());
	Entity* title(&Manager::addEntity());
	Entity* cat(&Manager::addEntity());
	Entity* dog(&Manager::addEntity());
	Entity* shinshila(&Manager::addEntity());

	////////////////
	title->AddComponent<UIText>("animal game", glm::vec2(-0.7f, 0.7f), 0.08f, 0.1f);
	////////////////
	background->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/Background.jpg", 1.0f, 1.0f);

	UIButton* catButton = cat->AddComponent<UIButton>(glm::vec2(-0.5, -0.5f), "res/Textures/Cat.png", 0.3f, 0.3f);
	auto lamSetCat = []()
	{
		animalText = "Cat";
		SceneManager::LoadNextScene();
	};
	catButton->AddCall(lamSetCat);


	UIButton* dogButton = dog->AddComponent<UIButton>(glm::vec2(0.0, -0.5f), "res/Textures/Dog.png", 0.2f, 0.3f);
	auto lamSetDog = []()
	{
		animalText = "Dog";
		SceneManager::LoadNextScene();
	};
	dogButton->AddCall(lamSetDog);


	UIButton* shishButton = shinshila->AddComponent<UIButton>(glm::vec2(0.5, -0.6f), "res/Textures/Shinshila.png", 0.2f, 0.2f);
	auto lamSetShish = []()
	{
		animalText = "Shinshila";
		SceneManager::LoadNextScene();
	};
	shishButton->AddCall(lamSetShish);

	
	///////////////////////////////////////////////////////////////////
	vec.push_back(title);
	vec.push_back(background);
	vec.push_back(cat);
	vec.push_back(dog);
	vec.push_back(shinshila);
}

void CreateScene2(std::vector<Entity*>& vec)
{
	Entity* background(&Manager::addEntity());
	Entity* animal(&Manager::addEntity());
	
	////////////////
	background->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/Background.jpg", 1.0f, 1.0f);

	std::string text = "res/Textures/" + animalText + ".png";
	animal->AddComponent<Transform>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(30.0f));
	animal->AddComponent<SpriteComponent>( text.c_str());
	animal->AddComponent<AnimalGrowth>();

	vec.push_back(animal);
	vec.push_back(background);
}

void CreateScene3(std::vector<Entity*>& vec)
{
	Entity* background(&Manager::addEntity());
	Entity* text(&Manager::addEntity());

	////////////////
	background->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/Background.jpg", 1.0f, 1.0f);
	
	text->AddComponent<UIText>("you w in", glm::vec2(-0.7f, 0.0f), 0.1f, 0.1f);

	vec.push_back(background);
	vec.push_back(text);
}

void CreateScene4(std::vector<Entity*>& vec)
{
	Entity* background(&Manager::addEntity());
	Entity* text(&Manager::addEntity());

	////////////////
	background->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/Background.jpg", 1.0f, 1.0f);

	text->AddComponent<UIText>("you lose", glm::vec2(-0.7f, 0.0f), 0.1f, 0.1f);

	vec.push_back(background);
	vec.push_back(text);
}