#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

const int NUM_CARDS = 52;
const int NUM_VALUES = 13;
const int NUM_SUITS = 4;
const int SMALLEST_VALUE = 2;

typedef struct
{
    int value;
    int suit;
} Card;

int compute_score(Card card)
{
    return (card.value + (NUM_VALUES - SMALLEST_VALUE)) % NUM_VALUES * NUM_SUITS + (card.suit - 1);
}

Card from_score(int score)
{
    Card card = {
        (score / NUM_SUITS + SMALLEST_VALUE) % 13,
        (score % NUM_SUITS + 1),
    };
    return card;
}

void print_card(Card card)
{
    switch (card.value)
    {
    case 1:
        printf("Ace");
        break;
    case 11:
        printf("Jack");
        break;
    case 12:
        printf("Queen");
        break;
    case 13:
        printf("King");
        break;
    default:
        printf("%d", card.value);
        break;
    }

    printf(" of ");

    switch (card.suit)
    {
    case 1:
        printf("Clubs");
        break;
    case 2:
        printf("Spades");
        break;
    case 3:
        printf("Diamonds");
        break;
    case 4:
        printf("Hearts");
        break;
    }

    printf("\n");
}

Card draw_card(bool *deck)
{
    int score;
    bool drawed = true;
    while (drawed)
    {
        score = rand() % NUM_CARDS;
        drawed = deck[score];
        deck[score] = true;
    }
    return from_score(score);
}

int compare_cards(Card card1, Card card2)
{
    int score1 = compute_score(card1);
    int score2 = compute_score(card2);

    if (score1 < score2)
    {
        return -1;
    }
    else if (score1 == score2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    srand(time(NULL));

    bool deck[NUM_CARDS] = {[0 ... NUM_CARDS - 1] = false};

    Card card1 = draw_card(deck);
    print_card(card1);
    Card card2 = draw_card(deck);
    print_card(card2);

    if (compare_cards(card1, card2) > 0)
    {
        printf("Player 1 wins\n");
    }
    else if (compare_cards(card1, card2) == 0)
    {
        printf("There is a tie\n");
    }
    else
    {
        printf("Player 2 wins\n");
    }
}