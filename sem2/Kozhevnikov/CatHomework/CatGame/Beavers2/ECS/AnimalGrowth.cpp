#include "AnimalGrowth.h"
#include "SceneManager/SceneManager.h"
#include "Render.h"

void AnimalGrowth::init()
{
	lastESC = Time::GetCurrentTime();

	maxSize  = GLFWGetWeidth();
	maxFull  = 100;
	maxClean = 100;
	maxHydr  = 100;
	
	hydr  = maxHydr;
	clean = maxClean;
	full = maxFull;


	speedGrowth = 10.0f;
	lastTime = Time::GetCurrentTime();

	transform = entity->GetComponent<Transform>();
	size = transform->GetScale().x;


	float iconSize = 0.05f;


	Entity* size(&Manager::addEntity());
	sizeText = size->AddComponent<UIText>("100 out of 100", glm::vec2(-0.8, 0.8), iconSize);
	size->AddComponent<UIIcon>(glm::vec2(-0.9, 0.8f), "res/Textures/size.png", iconSize, iconSize);


	////
	Entity* hydr(&Manager::addEntity());
	hydrText = hydr->AddComponent<UIText>("100 out of 100", glm::vec2(-0.8, 0.7), iconSize);
	hydr->AddComponent<UIIcon>(glm::vec2(-0.9, 0.7f), "res/Textures/water.png", iconSize, iconSize);
	UIButton* buttonHydr = hydr->AddComponent<UIButton>(glm::vec2(0.0, 0.7),
		"res/Textures/button.png",
		iconSize, iconSize);
	auto lamAddHydr = [this]()
	{
		increaseHydr(10);
	};
	buttonHydr->AddCall(lamAddHydr);
	////
	
	////
	Entity* clean(&Manager::addEntity());
	cleanText = clean->AddComponent<UIText>("100 out of 100", glm::vec2(-0.8, 0.6), iconSize);
	clean->AddComponent<UIIcon>(glm::vec2(-0.9, 0.6f), "res/Textures/clean.png", iconSize, iconSize);
	UIButton* buttonClean = clean->AddComponent<UIButton>(glm::vec2(0.0, 0.6),
														"res/Textures/button.png",
														iconSize, iconSize);
	auto lamAddClean = [this]()
	{
		increaseClean(10);
	};
	buttonClean->AddCall(lamAddClean);
	////

	////
	Entity* fullE(&Manager::addEntity());
	fullText = fullE->AddComponent<UIText>("100 out of 100", glm::vec2(-0.8, 0.5), iconSize);
	fullE->AddComponent<UIIcon>(glm::vec2(-0.9, 0.5f), "res/Textures/hungry.png", iconSize, iconSize);
	UIButton* buttonFull = fullE->AddComponent<UIButton>(glm::vec2(0.0, 0.5),
														"res/Textures/button.png",
														iconSize, iconSize);
	auto lamAddFull = [this]()
	{
		increaseFull(10);
	};
	buttonFull->AddCall(lamAddFull);

	Entity* waitScreen(&Manager::addEntity());
	escBack = waitScreen->AddComponent<UIIcon>(glm::vec2(0.0f), "res/Textures/beaver.jpg", 1.0f, 1.0f);
	escBack->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.6f));

	escBack->Disable();
}
void AnimalGrowth::update()
{
	if (maxSize <= size)
		SceneManager::LoadScene(2);

	if (size == 0 || clean == 0 || hydr == 0)
		SceneManager::LoadScene(3);

	bool isESCPressed = GLFWGetKeyState(GLFW_KEY_ESCAPE);

	if (isESCPressed == GLFW_PRESS && Time::GetCurrentTime() - lastESC > 0.1f)
	{
		lastESC = Time::GetCurrentTime();
		if (escBack->IsEnabled())
		{
			escBack->Disable();
		}
		else
		{
			escBack->Enable();
		}
	}

	if (Time::GetCurrentTime() - lastTime < 1.0f || escBack->IsEnabled())
		return;
	lastTime = Time::GetCurrentTime();

	if (full == 0)
	{
		full = maxFull;
		size -= speedGrowth;
	}
	else if (full == maxFull)
	{
		size += speedGrowth;
		full = maxFull / 2;
	}

	decreaseFull(2);
	decreaseHydr(5);
	decreaseClean(5);
}

void AnimalGrowth::draw()
{
	hydrText->ChangeText((std::to_string(hydr) + " out of " + std::to_string(maxHydr)).c_str());
	fullText->ChangeText((std::to_string(full) + " out of " + std::to_string(maxFull)).c_str());
	cleanText->ChangeText((std::to_string(clean) + " out of " + std::to_string(maxClean)).c_str());
	sizeText->ChangeText((std::to_string(size) + " out of " + std::to_string(maxSize)).c_str());

	transform->SetScale(glm::vec3(size));
}


AnimalGrowth::~AnimalGrowth()
{
	hydrText->entity->destroy();
	sizeText->entity->destroy();
	cleanText->entity->destroy();
	fullText->entity->destroy();
	escBack->entity->destroy();
}