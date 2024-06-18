#pragma once
#include "ECS.h"
#include "Components.h"


//Инсрукция по работе с SceneManager
// 
//1. Находишь SceneManager.cpp
//2. Делаешь новую функцию по примерам в самом низу файла.И пишешь в этой функции код для уровня
//3. Поле того как создал локацию добавляешь все созданные Entity в vector также по примеру и возвращаешь его
//4. В init() добавляешь в scenesFuncs свое создание уровня
//5. Поздравяю ты прекрасен и теперь можешь использовать SceneManager::LoadScene() или SceneManager::LoadNextScene()

class SceneManager : public Component
{
private:
	static int nowScene;
	static std::vector<void (*)(std::vector<Entity*>&)> scenesFuncs; //not the best, but...I was lazy to do something smarter (look for functions in cpp)
	static std::vector<Entity*> currentEntities;
public:

	void init() override;

	static void LoadScene(int n);
	static void LoadNextScene();
	static void ReloadScene();

private:
	static void ClearScene();
};