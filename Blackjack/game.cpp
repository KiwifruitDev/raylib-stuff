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

#include "game.hpp"
#include <iostream>

using namespace KiwifruitDev::Blackjack;

/// <summary>
/// Constructor.
/// </summary>
Game::Game() : deck(), state(GameState::Waiting)
{
	hand = new Hand();
	player = new Player();
	rng.seed(std::random_device()());
}

/// <summary>
/// Pick a card from the deck.
/// <para>If no cards are present, more cards are added to the deck.</para>
/// </summary>
Card Game::PickCard()
{
	// Check card count
	if (deck.size() == 0)
	{
		// Populate deck with more cards.
		PopulateDeck();
	}
	// Pick a card
	int index = rng() % deck.size();
	Card card = deck.at(index);
	// Remove card from deck at index
	deck.erase(deck.begin() + index);
	// Return card
	return card;
}

/// <summary>
/// Populate the deck with 52 cards.
/// </summary>
void Game::PopulateDeck()
{
	// Populate the deck with 13 cards of each suit.
	// Up to 52 cards in total.
	for (int i = 0; i < 13; i++)
	{
		deck.push_back(Card((CardValue)i, CardSuit::CLUBS));
		deck.push_back(Card((CardValue)i, CardSuit::DIAMONDS));
		deck.push_back(Card((CardValue)i, CardSuit::HEARTS));
		deck.push_back(Card((CardValue)i, CardSuit::SPADES));
	}
	// Shuffle the deck.
	std::shuffle(deck.begin(), deck.end(), rng);
}

/// <summary>
/// Deals a random card from the virtual deck.
/// </summary>
bool Game::Deal(bool checkBust)
{
	// Deal a card to the dealer.
	hand->AddCard(PickCard());
	
	// Check if the dealer has busted.
	if (hand->GetScore() > 21 && checkBust)
	{
		// The dealer has lost.
		state = GameState::Win;
		
		// Payout bet to player.
		player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);
		
		return true;
	}
	
	// The player can now make a decision.
	state = GameState::Active;

	return false;
}

/// <summary>
/// Get the hand.
/// </summary>
/// <returns>The hand.</returns>
Hand* Game::GetHand()
{
	return hand;
}

/// <summary>
/// Get the player.
/// </summary>
/// <returns>The player.</returns>
Player* Game::GetPlayer()
{
	return player;
}

/// <summary>
/// Get the state of the game.
/// </summary>
/// <returns>The state of the game.</returns>
GameState Game::GetState()
{
	return state;
}

/// <summary>
/// Hit the hand.
/// </summary>
void Game::Hit()
{
	// The player has chose to hit.
	state = GameState::Waiting;
	
	// Deal a card to the player.
	if (!player->AddCard(PickCard()))
		return;
	
	// Did the player bust?
	if (player->GetScore() > 21)
	{
		// The player has lost.
		state = GameState::Lose;
		
		// Take bet from player, if they have enough.
		if (player->GetBalance() >= player->GetBet())
		{
			player->SetBalance(player->GetBalance() - player->GetBet());
		}
		else
		{
			// The player has no money left.
			state = GameState::GameOver;
		}
		
		return;
	}
	else if (player->GetScore() == 21)
	{
		// The player has won.
		state = GameState::Win;

		// Payout bet to player.
		player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);

		return;
	}
	else if (player->GetScore() < 21)
	{
		// Did the dealer bust outright?
		if (hand->GetScore() > 21)
		{
			// The player has won.
			state = GameState::Win;

			// Payout bet to player.
			player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);

			return;
		}
		
		// If the dealer's score is <= 16, deal
		while (hand->GetScore() <= 16)
		{
			if(Deal())
				return;
		}

		// Is the player's hand higher than the dealer's?
		if (player->GetScore() > hand->GetScore())
		{
			// The player has won.
			state = GameState::Win;

			// Payout bet to player.
			player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);
		}
		else if (player->GetScore() < hand->GetScore())
		{
			// The player has lost.
			state = GameState::Lose;

			// Take bet from player, if they have enough.
			if (player->GetBalance() >= player->GetBet())
			{
				player->SetBalance(player->GetBalance() - player->GetBet());
			}
			else
			{
				// The player has no money left.
				state = GameState::GameOver;
			}
		}
		else
		{
			// The player has tied.
			state = GameState::Push;
		}
	}
}

/// <summary>
/// Stand the hand.
/// </summary>
void Game::Stand()
{
	// The player has chose to stand.
	state = GameState::Waiting;

	// Did the dealer bust outright?
	if (hand->GetScore() > 21)
	{
		// The player has won.
		state = GameState::Win;

		// Payout bet to player.
		player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);

		return;
	}
	
	// If the dealer's score is <= 16, deal
	while (hand->GetScore() <= 16)
	{
		if(Deal())
			return;
	}
	
	// Is the player's hand higher than the dealer's?
	if (player->GetScore() > hand->GetScore())
	{
		// The player has won.
		state = GameState::Win;

		// Payout bet to player.
		player->SetBalance(player->GetBalance() + player->GetBet() * 1.5);
	}
	else if (player->GetScore() < hand->GetScore())
	{
		// The player has lost.
		state = GameState::Lose;

		// Take bet from player, if they have enough.
		if (player->GetBalance() >= player->GetBet())
		{
			player->SetBalance(player->GetBalance() - player->GetBet());
		}
		else
		{
			// The player has no money left.
			state = GameState::GameOver;
		}
	}
	else
	{
		// The player has tied.
		state = GameState::Push;
	}
}

/// <summary>
/// Resets the game.
/// </summary>
void Game::Start()
{
	// Reset deck.
	deck.clear();
	PopulateDeck();

	// Reset the hand.
	hand = new Hand();

	// Reset the player.
	int balance = player->GetBalance();
	int bet = player->GetBet();
	if (player != nullptr)
	{
		balance = player->GetBalance();
		bet = player->GetBet();
	}
	player = new Player(balance, bet);

	// Reset the state.
	state = GameState::Waiting;
}
