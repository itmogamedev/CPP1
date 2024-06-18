#include "ECSFunc.h"

//////////////////////////// - INFORMATION - ///////////////////////////////
//// 1. ������������� ���������� ������ ������� �������� 10    ////
//// 2. ������� �������� ��������� ����� ������� ��������		////
////    10																////
////////////////////////////////////////////////////////////////////////////


void ECSInit()
{
	/////////////////////Define entities/////////////////////
	Entity& coursor(Manager::addEntity());
	Entity& cam(Manager::addEntity());
	Entity& raycast(Manager::addEntity());
	Entity& timeManager(Manager::addEntity());
	Entity& sceneManager(Manager::addEntity());
	//////////////////////////////////////////////
	timeManager.AddComponent<Time>();

	sceneManager.AddComponent<SceneManager>();

	coursor.AddComponent<Coursor>();
	
	cam.AddComponent<Transform>(glm::vec3(0.0f));
	cam.AddComponent<CamComponent>();
	///////////////////////////////////////////////////

	SceneManager::LoadScene(0);
}

void ECSStop(std::unique_ptr<Manager> manager)
{
	manager->refresh();
	manager.reset();
}

Entity& CreatObj()
{
	Entity& obj(Manager::addEntity());

	return obj;
}



//some prefabs as functions. Don't know still is it worth it to declare them?


