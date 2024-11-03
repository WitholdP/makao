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

		if (game.SkipCheck(currentPlayer))
		{
			game.SwitchActivePlayer();
			continue;
		}

		game.CardChoice(currentPlayer);

		bool winCheck = currentPlayer.CheckHandEmpty();
		if (winCheck)
			game.SetWinner(currentPlayer.GetPlayerNumber());

		round++;
		game.SwitchActivePlayer();
	}

	return 0;
}
