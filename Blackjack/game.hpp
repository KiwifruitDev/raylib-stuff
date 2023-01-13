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

#pragma once

#include "player.hpp"
#include "cards.hpp"
#include "hand.hpp"
#include <random>

namespace KiwifruitDev
{
	namespace Blackjack
	{
		enum GameState
		{
			/// <summary>
			/// Waiting for a decision.
			/// </summary>
			Waiting,

			/// <summary>
			/// Can make a decision.
			/// </summary>
			Active,
			
			/// <summary>
			/// Player won.
			/// </summary>
			Win,
			
			/// <summary>
			/// Dealer won.
			/// </summary>
			Lose,

			/// <summary>
			/// Tie, push.
			/// </summary>
			Push,

			/// <summary>
			/// The player ran out of money.
			/// </summary>
			GameOver
		};
		
		/// <summary>
		/// Game logic.
		/// </summary>
		class Game
		{
		private:
			/// <summary>
			/// A virtual card deck.
			/// <para>This is populated with 52 cards and then shuffled.</para>
			/// </summary>
			std::vector<Card> deck;
			
			/// <summary>
			/// The dealer's hand.
			/// </summary>
			Hand* hand;

			/// <summary>
			/// The player and their hand.
			/// </summary>
			Player* player;
			
			/// <summary>
			/// The state of the game.
			/// </summary>
			GameState state;

			/// <summary>
			/// Random number generator.
			/// </summary>
			std::mt19937 rng;

			/// <summary>
			/// Populate the deck with 52 cards.
			/// </summary>
			void PopulateDeck();
		public:
			/// <summary>
			/// Constructor.
			/// </summary>
			Game();
			
			/// <summary>
			/// Pick a card from the deck.
			/// <para>If no cards are present, more cards are added to the deck.</para>
			/// </summary>
			Card PickCard();

			/// <summary>
			/// Deals a random card from the virtual deck.
			/// <param name="checkBust">Check if the dealer has busted.</param>
			/// <returns>Whether or not the dealer busted.</returns>
			/// </summary>
			bool Deal(bool checkBust = true);

			/// <summary>
			/// Get the hand.
			/// </summary>
			/// <returns>The hand.</returns>
			Hand* GetHand();

			/// <summary>
			/// Get the player.
			/// </summary>
			/// <returns>The player.</returns>
			Player* GetPlayer();

			/// <summary>
			/// Get the state of the game.
			/// </summary>
			/// <returns>The state of the game.</returns>
			GameState GetState();

			/// <summary>
			/// Hit the hand.
			/// </summary>
			void Hit();
			
			/// <summary>
			/// Stand the hand.
			/// </summary>
			void Stand();
			
			/// <summary>
			/// Resets the game.
			/// </summary>
			void Start();
		};

		/// <summary>
		/// Static game instance.
		/// </summary>
		static Game* globalGame;
	}
}
