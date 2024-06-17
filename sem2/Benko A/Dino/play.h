#pragma once

enum Terrain { Plain, River, Mountain };
enum Dinosavrus { Teranosavr = 1, Diplodog = 2, Triceratops = 3 };

int play(sf::RenderWindow& window, sf::Font& font)
{

    int cH, ecH, dino1, dino2, a, b, cu_ca, rN1, rN2, rN3, n = 1, en = 1;
    std::string line, cu_pul;
    std::ifstream in("cash.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cu_ca = stoi(line);
        }
    }
    in.close();

    std::ofstream out;
    out.open("dino_numbers.txt");
    if (out.is_open())
    {
        if (stsl1 == false && MASS[0] != 0) {
            out << MASS[0];
        }
        if (stsl2 == false && MASS[1] != 0) {
            out << MASS[1];
        }
        if (stsl3 == false && MASS[2] != 0) {
            out << MASS[2];
        }
        if (stsl4 == false && MASS[3] != 0) {
            out << MASS[3];
        }
        if (stsl5 == false && MASS[4] != 0) {
            out << MASS[4];
        }
        if (stsl6 == false && MASS[5] != 0) {
            out << MASS[5];
        }
    }
    out.close();

    std::string pull, enemy_pull, file_name, terr_name, temr, temr2, terr_n;

    std::string line1;
    std::ifstream in1("pull.txt");
    if (in1.is_open())
    {
        while (getline(in1, line1))
        {
            pull = line1;
        }
    }
    
    if (pull.length() == 0)
    {
        UI alert1({ 1000, 100 }, { 800, 1100 }, sf::Color(20, 230, 230), 60, "You do not choose any dino", font);
        alert1.draw(window);
        window.display();
        Sleep(1000);
        return 0;
    }

    while (window.isOpen()) {
        

        srand(time(0));

        rN1 = rand() % 3 + 1;
        rN2 = rand() % 3 + 1;
        rN3 = rand() % 3 + 1;
        enemy_pull = std::to_string(rN1) + std::to_string(rN2) + std::to_string(rN3);
        cH = 100;
        ecH = 100;
        temr = pull[0];
        dino1 = std::stoi(temr);
        temr2 = enemy_pull[0];
        dino2 = std::stoi(temr2);
        Player player;
        DinoStr D;
        DinoDex D1;
        DinoInt D2;

        switch (dino1) {
        case 1:
            a = player.damage(&D);
            break;
        case 2:
            a = player.damage(&D1);
            break;
        case 3:
            a = player.damage(&D2);
            break;
        }

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> distribution(0, 2);

        int randomIndex = distribution(gen);
        Terrain randomTerrain = static_cast<Terrain>(randomIndex);

        switch (randomTerrain) {
        case Terrain::Plain:
            terr_name = "plain.png";
            terr_n = "PLAIN";
            break;
        case Terrain::River:
            terr_name = "river.png";
            terr_n = "RIVER";
            break;
        case Terrain::Mountain:
            terr_name = "mountain.png";
            terr_n = "MOUNTAIN";
        }

        Button dinoB1({ 600, 600 }, { 200, 250 }, sf::Color(20, 230, 230), "");
        Button dinoB2({ 600, 600 }, { 1800, 250 }, sf::Color(20, 230, 230), "");
        UI terra({ 600, 150 }, { 1000, 100 }, sf::Color(20, 230, 230), 100, terr_n, font);
        UI stat1({ 600, 100 }, { 200, 850 }, sf::Color(20, 230, 230), 60, std::to_string(cH).append("HP"), font);
        UI stat2({ 600, 100 }, { 1800, 850 }, sf::Color(20, 230, 230), 60, std::to_string(ecH).append("HP"), font);
        UI n1({ 100, 100 }, { 800, 250 }, sf::Color(20, 230, 230), 60, std::to_string(n), font);
        UI n2({ 100, 100 }, { 1700, 250 }, sf::Color(20, 230, 230), 60, std::to_string(en), font);
        Button back({ 410, 125 }, { 1100, 1300 }, sf::Color(20, 230, 230), "back.png");
        back.color(sf::Color(20, 150, 150), window);

        switch (dino1) {
        case 1:
            file_name = "ter.jpg";
            break;
        case 2:
            file_name = "dip.jpg";
            break;
        case 3:
            file_name = "tri.jpg";
            break;
        }

        dinoB1.img(file_name, window);

        switch (dino2) {
        case 1:
            file_name = "ter.jpg";
            break;
        case 2:
            file_name = "dip.jpg";
            break;
        case 3:
            file_name = "tri.jpg";
            break;
        }

        dinoB2.img(file_name, window);

        sf::Texture start;
        start.loadFromFile(terr_name);
        sf::RectangleShape HAHAShape(sf::Vector2f(window.getSize()));
        HAHAShape.setTexture(&start);
        HAHAShape.setPosition(0, 0);
        window.draw(HAHAShape);
        terra.draw(window);
        dinoB1.draw(window);
        dinoB2.draw(window);
        stat1.draw(window);
        stat2.draw(window);
        back.draw(window);
        window.display();

        while (pull.length() != 0 and enemy_pull.length() != 0)
        {
            temr = pull[0];
            dino1 = std::stoi(temr);

            temr2 = enemy_pull[0];
            dino2 = std::stoi(temr2);

            switch (dino1) {
            case 1:
                a = player.damage(&D);
                break;
            case 2:
                a = player.damage(&D1);
                break;
            case 3:
                a = player.damage(&D2);
                break;
            }

            switch (dino1) {
            case 1:
                file_name = "ter.jpg";
                break;
            case 2:
                file_name = "dip.jpg";
                break;
            case 3:
                file_name = "tri.jpg";
                break;
            }

            dinoB1.img(file_name, window);
            dinoB1.color(sf::Color(20, 230, 230), window);

            switch (dino2) {
            case 1:
                file_name = "ter.jpg";
                break;
            case 2:
                file_name = "dip.jpg";
                break;
            case 3:
                file_name = "tri.jpg";
                break;
            }
            
            dinoB2.img(file_name, window);
            dinoB2.color(sf::Color(20, 230, 230), window);

            b = rand() % 20 + 10;
            cH = cH - b;
            UI dmg1({ 600, 100 }, { 200, 950 }, sf::Color(20, 230, 230), 60, std::to_string(b).append("HP damage to you"), font);
            dmg1.draw(window);
            window.display();
            Sleep(500);
            if ((randomTerrain == Terrain::Plain and dino1 == 1) or (randomTerrain == Terrain::River and dino1 == 2) or (randomTerrain == Terrain::Mountain and dino1 == 3)) {
                ecH = ecH - (a * 2);
                UI dmg1({ 600, 100 }, { 1800, 950 }, sf::Color(20, 230, 230), 60, std::to_string(a*2).append("HP damage to enemy"), font);
                dmg1.draw(window);
                window.display();
                Sleep(500);
            }
            else {
                ecH = ecH - a;
                UI dmg1({ 600, 100 }, { 1800, 950 }, sf::Color(20, 230, 230), 60, std::to_string(a).append("HP damage to enemy"), font);
                dmg1.draw(window);
                window.display();
                Sleep(500);
            }

            stat1.text(std::to_string(cH).append("HP"), window);
            stat2.text(std::to_string(ecH).append("HP"), window);

            if (cH <= 0) {
                pull.erase(pull.begin());
                cH = 0;
                stat1.text(std::to_string(cH).append("HP"), window);
                stat1.draw(window);
                window.display();
                cH = 100;
                dinoB1.color(sf::Color(230, 20, 20), window);

                if (pull.length() > 0) {
                    ++n;
                    n1.text(std::to_string(n), window);
                }
            }
            if (ecH <= 0) {
                enemy_pull.erase(enemy_pull.begin());
                ecH = 0;
                stat2.text(std::to_string(ecH).append("HP"), window);
                stat2.draw(window);
                window.display();
                cu_ca += (rand() % 8 + 8);
                ecH = 100;
                dinoB2.color(sf::Color(230, 20, 20), window);
                if (enemy_pull.length() > 0) {
                    ++en;
                    n2.text(std::to_string(en), window);
                }

            }
            sf::Texture start;
            start.loadFromFile(terr_name);
            sf::RectangleShape HAHAShape(sf::Vector2f(window.getSize()));
            HAHAShape.setTexture(&start);
            HAHAShape.setPosition(0, 0);
            window.draw(HAHAShape);
            terra.draw(window);
            dinoB1.draw(window);
            dinoB2.draw(window);
            stat1.draw(window);
            stat2.draw(window);
            n1.draw(window);
            n2.draw(window);
            back.draw(window);
            window.display();
            Sleep(1000);
        }

        in.open("dino_numbers.txt");
        if (in.is_open())
        {
            while (getline(in, line))
            {
                cu_pul = line;
            }
        }
        in.close();
        out.open("dino_numbers.txt");
        if (out.is_open())
        {
            if (cu_pul.length() != 0) {
                out << cu_pul << pull;
            } else if (pull.length() != 0) {
                out << pull;
            }
        }
        out.close();

        pull = "";

        out.open("pull.txt");
        if (out.is_open())
        {
            out << pull;
        }
        out.close();

        out.open("cash.txt");
        if (out.is_open())
        {
            out << cu_ca;
        }
        out.close();
        back.color(sf::Color(20, 230, 230), window);
        back.draw(window);
        window.display();
        while (window.isOpen()) {
            sf::Vector2i mPos = sf::Mouse::getPosition(window);
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (back.clicked(mPos))
                        {
                            tem = 0;
                            stsl1 = false, stsl2 = false, stsl3 = false, stsl4 = false, stsl5 = false, stsl6 = false;
                            back.color(sf::Color(20, 180, 180), window);
                            back.draw(window);
                            window.display();
                            Sleep(250);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}