#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include "./cardUtils.h"

using namespace std;

class Message
{
public:
    void CloseGameMessage()
    {
        cout << "Game closed" << endl;
    }

    void WinnerMessage(int winner)
    {
        cout << "The winner is player: " << winner << endl;
    }

    void DrawCardOptionMessage()
    {
        cout << "Type: 99 to draw a card" << endl;
    }

    void PlayerMoveQuestionMessage(int playerNumber)
    {
        cout << "What is your move player " << playerNumber << " ?" << endl;
    }

    void DisplayTableCardMessage(Card card)
    {
        cout << "On the table is: " << endl;
        card.PrintCard();
        cout << endl;
    }

    void WrongUserChoiceMessage()
    {
        cout << "Your choice was not a number, or is outside the range." << endl;
    }

    void WrongCardChoiceMessage()
    {
        cout << "Remember that card has to mach either value or the color." << endl;
        cout << "If you dont have a matching card then type 99 to draw from the deck." << endl;
    }
};

#endif