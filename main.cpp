#include <iostream>
#include <vector>
#include "./cardUtils.h"
#include "./game.h"

using namespace std;

int main()
{
	Game game;
	int round = 0;

	while (game.m_winner == 0)
	{
		Player &currentPlayer = game.GetCurrentPlyer();
		cout << endl;
		Card &topCard = game.GetTopTableCard();

		if (round != 0)
		{
			game.CheckTableCardPenalty(topCard, currentPlayer);
		}

		if (currentPlayer.skipsRound && topCard.IsActive())
		{
			game.gameLogger.SkipRoundMessage();
			currentPlayer.skipsRound = false;
			topCard.Deactivate();
			game.SwitchActivePlayer();
			continue;
		}

		game.CardChoice(currentPlayer);

		bool winCheck = currentPlayer.CheckHandEmpty();
		if (winCheck)
		{
			game.SetWinner(currentPlayer.GetPlayerNumber());
		}
		round++;
		game.SwitchActivePlayer();
	}

	return 0;
}
