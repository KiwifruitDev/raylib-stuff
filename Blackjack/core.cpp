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

#include "raylib.h"
#include "game.hpp"
#include <sounds.hpp>

using namespace KiwifruitDev::Blackjack;

// Core executable file

void DrawCard(Card card, int i, float y)
{
	// Draw symbol (text character for now)
	switch (card.suit)
	{
	case CardSuit::CLUBS:
		DrawText("C", 20 + (i * 70), y + 10, 40, BLACK);
		break;
	case CardSuit::DIAMONDS:
		DrawText("D", 20 + (i * 70), y + 10, 40, BLACK);
		break;
	case CardSuit::HEARTS:
		DrawText("H", 20 + (i * 70), y + 10, 40, BLACK);
		break;
	case CardSuit::SPADES:
		DrawText("S", 20 + (i * 70), y + 10, 40, BLACK);
		break;
	}
	// Draw value
	switch (card.value)
	{
	case CardValue::ACE:
		DrawText("A", 20 + (i * 70), y + 50, 40, BLACK);
		break;
	case CardValue::TEN:
		DrawText("10", 20 + (i * 70), y + 50, 40, BLACK);
		break;
	case CardValue::JACK:
		DrawText("J", 20 + (i * 70), y + 50, 40, BLACK);
		break;
	case CardValue::QUEEN:
		DrawText("Q", 20 + (i * 70), y + 50, 40, BLACK);
		break;
	case CardValue::KING:
		DrawText("K", 20 + (i * 70), y + 50, 40, BLACK);
		break;
	default:
		char value[2];
		sprintf(value, "%d", card.value + 1);
		DrawText(value, 20 + (i * 70), y + 50, 40, BLACK);
		break;
	}
}

int main(void)
{
    const int screenWidth = 780;
    const int screenHeight = 450;
	double startTime = 0.0;
	double time = 0.0;
	bool dealerDealt = false;
	bool playerDealt = false;
	bool dealerRevealed = false;
	double nextAnimTimeInterval = 0.25;
	double nextAnimTime = nextAnimTimeInterval;
	bool gameEnd = true;

	Rectangle hitButtonShadow = { 12.0f, 302.0f, 120.0f, 40.0f };
	Rectangle hitButton = { 10.0f, 300.0f, 120.0f, 40.0f };
	
	Rectangle standButtonShadow = { 142.0f, 302.0f, 120.0f, 40.0f };
	Rectangle standButton = { 140.0f, 300.0f, 120.0f, 40.0f };
	
	Rectangle betButtonShadow = { 272.0f, 302.0f, 120.0f, 40.0f };
	Rectangle betButton = { 270.0f, 300.0f, 120.0f, 40.0f };
	
	Rectangle resetButtonShadow = { 402.0f, 302.0f, 120.0f, 40.0f };
	Rectangle resetButton = { 400.0f, 300.0f, 120.0f, 40.0f };

    InitWindow(screenWidth, screenHeight, "raylib-stuff: Blackjack");
	InitAudioDevice();

	SetTargetFPS(60);
	
	globalGame = new Game();
	globalSounds = new Sounds();
	globalGame->Start();

	while (!WindowShouldClose())
	{
		// Update //
		time = GetTime() - startTime;
		std::vector<Card> house = globalGame->GetHand()->GetCards();
		std::vector<Card> playerHand = globalGame->GetPlayer()->GetCards();

		// Status
		char statusText[32];
		switch (globalGame->GetState())
		{
		case Waiting:
			sprintf_s(statusText, "Waiting...");
			gameEnd = true;
			break;
		case Active:
			sprintf_s(statusText, "Your Turn");
			gameEnd = false;
			break;
		case Win:
			sprintf_s(statusText, "You Win!");
			gameEnd = true;
			break;
		case Lose:
			sprintf_s(statusText, "You Lose!");
			gameEnd = true;
			break;
		case Push:
			sprintf_s(statusText, "Push - Draw!");
			gameEnd = true;
			break;
		case GameOver:
			sprintf_s(statusText, "Game Over!");
			gameEnd = true;
			break;
		}

		// Animation to draw the cards on-screen
		if (time >= nextAnimTime)
		{
			if (!dealerDealt)
			{
				globalGame->Deal(false);
				// Play a sound
				PlaySound(globalSounds->Tick);
				// Stop dealing after two cards have been dealt
				if (house.size() == 1)
				{
					dealerDealt = true;
				}
				nextAnimTime += nextAnimTimeInterval;
			}
			else if (!playerDealt)
			{
				globalGame->GetPlayer()->AddCard(globalGame->PickCard());
				PlaySound(globalSounds->Tick);
				playerDealt = true;
			}
		}

		// Detect button click
		Vector2 mousePos = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, hitButton) && !gameEnd)
			{
				// Play a sound
				PlaySound(globalSounds->Click);
				// Hit
				globalGame->Hit();
				dealerRevealed = true;
			}
			else if (CheckCollisionPointRec(mousePos, standButton) && !gameEnd)
			{
				// Play a sound
				PlaySound(globalSounds->Click);
				// Stand
				globalGame->Stand();
				dealerRevealed = true;
			}
			else if (CheckCollisionPointRec(mousePos, betButton) && !gameEnd)
			{
				// Play a sound
				PlaySound(globalSounds->Click);
				// Bet
				globalGame->GetPlayer()->SetBet(globalGame->GetPlayer()->GetBet() + 10);
			}
			else if (CheckCollisionPointRec(mousePos, resetButton))
			{
				// Play a sound
				PlaySound(globalSounds->Click);
				// Reset game
				globalGame->Start();
				dealerDealt = false;
				playerDealt = false;
				startTime = GetTime();
				nextAnimTime = 0;
				dealerRevealed = false;
			}
		}
		else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			if (CheckCollisionPointRec(mousePos, betButton) && !gameEnd)
			{
				// Play a sound
				PlaySound(globalSounds->Click);
				// Bet
				globalGame->GetPlayer()->SetBet(globalGame->GetPlayer()->GetBet() - 10);
			}
		}

        // Draw //
        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Dealer's cards
		for (int i = 0; i < house.size(); i++)
		{
            DrawRectangleRounded({ 12.0f + (i * 70.0f), 52.0f, 60.0f, 90.0f }, 0.2f, 10, BLACK);
			DrawRectangleRounded({ 10.0f + (i * 70.0f), 50.0f, 60.0f, 90.0f }, 0.2f, 10, LIGHTGRAY);
			if (!dealerRevealed && i > 0)
			{
				break;
			}
			DrawCard(house[i], i, 50.0f);
		}
		DrawText("House", 12, 12, 20, BLACK);
        DrawText("House", 10, 10, 20, WHITE);

        // Player's cards
		for (int i = 0; i < playerHand.size(); i++)
		{
            DrawRectangleRounded({ 12.0f + (i * 70.0f), 202.0f, 60.0f, 90.0f }, 0.2f, 10, BLACK);
			DrawRectangleRounded({ 10.0f + (i * 70.0f), 200.0f, 60.0f, 90.0f }, 0.2f, 10, LIGHTGRAY);
			DrawCard(playerHand[i], i, 200.0f);
		}
		DrawText("Your Hand", 12, 162, 20, BLACK);
		DrawText("Your Hand", 10, 160, 20, WHITE);

		// Hit
		DrawRectangleRounded(hitButtonShadow, 0.2f, 10, BLACK);
		DrawRectangleRounded(hitButton, 0.2f, 10, GRAY);
		DrawText("Hit", 12, 302, 20, BLACK);
		DrawText("Hit", 10, 300, 20, WHITE);

		// Stand
		DrawRectangleRounded(standButtonShadow, 0.2f, 10, BLACK);
		DrawRectangleRounded(standButton, 0.2f, 10, GRAY);
		DrawText("Stand", 142, 302, 20, BLACK);
		DrawText("Stand", 140, 300, 20, WHITE);

		// Bet
		DrawRectangleRounded(betButtonShadow, 0.2f, 10, BLACK);
		DrawRectangleRounded(betButton, 0.2f, 10, GRAY);
		DrawText("Bet", 272, 302, 20, BLACK);
		DrawText("Bet", 270, 300, 20, WHITE);

		// Reset
		DrawRectangleRounded(resetButtonShadow, 0.2f, 10, BLACK);
		DrawRectangleRounded(resetButton, 0.2f, 10, GRAY);
		DrawText("Reset", 402, 302, 20, BLACK);
		DrawText("Reset", 400, 300, 20, WHITE);

		// Player's bet
		char betText[32];
		sprintf_s(betText, "Bet: %d", globalGame->GetPlayer()->GetBet());
		DrawText(betText, 12, 352, 20, BLACK);
		DrawText(betText, 10, 350, 20, WHITE);

		// Player's money
		char moneyText[32];
		sprintf_s(moneyText, "Money: %d", globalGame->GetPlayer()->GetBalance());
		DrawText(moneyText, 12, 382, 20, BLACK);
		DrawText(moneyText, 10, 380, 20, WHITE);

		DrawText(statusText, 12, 412, 20, BLACK);
		DrawText(statusText, 10, 410, 20, WHITE);

		// Center: raylib-stuff: Blackjack
		DrawText("raylib-stuff: Blackjack", 280, 382, 20, BLACK);
		DrawText("raylib-stuff: Blackjack", 278, 380, 20, WHITE);
		
		// Center: by KiwifruitDev
		DrawText("by KiwifruitDev", 320, 412, 20, BLACK);
		DrawText("by KiwifruitDev", 318, 410, 20, WHITE);

        EndDrawing();
    }

	CloseAudioDevice();
    CloseWindow();
    return 0;
}
