/*
    DECK HEADER FILE
    AUTHOR: BRETT VANDYKE

    This file contains functions defining the deck structures and enums.
    For Deck cards, deck structure, shuffling, dealing functions, see deck.c

*/

#ifndef DECK_H  // An include guard, see description below.
#define DECK_H

// CREATE THE DECK STRUCTURE

// Defines the Suit datatype
typedef enum {
    HEARTS, DIAMONDS, CLUBS, SPADES
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

// function lib. See deck.c for function definitions.
Deck create_deck();
void shuffle_deck(Deck *deck); // * denotes pointer operator to Deck struct.
Card draw_card(Deck *deck);

#endif

/*  ------- NOTES -------
    INCLUDE GUARDS
    Prevents multiple inclusions of the same header file,
    Which prevents redifinition of classes, structures, and functions.

    * #ifndef DECK_H: if not defined and name of header.
        checks to see if DECK_H has not been defined.

    * #define DECK_H: Prevents code in the guard from being included again

    * #endif: Marks end of the #ifndef block.
      If DECK_H defined, skip the enclosed code.

*/