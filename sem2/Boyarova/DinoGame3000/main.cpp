#pragma once
#include "Player.h"
#include "Help.h"
#include "GameMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Text.h"
#include "Music.h"
#include "Shop.h"
#include "GameInfo.h"
#include "Play.h"
#include "Fun.h"
#include "End.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), "GodHelpMe");
    load_fonts();
    load_music();
    Player player;
    BestSongEver.setLoop(true);
    player.LoadGame("data.txt");
    


    while (window.isOpen())
    {
        if (isMenuActive == 1)
        {
            DisplayMenu(window);

        }
        else if (isMenuActive == 2)
        {
            GameShop(window);

        }
        else if (isMenuActive == 3)
        {
            GameInfo();

        }
        else if (isMenuActive == 4)
        {
            Play(window);

        }
      

    }

    return 0;
}