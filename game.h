#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "./cardUtils.h"
#include "./messages.h"

using namespace std;

#define STARTING_PLAYER_HAND 5
#define PLAYER_1_NUMBER 1
#define PLAYER_2_NUMBER 2
#define DRAW_CARD_CHOICE_NUMBER 99

class Player
{

    friend class Game;

public:
    void PrintHand()
    {
        for (int i = 0; i < m_playerHand.size(); ++i)
        {
            cout << i << ". ";
            m_playerHand[i].PrintCard();
            cout << endl;
        }
    }

    int GetHandSize()
    {
        return m_playerHand.size();
    }

    void AddCardToHand(Card &card)
    {
        m_playerHand.push_back(card);
    }

    Card PickCard(int index)
    {
        return m_playerHand[index];
    }

    void RemoveCard(int index)
    {
        m_playerHand.erase(m_playerHand.begin() + index);
    }

    bool CheckHandEmpty()
    {
        return m_playerHand.size() == 0 ? true : false;
    }

    int GetPlayerNumber()
    {
        return m_playerNumber;
    }

    bool skipsRound = false;

private:
    int m_playerNumber;
    vector<Card> m_playerHand;
};

class Game
{
public:
    Game()
    {
        m_winner = 0;
        m_activePlayer = PLAYER_1_NUMBER;

        Deck deck;
        // deck.Shuffle();

        m_playingDeck = deck;

        for (int i = 0; i < 2 * STARTING_PLAYER_HAND; ++i)
        {
            Card card = m_playingDeck.Deal();
            if (i % 2 == 0)
            {
                m_player1.m_playerNumber = PLAYER_1_NUMBER;
                m_player1.AddCardToHand(card);
            }
            else
            {
                m_player2.m_playerNumber = PLAYER_2_NUMBER;
                m_player2.AddCardToHand(card);
            }
        }

        m_table.push_back(m_playingDeck.Deal());

        // TODO: m_activePlayer set to the one with highest heart card
    }

    ~Game()
    {
        gameLogger.CloseGameMessage();
    }

    Card &GetTopTableCard()
    {
        return m_table.back();
    }

    vector<Card> GetTable()
    {
        return m_table;
    }

    int GetTableSize()
    {
        return m_table.size();
    }

    void AddCardToTable(Card card)
    {
        m_table.push_back(card);
    }

    Player &GetCurrentPlyer()
    {
        return m_activePlayer == PLAYER_1_NUMBER ? m_player1 : m_player2;
    }

    void SwitchActivePlayer()
    {
        m_activePlayer == PLAYER_1_NUMBER ? m_activePlayer = PLAYER_2_NUMBER : m_activePlayer = PLAYER_1_NUMBER;
    }

    void SetWinner(int playerNumber)
    {
        m_winner = playerNumber;
        gameLogger.WinnerMessage(m_winner);
    }

    bool ValidateUserInput(string input, int handSize)
    {
        if (!all_of(input.begin(), input.end(), ::isdigit))
        {
            gameLogger.WrongUserChoiceMessage();
            return false;
        }

        int pickedCardIndex = stoi(input);

        if (pickedCardIndex == DRAW_CARD_CHOICE_NUMBER)
            return true;

        if (pickedCardIndex < 0 || pickedCardIndex >= handSize)
        {
            gameLogger.WrongUserChoiceMessage();
            return false;
        }

        return true;
    }

    bool ValidateCardChoice(Card pickedCard)
    {
        Card topCard = GetTopTableCard();
        if (topCard.GetColor() == pickedCard.GetColor())
            return true;
        if (topCard.GetValue() == pickedCard.GetValue())
            return true;

        gameLogger.WrongCardChoiceMessage();
        return false;
    }

    void DrawCardX(int numberOfCardsToDraw, Player &currentPlayer)
    {
        if (numberOfCardsToDraw > m_playingDeck.GetSize())
        {
            Card lastCardInTable = GetTopTableCard();
            m_table.pop_back();
            m_playingDeck.returnCardsToDeck(m_table);
            m_table = {};
            m_table.push_back(lastCardInTable);
        }
        for (int i = 0; i < numberOfCardsToDraw; ++i)
        {
            Card card = m_playingDeck.Deal();
            currentPlayer.AddCardToHand(card);
        }
    }

    bool SkipCheck(Player &currentPlayer)
    {
        Card &topCard = GetTopTableCard();
        if (currentPlayer.skipsRound && topCard.IsActive())
        {
            gameLogger.SkipRoundMessage();
            currentPlayer.skipsRound = false;
            topCard.Deactivate();
            return true;
        }
        return false;
    }

    void CardChoice(Player &currentPlayer)
    {
        bool validCardChoice = false;

        while (!validCardChoice)
        {
            cout << endl;
            gameLogger.DisplayTableCardMessage(GetTopTableCard());
            cout << endl;

            gameLogger.PlayerMoveQuestionMessage(currentPlayer.GetPlayerNumber());
            cout << endl;
            currentPlayer.PrintHand();
            gameLogger.DrawCardOptionMessage();

            string input;
            cin >> input;

            if (!ValidateUserInput(input, currentPlayer.GetHandSize()))
                continue;

            // TODO: Can be rafactored so stoi() call is not doubled
            int pickedCardIndex = stoi(input);
            if (pickedCardIndex == DRAW_CARD_CHOICE_NUMBER)
            {
                DrawCardX(1, currentPlayer);
                validCardChoice = true;
                continue;
            }

            Card pickedCard = currentPlayer.PickCard(pickedCardIndex);
            pickedCard.Activate();

            if (!ValidateCardChoice(pickedCard))
                continue;

            currentPlayer.RemoveCard(pickedCardIndex);
            AddCardToTable(pickedCard);
            validCardChoice = true;
            cout << endl;
        }
    }

    void CheckTableCardPenalty(Card card, Player &currentPlayer)
    {
        switch (card.GetValue())
        {
        case Value::Two:
            gameLogger.DrawXMessage(2);
            DrawCardX(2, currentPlayer);
            break;

        case Value::Three:
            gameLogger.DrawXMessage(3);
            DrawCardX(3, currentPlayer);
            break;

        case Value::Four:
            currentPlayer.skipsRound = true;
            break;

        case Value::King:
            if (card.GetColor() == Color::Heart || card.GetColor() == Color::Spade)
            {
                gameLogger.DrawXMessage(5);
                DrawCardX(5, currentPlayer);
            }
            else
            {
                gameLogger.NoPenaltyMessage();
            }
            break;

        default:
            gameLogger.NoPenaltyMessage();
            break;
        }
    }

    Player m_player1;
    Player m_player2;
    Deck m_playingDeck;
    int m_winner;
    int m_activePlayer;
    Message gameLogger;

private:
    vector<Card> m_table;
};

#endif
