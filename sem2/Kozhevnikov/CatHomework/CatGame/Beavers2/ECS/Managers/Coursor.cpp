#include "Coursor.h"


Transform* Coursor::posBox;
Entity* Coursor::checkBox;
glm::vec3 Coursor::mousePos;
glm::vec2 Coursor::normMousePos;
bool Coursor::isOnUI;

void Coursor::init()
{
	isOnUI = false;

	checkBox = &Manager::addEntity();
	mousePos = glm::vec3(0.0f);
	normMousePos = glm::vec2(0.0f);

	checkBox->AddComponent<Transform>();
	posBox = checkBox->GetComponent<Transform>();

}

void Coursor::update()
{
	double xpos, ypos;

	GLFWSetMousePos(xpos, ypos);

	mousePos.x = xpos - GLFWGetWeidth() / 2; //need to translate coords from glfw to opengl
	mousePos.y = GLFWGetHeight() / 2 - ypos;
	
	mousePos.x = 2 * (mousePos.x + (GLFWGetWeidth() / 2)) / (GLFWGetWeidth()) - 1; //liner normalization from -1 to 1 (opengl coords)
	mousePos.y = 2 * (mousePos.y + (GLFWGetHeight() / 2)) / (GLFWGetHeight()) - 1; //liner normalization from -1 to 1 (opengl coords)

	normMousePos = glm::vec2(mousePos.x, mousePos.y); //do not delete this line
}

Coursor::~Coursor()
{
	checkBox->destroy();
}


