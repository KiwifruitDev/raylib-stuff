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

// Blackjack card definitions

namespace KiwifruitDev
{
	namespace Blackjack
	{
		enum CardSuit
		{
			CLUBS,
			DIAMONDS,
			HEARTS,
			SPADES
		};

		enum CardValue
		{
			ACE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			SEVEN,
			EIGHT,
			NINE,
			TEN,
			JACK,
			QUEEN,
			KING
		};
		
		/// <summary>
		/// Card struct to hold the value and suit of a card.
		/// </summary>
		struct Card {
			/// <summary>
			/// Constructor to create a card.
			/// </summary>
			/// <param name="value">The value of the card.</param>
			/// <param name="suit">The suit of the card.</param>
			Card(CardValue value, CardSuit suit) : value(value), suit(suit) {}
			
			/// <summary>
			/// The suit of the card.
			/// </summary>
			CardSuit suit;

			/// <summary>
			/// The visual value of the card.
			/// <para>See <see cref="Card::GetValue"/> for the actual value.</para>
			/// </summary>
			CardValue value;

			/// <summary>This will provide the card's actual value.</summary>
			/// <param name="score">The current hand. Used to determine if an ace should be 1 or 11.</param>
			/// <returns>The card's actual value.</returns>
			int GetValue(int score)
			{
				switch (value)
				{
				case ACE:
					// Calculate if the ace should be 1 or 11
					return score + 11 > 21 ? 1 : 11;
				case JACK:
				case QUEEN:
				case KING:
					// Face cards are worth 10
					return 10;
				default:
					// All other cards are worth their number
					return value + 1;
				}
			}
		};
	}
}
