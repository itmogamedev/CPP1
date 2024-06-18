#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "Renderer.h"



class Coursor : public Component
{
private:
	static Entity* checkBox;
	static Transform* posBox;

	static glm::vec3 mousePos;
	static glm::vec2 normMousePos;

public:
	static bool isOnUI;

	void update() override;
	void init() override;

	static inline glm::vec3 GetMousePos()
	{
		return mousePos;
	}

	static inline glm::vec2 GetNormalizedMousePos()
	{
		return normMousePos;
	}
	~Coursor();
};