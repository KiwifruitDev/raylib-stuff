/*
	raylib-stuff: Blackjack

	MIT License

	Copyright (c) 2023 KiwifruitDev

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "player.hpp"

using namespace KiwifruitDev::Blackjack;

/// <summary>
/// Default constructor.
/// </summary>
Player::Player(int balance, int bet) : Hand(), bet(bet), balance(balance) {}

/// <summary>
/// Gets the player's current bet.
/// </summary>
/// <returns>The player's current bet.</returns>
int Player::GetBet()
{
	return bet;
}

/// <summary>
/// Gets the player's current balance.
/// </summary>
/// <returns>The player's current balance.</returns>
int Player::GetBalance()
{
	return balance;
}

/// <summary>
/// Sets the player's current bet.
/// </summary>
/// <param name="bet">The bet to set.</param>
/// <returns>True if the bet was set, false if the bet is invalid.</returns>
bool Player::SetBet(int bet)
{
	if (bet > 0 && bet <= balance)
	{
		this->bet = bet;
		return true;
	}
	return false;
}

/// <summary>
/// Sets the player's current balance.
/// </summary>
/// <param name="balance">The balance to set.</param>
void Player::SetBalance(int balance)
{
	this->balance = balance;
}
