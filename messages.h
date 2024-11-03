#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include "./cardUtils.h"
#include "./game.h"

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

    void NoPenaltyMessage()
    {
        cout << "You do not have a penalty." << endl;
    }

    void DrawXMessage(int x)
    {
        cout << "You have to draw " << x << " cards." << endl;
    }

    void SkipRoundMessage()
    {
        cout << "You Have to skip this round." << endl;
    }

    void PickAceDemandMessage()
    {
        cout << "Which color you would like to demand?" << endl;
    }

    void AceColorChangeMessage(Color color)
    {
        cout << endl;
        cout << "Color has been changed to: ";
        Print(color);
        cout << endl;
    }

    void AceColorChangeReminder(Color color)
    {
        cout << endl;
        cout << "Remember that color has been changed to: ";
        Print(color);
        cout << endl;
    }

    void PickJackDemandMessage()
    {
        cout << "Which value you would like to demand?" << endl;
    }

    void JackValueDemandMessage(Value value)
    {
        cout << endl;
        cout << "Value has been demanded: ";
        Print(value);
        cout << endl;
    }

    void JackValueDemandReminder(Value value)
    {
        cout << endl;
        cout << "Remember that value has been changed to: ";
        Print(value);
        cout << endl;
    }
};

#endif
