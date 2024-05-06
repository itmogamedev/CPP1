#pragma once

#ifndef IMAGES_H__
#define IMAGES_H__

#include <iostream>

#include "SFML/Graphics.hpp"

sf::Texture title;
sf::Texture start_game;
sf::Texture texture_shop;
sf::Texture texture_options;
sf::Texture texture_exit;
sf::Texture texture_question;
sf::Texture texture_yes;
sf::Texture texture_no;
sf::Texture t_options;
sf::Texture t_music;
sf::Texture t_sound;
sf::Texture t_switch_yes;
sf::Texture t_switch_no;
sf::Texture t_back;
sf::Texture t_magaz;
sf::Texture t_magaz_left;
sf::Texture t_magaz_right;
sf::Texture t_coin;
sf::Texture t_small;
sf::Texture t_big;
sf::Texture t_small_bought;
sf::Texture t_big_bought;
sf::Texture t_fault_small;
sf::Texture t_fault_big;
sf::Texture t_area;
sf::Texture t_hold_card;
sf::Texture t_pick_card;
sf::Texture t_del_card;
sf::Texture t_start_btn;
sf::Texture t_hold_start_btn;
sf::Texture t_battle;
sf::Texture t_vs;
sf::Texture t_border;
sf::Texture t_bar;
sf::Texture t_hold_card_mini;
sf::Texture t_pick_card_mini;
sf::Texture t_del_card_mini;
sf::Texture t_attack_card_mini;
sf::Texture t_death_card_mini;
sf::Texture t_attack_card;
sf::Texture t_attacked_card;

sf::Sprite _title;
sf::Sprite sp_start;
sf::Sprite sp_shop;
sf::Sprite sp_options;
sf::Sprite sp_exit;
sf::Sprite sp_question;
sf::Sprite sp_yes;
sf::Sprite sp_no;
sf::Sprite sp_t_options;
sf::Sprite sp_music;
sf::Sprite sp_sound;
sf::Sprite music_button;
sf::Sprite sound_button;
sf::Sprite sp_back;
sf::Sprite sp_magaz;
sf::Sprite sp_magaz_left;
sf::Sprite sp_magaz_right;
sf::Sprite sp_coin;
sf::Sprite sp_small_left;
sf::Sprite sp_small_right;
sf::Sprite sp_big;
sf::Sprite sp_small_bought_left;
sf::Sprite sp_small_bought_right;
sf::Sprite sp_big_bought;
sf::Sprite sp_fault_small_left;
sf::Sprite sp_fault_small_right;
sf::Sprite sp_fault_big;
sf::Sprite sp_area;
sf::Sprite sp_hold_left_card;
sf::Sprite sp_hold_centre_card;
sf::Sprite sp_hold_right_card;
sf::Sprite sp_pick_left_card;
sf::Sprite sp_pick_centre_card;
sf::Sprite sp_pick_right_card;
sf::Sprite sp_del_left_card;
sf::Sprite sp_del_centre_card;
sf::Sprite sp_del_right_card;
sf::Sprite sp_start_btn;
sf::Sprite sp_hold_start_btn;
sf::Sprite sp_battle;
sf::Sprite sp_vs;
sf::Sprite sp_border_top_left;
sf::Sprite sp_border_top_centre;
sf::Sprite sp_border_top_right;
sf::Sprite sp_border_bottom_left;
sf::Sprite sp_border_bottom_centre;
sf::Sprite sp_border_bottom_right;
sf::Sprite sp_bar_top_left;
sf::Sprite sp_bar_top_centre;
sf::Sprite sp_bar_top_right;
sf::Sprite sp_bar_bottom_left;
sf::Sprite sp_bar_bottom_centre;
sf::Sprite sp_bar_bottom_right;
sf::Sprite sp_hold_bottom_left_card_mini;
sf::Sprite sp_hold_bottom_centre_card_mini;
sf::Sprite sp_hold_bottom_right_card_mini;
sf::Sprite sp_pick_top_left_card_mini;
sf::Sprite sp_pick_top_centre_card_mini;
sf::Sprite sp_pick_top_right_card_mini;
sf::Sprite sp_pick_bottom_left_card_mini;
sf::Sprite sp_pick_bottom_centre_card_mini;
sf::Sprite sp_pick_bottom_right_card_mini;
sf::Sprite sp_del_bottom_left_card_mini;
sf::Sprite sp_del_bottom_centre_card_mini;
sf::Sprite sp_del_bottom_right_card_mini;
sf::Sprite sp_attack_top_left_card_mini;
sf::Sprite sp_attack_top_centre_card_mini;
sf::Sprite sp_attack_top_right_card_mini;
sf::Sprite sp_death_top_left_card_mini;
sf::Sprite sp_death_top_centre_card_mini;
sf::Sprite sp_death_top_right_card_mini;
sf::Sprite sp_death_bottom_left_card_mini;
sf::Sprite sp_death_bottom_centre_card_mini;
sf::Sprite sp_death_bottom_right_card_mini;
sf::Sprite sp_attack_top_left_card;
sf::Sprite sp_attack_top_centre_card;
sf::Sprite sp_attack_top_right_card;
sf::Sprite sp_attack_bottom_left_card;
sf::Sprite sp_attack_bottom_centre_card;
sf::Sprite sp_attack_bottom_right_card;
sf::Sprite sp_attacked_top_left_card;
sf::Sprite sp_attacked_top_centre_card;
sf::Sprite sp_attacked_top_right_card;
sf::Sprite sp_attacked_bottom_left_card;
sf::Sprite sp_attacked_bottom_centre_card;
sf::Sprite sp_attacked_bottom_right_card;


int load_images() {
	try {title.loadFromFile("img/t_DINOSAURS 2.png");
		_title.setTexture(title);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {start_game.loadFromFile("img/play.png");
		sp_start.setTexture(start_game);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_shop.loadFromFile("img/shop.png");
		sp_shop.setTexture(texture_shop);}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_options.loadFromFile("img/settings.png");
		sp_options.setTexture(texture_options);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_exit.loadFromFile("img/exit.png");
		sp_exit.setTexture(texture_exit);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_question.loadFromFile("img/exit_y_or_n.png");
		sp_question.setTexture(texture_question);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_yes.loadFromFile("img/y.png");
		sp_yes.setTexture(texture_yes);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {texture_no.loadFromFile("img/n.png");
		sp_no.setTexture(texture_no);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_options.loadFromFile("img/options/settings.png");
		sp_t_options.setTexture(t_options);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_music.loadFromFile("img/options/music.png");
		sp_music.setTexture(t_music);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_sound.loadFromFile("img/options/sounds.png");
		sp_sound.setTexture(t_sound);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_switch_yes.loadFromFile("img/options/ON.png");
		music_button.setTexture(t_switch_yes);
		sound_button.setTexture(t_switch_yes);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_switch_no.loadFromFile("img/options/OFF.png");}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {t_back.loadFromFile("img/options/back.png");
		sp_back.setTexture(t_back);}
	catch (const std::exception& e) {std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;}

	try {
		t_magaz.loadFromFile("img/magaz.png");
		sp_magaz.setTexture(t_magaz);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_magaz_left.loadFromFile("img/cards/left.png");
		t_magaz_right.loadFromFile("img/cards/right.png");
		sp_magaz_left.setTexture(t_magaz_left);
		sp_magaz_right.setTexture(t_magaz_right);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_coin.loadFromFile("img/coin.png");
		sp_coin.setTexture(t_coin);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_small.loadFromFile("img/cards/hold_small.png");
		t_big.loadFromFile("img/cards/hold_big.png");
		sp_small_left.setTexture(t_small);
		sp_small_right.setTexture(t_small);
		sp_big.setTexture(t_big);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_small_bought.loadFromFile("img/cards/hold_small_bought.png");
		t_big_bought.loadFromFile("img/cards/hold_big_bought.png");
		sp_small_bought_left.setTexture(t_small_bought);
		sp_small_bought_right.setTexture(t_small_bought);
		sp_big_bought.setTexture(t_big_bought);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_fault_small.loadFromFile("img/cards/fault_small.png");
		t_fault_big.loadFromFile("img/cards/fault_big.png");
		sp_fault_small_left.setTexture(t_fault_small);
		sp_fault_small_right.setTexture(t_fault_small);
		sp_fault_big.setTexture(t_fault_big);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_area.loadFromFile("img/play/area.png");
		sp_area.setTexture(t_area);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_hold_card.loadFromFile("img/play/hold_card.png");
		t_pick_card.loadFromFile("img/play/pick_card.png");
		sp_hold_left_card.setTexture(t_hold_card);
		sp_hold_centre_card.setTexture(t_hold_card);
		sp_hold_right_card.setTexture(t_hold_card);
		sp_pick_left_card.setTexture(t_pick_card);
		sp_pick_centre_card.setTexture(t_pick_card);
		sp_pick_right_card.setTexture(t_pick_card);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_del_card.loadFromFile("img/play/del_card.png");
		sp_del_left_card.setTexture(t_del_card);
		sp_del_centre_card.setTexture(t_del_card);
		sp_del_right_card.setTexture(t_del_card);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_start_btn.loadFromFile("img/play/start_btn.png");
		sp_start_btn.setTexture(t_start_btn);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_hold_start_btn.loadFromFile("img/play/hold_start_btn.png");
		sp_hold_start_btn.setTexture(t_hold_start_btn);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_battle.loadFromFile("img/play/battle.png");
		sp_battle.setTexture(t_battle);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_vs.loadFromFile("img/play/vs.png");
		sp_vs.setTexture(t_vs);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_border.loadFromFile("img/play/border.png");
		t_bar.loadFromFile("img/play/bar.png");
		sp_border_top_left.setTexture(t_border);
		sp_border_top_centre.setTexture(t_border);
		sp_border_top_right.setTexture(t_border);
		sp_border_bottom_left.setTexture(t_border);
		sp_border_bottom_centre.setTexture(t_border);
		sp_border_bottom_right.setTexture(t_border);
		sp_bar_top_left.setTexture(t_bar);
		sp_bar_top_centre.setTexture(t_bar);
		sp_bar_top_right.setTexture(t_bar);
		sp_bar_bottom_left.setTexture(t_bar);
		sp_bar_bottom_centre.setTexture(t_bar);
		sp_bar_bottom_right.setTexture(t_bar);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_hold_card_mini.loadFromFile("img/play/hold_card_mini.png");
		t_pick_card_mini.loadFromFile("img/play/pick_card_mini.png");
		t_del_card_mini.loadFromFile("img/play/del_card_mini.png");
		sp_hold_bottom_left_card_mini.setTexture(t_hold_card_mini);
		sp_hold_bottom_centre_card_mini.setTexture(t_hold_card_mini);
		sp_hold_bottom_right_card_mini.setTexture(t_hold_card_mini);
		sp_pick_top_left_card_mini.setTexture(t_pick_card_mini);
		sp_pick_top_centre_card_mini.setTexture(t_pick_card_mini);
		sp_pick_top_right_card_mini.setTexture(t_pick_card_mini);
		sp_pick_bottom_left_card_mini.setTexture(t_pick_card_mini);
		sp_pick_bottom_centre_card_mini.setTexture(t_pick_card_mini);
		sp_pick_bottom_right_card_mini.setTexture(t_pick_card_mini);
		sp_del_bottom_left_card_mini.setTexture(t_del_card_mini);
		sp_del_bottom_centre_card_mini.setTexture(t_del_card_mini);
		sp_del_bottom_right_card_mini.setTexture(t_del_card_mini);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_attack_card_mini.loadFromFile("img/play/attack_card_mini.png");
		sp_attack_top_left_card_mini.setTexture(t_attack_card_mini);
		sp_attack_top_centre_card_mini.setTexture(t_attack_card_mini);
		sp_attack_top_right_card_mini.setTexture(t_attack_card_mini);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_death_card_mini.loadFromFile("img/play/death_card_mini.png");
		sp_death_top_left_card_mini.setTexture(t_death_card_mini);
		sp_death_top_centre_card_mini.setTexture(t_death_card_mini);
		sp_death_top_right_card_mini.setTexture(t_death_card_mini);
		sp_death_bottom_left_card_mini.setTexture(t_death_card_mini);
		sp_death_bottom_centre_card_mini.setTexture(t_death_card_mini);
		sp_death_bottom_right_card_mini.setTexture(t_death_card_mini);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

	try {
		t_attack_card.loadFromFile("img/play/attack_card.png");
		t_attacked_card.loadFromFile("img/play/attacked_card.png");
		sp_attack_top_left_card.setTexture(t_attack_card);
		sp_attack_top_centre_card.setTexture(t_attack_card);
		sp_attack_top_right_card.setTexture(t_attack_card);
		sp_attack_bottom_left_card.setTexture(t_attack_card);
		sp_attack_bottom_centre_card.setTexture(t_attack_card);
		sp_attack_bottom_right_card.setTexture(t_attack_card);
		sp_attacked_top_left_card.setTexture(t_attacked_card);
		sp_attacked_top_centre_card.setTexture(t_attacked_card);
		sp_attacked_top_right_card.setTexture(t_attacked_card);
		sp_attacked_bottom_left_card.setTexture(t_attacked_card);
		sp_attacked_bottom_centre_card.setTexture(t_attacked_card);
		sp_attacked_bottom_right_card.setTexture(t_attacked_card);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 0;
	}

}

#endif