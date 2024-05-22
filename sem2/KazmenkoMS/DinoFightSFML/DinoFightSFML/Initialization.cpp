#include "Resourses.h"
#include "Functions.h"
// window
const unsigned int width = 1280, height = 720;
sf::ContextSettings settings;
sf::RenderWindow window(sf::VideoMode(width, height), "Dino Fight", sf::Style::Default);
sf::Color bg_color(0, 121, 128, 255);
sf::Color text_color(66, 66, 66, 255);
sf::Font font;

float elapsed, elapsed1;
sf::Clock timer, timer1;
State state;

sf::Texture emptyTexture;
std::unordered_map<std::string, sf::Texture>Textures;
std::unordered_map < std::string, sf::Sound> Sounds;
std::vector<Dino*>dinos;

std::vector<Dino*>emptyvec; // только для DisplayDinos чтобы передать в качестве параметра по умолчанию
Player player;

// создать и добавить текстуру в мап
void CreateTexture(std::string name)
{
	sf::Texture tmptext;
	tmptext.loadFromFile(name);
	Textures[name] = tmptext;
}
// создать и добавить звук в мап
void CreateSound(std::string soundname,bool isLoop,float volume)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	buffer->loadFromFile("resources/" + soundname + ".mp3");
	sf::Sound sound(*buffer);
	sound.setLoop(isLoop);
	sound.setVolume(volume);
	Sounds[soundname] = sound;
}
// заглушить все звуки
void MuteAll()
{
	for (auto& sound : Sounds)
	{
		sound.second.stop();
	}
}
// texture manager
void LoadTextures(std::unordered_map<std::string, sf::Texture>& Textures)
{
	for (Dino* dino : dinos)
	{
		CreateTexture("resources/DinoTextures/Idle_" + dino->getname() + ".png");
		CreateTexture("resources/DinoTextures/Run_" + dino->getname() + ".png");
		CreateTexture("resources/DinoTextures/Hurt_" + dino->getname() + ".png");
		CreateTexture("resources/DinoTextures/Kick_" + dino->getname() + ".png");
		CreateTexture("resources/DinoTextures/Death_" + dino->getname() + ".png");
	}
	CreateTexture("resources/logo.png");
	CreateTexture("resources/Button.png");
	CreateTexture("resources/PressedButton.png");
	CreateTexture("resources/cross.png");
	CreateTexture("resources/ArrowL.png");
	CreateTexture("resources/ArrowR.png");
	CreateTexture("resources/PressedArrowL.png");
	CreateTexture("resources/PressedArrowR.png");
	CreateTexture("resources/buyButton.png");
	CreateTexture("resources/buyButtonPressed.png");
	CreateTexture("resources/PickButton.png");
	CreateTexture("resources/PickButtonPressed.png");
	CreateTexture("resources/StartButton.png");
}

// 