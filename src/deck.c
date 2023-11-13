/*
    Deck source file
    Author: Brett Vandyke

    Contains the implementation of the functions declared in 'deck.h'

*/

#include "deck.h"   // access to card and deck structs.
#include <stdlib.h> // provides access to basic system functions

/*Create a Deck Struct and fill with 52 Cards.
    2D array composed of suits & ranks defined in deck.h.
    Enum assigns a number to each object (H=1, S=4).
    Ranks run to 13. Each suit is paired to a rank one time
    and saved to the deck struct.
*/
Deck create_deck() {
    Deck deck;
    int cardIndex = 0;

    for (int suit = HEARTS; suit <= SPADES; suit++) {
        for(int rank = 1; rank <= 13; rank++) {
            deck.cards[cardIndex].suit = suit;
            deck.cards[cardIndex].rank = rank;
            cardIndex++;
        }
    }

    deck.top = 51; // last card index in 52 card deck (52-1)
    return deck;
}

/* SHUFFLE Function
    Fisher-Yates algo used (see wikipedia.org article.)
    Loops down from top card (#52). Randomly selects j.
*/
void shuffle_deck(Deck *deck) {
    for (int i = deck->top; i > 0; i--) {
        int j = rand() % (i + 1); 

        //rand card swaps
        Card temp = deck->cards[i];         // copies current card
        deck->cards[i] = deck->cards[j];    // overwrites card i
        deck->cards[j] = temp;              // overwrites card j
    }

}

/* Draw Card / Deal Function

*/

const Card EMPTY_CARD = {0,0}; // Assumed that 0 is not valid.

Card draw_card(Deck *deck) {
    
    // Event handler for empty deck.
    if (deck->top < 0) {
        // the deck is empty
        return EMPTY_CARD;
    }

    Card drawnCard = deck->cards[deck->top];
    deck->top--;

    return drawnCard;
}

/*
    --- NOTES ---
    -> deref operator combines the * and . operators into one.
    shortens (*ptr).member to ptr->member.
    
    *EXAMPLE*
    int topCardIndex = deck->top; // accesses the top memb of Deck through addr pointer.
*/