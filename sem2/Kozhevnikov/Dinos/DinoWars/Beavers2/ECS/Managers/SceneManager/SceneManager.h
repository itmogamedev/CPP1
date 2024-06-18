#pragma once
#include "ECS.h"
#include "Components.h"


//��������� �� ������ � SceneManager
// 
//1. �������� SceneManager.cpp
//2. ������� ����� ������� �� �������� � ����� ���� �����.� ������ � ���� ������� ��� ��� ������
//3. ���� ���� ��� ������ ������� ���������� ��� ��������� Entity � vector ����� �� ������� � ����������� ���
//4. � init() ���������� � scenesFuncs ���� �������� ������
//5. ��������� �� ��������� � ������ ������ ������������ SceneManager::LoadScene() ��� SceneManager::LoadNextScene()

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