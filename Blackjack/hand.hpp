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

#include "cards.hpp"
#include <vector>

namespace KiwifruitDev
{
	namespace Blackjack
	{
		/// <summary>
		/// Hand class to hold cards.
		/// </summary>
		class Hand
		{
		protected:
			/// <summary>
			/// The cards in the hand.
			/// </summary>
			std::vector<Card> cards;

			/// <summary>
			/// The score of the hand.
			/// </summary>
			int score;
		public:
			/// <summary>
			/// Default constructor.
			/// </summary>
			Hand();

			/// <summary>
			/// Add a card to the hand.
			/// </summary>
			/// <param name="card">The card to add.</param>
			/// <returns>True if the card was added, false if the hand is full.</returns>
			bool AddCard(Card card);

			/// <summary>
			/// Gets the score of the hand.
			/// </summary>
			/// <returns>The score of the hand.</returns>
			int GetScore();

			/// <summary>
			/// Gets the card at the specified index.
			/// </summary>
			/// <param name="index">The index of the card.</param>
			/// <returns>The card at the specified index.</returns>
			Card GetCard(int index);

			/// <summary>
			/// Gets the cards in the hand.
			/// </summary>
			/// <returns>The cards in the hand.</returns>
			std::vector<Card> GetCards();
		};
	}
}
