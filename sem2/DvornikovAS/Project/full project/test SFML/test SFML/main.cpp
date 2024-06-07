#include <iostream>

#include "Music.h"
#include "Texts.h"
#include "Images.h"
#include "Main_cycle.h"
#include "window.h"


int main() {

	window.setFramerateLimit(60);

	load_music();
	load_fonts();
	load_texts();
	load_images();

	//загрузка карточек в магазин
	shop_cards.push_back(std::make_pair(pterodactile(), std::make_pair(pterodactile().getPrice(), pterodactile().getStatus())));
	shop_cards.push_back(std::make_pair(brahiosaur(), std::make_pair(brahiosaur().getPrice(), brahiosaur().getStatus())));
	shop_cards.push_back(std::make_pair(stegosaur(), std::make_pair(stegosaur().getPrice(), stegosaur().getStatus())));
	shop_cards.push_back(std::make_pair(trex(), std::make_pair(trex().getPrice(), trex().getStatus())));

	shop_cards2.push_back(std::make_pair(pterodactile2(), std::make_pair(pterodactile2().getPrice(), pterodactile2().getStatus())));
	shop_cards2.push_back(std::make_pair(brahiosaur2(), std::make_pair(brahiosaur2().getPrice(), brahiosaur2().getStatus())));
	shop_cards2.push_back(std::make_pair(stegosaur2(), std::make_pair(stegosaur2().getPrice(), stegosaur2().getStatus())));
	shop_cards2.push_back(std::make_pair(trex2(), std::make_pair(trex2().getPrice(), trex2().getStatus())));

	main_cycle();

	return 0;
}