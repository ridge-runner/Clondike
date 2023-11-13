/*
    DECK HEADER FILE
    AUTHOR: BRETT VANDYKE

    This file contains functions defining the deck structures and enums.
    For Deck cards, deck structure, shuffling, dealing.

*/

#ifndef DECK_H  // this directive detects 
#define DECK_H

// CREATE THE DECK STRUCTURE

// Defines the Suit datatype
typedef enum {
    HEART, DIAMONDS, CLUBS, SPADES
} Suit;                             

// Defines the Card structure
typedef struct {
    int rank;       // Rank of the card (1-13, Order: Ace-King)
    Suit suit;      // Suit of the card. 
} Card;

// Defines the Deck structure
typedef struct {
    Card cards[52]; // array of Cards.
    int top;        // Index of the top card
} Deck;

// function lib. See deck.c for source.
Deck create_deck();
void shuffle_deck(Deck *deck);
Card draw_card(Deck *deck);

#endif