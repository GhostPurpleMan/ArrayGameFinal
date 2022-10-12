#include "Player.h"
#include <iostream>
using namespace std;



constexpr char kplayerSymbol = '@';

Player::Player()
    :m_hasKey(false)
{

}
Player::~Player()
{

}


void Player::setPosition(int x, int y)
{
    m_Position.x = x;
    m_Position.y = y;
}

bool Player::HasKey()
{
    return m_hasKey;
}
void Player::PickupKey()
{
    m_hasKey = true;
}
void Player::UseKey()
{
    m_hasKey = false;
}
void Player::Draw()
{
    cout << kplayerSymbol;
}