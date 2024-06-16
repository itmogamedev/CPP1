#include "Player.h"

Player::Player(int i_coins)
{
	coins = i_coins;

	chosen_dinos.push_back(nullptr);
	chosen_dinos.push_back(nullptr);
	chosen_dinos.push_back(nullptr);
}
bool Player::any_dino_alive()
{
	for (auto a : chosen_dinos)
	{
		if (a!= nullptr && a->is_alive)
		{
			return true;
		}
	}
	return false;
}
int Player::getCoins()
{
	return coins;
}
void Player::buy_dino(Dino* newDino)
{
    if (coins >= newDino->getCost())
    {
        coins -= newDino->getCost();
        dinos_owned.push_back(newDino);
      //  std::cout << "DINO BOUGHT. COINS: " << coins << std::endl;
    }
    else
    {
      //  std::cout << "TOO POOR" << std::endl;
    }
}
void Player::generate_dinos()
{
	for (int k = 0; k < 3; k++)
	{
		this->chosen_dinos[k] = new Dino();
	}
}
void Player::giveCoins(int a)
{
	coins += a;
}
void Player::setCoins(int a)
{
	coins = a;
}
void Player::reset_dinos()
{
	for (auto d : dinos_owned)
	{
		d->reset();
	}
}
bool Player::has_dinos()
{
	return (!dinos_owned.empty());
}