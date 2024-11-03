#ifndef CARDUTILS_H
#define CARDUTILS_H

#include <iostream>
#include <vector>

using namespace std;

enum class Color : int8_t
{
    Heart = 0, // kier
    Diamond,   // karo
    Spade,     // pik
    Club,      // trefl

    Number,
    False = -1
};

void PrintAllColors()
{
    cout << "0. Heart" << endl;
    cout << "1. Diamond" << endl;
    cout << "2. Spade" << endl;
    cout << "3. Club" << endl;
}

void Print(Color color)
{
    switch (color)
    {
    case Color::Heart:
        cout << "Heart";
        break;
    case Color::Diamond:
        cout << "Diamond";
        break;
    case Color::Spade:
        cout << "Spade";
        break;
    case Color::Club:
        cout << "Club";
        break;
    case Color::False:
        cout << "False";
        break;
    default:
        cout << "none";
    }
}

enum class Value : uint8_t
{
    Two = 0,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,

    Number
};

void Print(Value value)
{
    switch (value)
    {
    case Value::Two:
        cout << "Two";
        break;
    case Value::Three:
        cout << "Three";
        break;
    case Value::Four:
        cout << "Four";
        break;
    case Value::Five:
        cout << "Five";
        break;
    case Value::Six:
        cout << "Six";
        break;
    case Value::Seven:
        cout << "Seven";
        break;
    case Value::Eight:
        cout << "Eight";
        break;
    case Value::Nine:
        cout << "Nine";
        break;
    case Value::Ten:
        cout << "Ten";
        break;
    case Value::Jack:
        cout << "Jack";
        break;
    case Value::Queen:
        cout << "Queen";
        break;
    case Value::King:
        cout << "King";
        break;
    case Value::Ace:
        cout << "Ace";
        break;
    default:
        cout << "none";
    }
}

class Card
{
public:
    friend class Deck;

    Card() = default;
    Card(Color color, Value value) : m_color(color), m_value(value) {}

    void PrintCard()
    {
        Print(m_color);
        cout << " ";
        Print(m_value);
    }

    Color GetColor()
    {
        return m_color;
    }

    Value GetValue()
    {
        return m_value;
    }

    void Activate()
    {
        active = true;
    }

    void Deactivate()
    {
        active = false;
    }

    bool IsActive()
    {
        return active;
    }

    bool IsAce()
    {
        return m_value == Value::Ace;
    }

private:
    Color m_color = Color::Heart;
    Value m_value = Value::Two;
    bool active = false;
};

class Deck
{
public:
    Deck()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int i = 0; i < (int)Color::Number; ++i)
        {
            for (int j = 0; j < (int)Value::Number; ++j)
            {
                m_cards.push_back(Card((Color)i, (Value)j));
            }
        }
    }

    void Print()
    {
        for (Card card : m_cards)
        {
            card.PrintCard();
            cout << endl;
        }
        cout << endl;
    }

    void Shuffle()
    {
        srand(time(NULL));
        int size = m_cards.size();

        for (int i = 0; i < size; ++i)
        {
            int index = rand() % size;
            swap(m_cards[i], m_cards[index]);
        }
    }

    Card Deal()
    {
        Card result = m_cards[m_cards.size() - 1];
        m_cards.pop_back();
        return result;
    }

    int GetSize()
    {
        return m_cards.size();
    }

    void returnCardsToDeck(vector<Card> cards)
    {
        for (Card card : cards)
        {
            card.active = false;
        }
        m_cards.insert(m_cards.end(), cards.begin(), cards.end());
    }

private:
    vector<Card> m_cards = {};
};

#endif
