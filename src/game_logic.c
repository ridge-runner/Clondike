/*
    GAME LOGIC SOURCE
    AUTHOR: BRETT VANDYKE

    Contains the source for functions referenced in 
    game_logic.h

    * Initializing function - shuffle the deck & deal starting cards to tableau.

*/

#include <ncurses.h>
#include "game_logic.h"

/* GAME STATE
    Creates the tableau, foundation, stock and waste piles.
    Tracks the status of each pile.
*/
GameState initialize_game() {
    GameState state;

    // init sizes
    for (int i = 0; i < NUM_TABLEAU; i++) {
        state.tableau_size[i] = 0;
    }
    for (int i = 0; i < NUM_FOUNDATIONS; i++) {
        state.foundation_size[i] = 0;
    }

    state.stock_size = 0;
    state.waste_size = 0;

    // create and shuffle deck
    Deck deck = create_deck();
    shuffle_deck(&deck);

    // Deal cards to the tableau from the deck
    for (int i = 0; i < NUM_TABLEAU; i++) {
        for (int j = 0; j <= i; j++) {
            state.tableau[i][j] = draw_card(&deck);
            state.tableau_size[i]++;
        }
    }

    // Remaining cards go to the stock
    while (deck.top >= 0) {
        state.stock[state.stock_size++] = draw_card(&deck);
    }

    return state;
}

/* Move Waste to Tableau
    Moves a waste card to the tableau pile
*/

bool move_waste_to_foundation(GameState *state, int foundationIndex) {
    if (state->waste_size <= 0) return false; // No cards in waste

    Card wasteCard = state->waste[state->waste_size - 1];
    if (state->foundation_size[foundationIndex] > 0) {
        Card topFoundationCard = state->foundation[foundationIndex][state->foundation_size[foundationIndex] - 1];
        // Check if the move is valid (same suit and one rank higher)
        if (!is_valid_foundation_move(wasteCard, topFoundationCard)) return false;
    }

    // Move the card
    state->foundation[foundationIndex][state->foundation_size[foundationIndex]++] = wasteCard;
    state->waste_size--;
    return true;
}

/*
    MOVE WASTE TO TABLEAU
*/
bool move_waste_to_tableau(GameState *state, int tableauIndex) {
    if (state->waste_size <= 0) return false; // No cards in waste

    Card wasteCard = state->waste[state->waste_size - 1];
    if (state->tableau_size[tableauIndex] > 0) {
        Card topTableauCard = state->tableau[tableauIndex][state->tableau_size[tableauIndex] - 1];
        // Check if the move is valid (opposite color and one rank lower)
        if (!is_valid_move(wasteCard, topTableauCard)) return false;
    }

    // Move the card
    state->tableau[tableauIndex][state->tableau_size[tableauIndex]++] = wasteCard;
    state->waste_size--;
    return true;
}

/*
    MOVE WITHIN TABLEAU
*/
bool move_within_tableau(GameState *state, int fromIndex, int toIndex) {
    if (state->tableau_size[fromIndex] <= 0) return false; // No cards to move

    // Get the card being moved
    Card cardToMove = state->tableau[fromIndex][state->tableau_size[fromIndex] - 1];

    if (state->tableau_size[toIndex] > 0) {
        Card topToCard = state->tableau[toIndex][state->tableau_size[toIndex] - 1];
        if (!is_valid_move(cardToMove, topToCard)) return false;
    }

    // Move the card
    state->tableau[toIndex][state->tableau_size[toIndex]++] = cardToMove;
    state->tableau_size[fromIndex]--;
    return true;
}

/*
    MOVE TABLEAU TO FOUNDATION
*/
bool move_tableau_to_foundation(GameState *state, int tableauIndex, int foundationIndex) {
    if (state->tableau_size[tableauIndex] <= 0) return false; // No cards to move

    // Get the card being moved
    Card cardToMove = state->tableau[tableauIndex][state->tableau_size[tableauIndex] - 1];

    if (state->foundation_size[foundationIndex] > 0) {
        Card topFoundationCard = state->foundation[foundationIndex][state->foundation_size[foundationIndex] - 1];
        if (!is_valid_foundation_move(cardToMove, topFoundationCard)) return false;
    }

    // Move the card
    state->foundation[foundationIndex][state->foundation_size[foundationIndex]++] = cardToMove;
    state->tableau_size[tableauIndex]--;
    return true;
}

/*
    FLIP TABLEAU CARD
*/
bool flip_tableau_card(GameState *state, int tableauIndex) {
    // This depends on how you're representing face-down vs face-up cards
    // Assuming you have a way to check if the top card is face-down

    if (is_top_card_face_down(state, tableauIndex)) {
        flip_card(&state->tableau[tableauIndex][state->tableau_size[tableauIndex] - 1]);
        return true;
    }
    return false;
}

/*
    Validating moves
*/
#include "game_logic.h"

bool is_opposite_color(Card card1, Card card2) {
    // Assuming even numbers for red suits (hearts, diamonds) and odd for black (spades, clubs)
    return (card1.suit % 2) != (card2.suit % 2);
}

bool is_valid_move(Card card1, Card card2) {
    // card1 can be placed on card2 if it's of opposite color and one rank lower
    return is_opposite_color(card1, card2) && card1.rank == card2.rank - 1;
}

bool is_valid_foundation_move(Card card1, Card card2) {
    // card1 can be placed on card2 if it's the same suit and one rank higher
    return card1.suit == card2.suit && card1.rank == card2.rank + 1;
}

/************************
 * Displaying Game State
*************************/
void display_stock(const GameState *state) {
    mvprintw(0, 0, "Stock:");
    if (state->stock_size > 0) {
        mvprintw(1, 0, "[*]"); // Represent face-down card in stock
    } else {
        mvprintw(1, 0, "[ ]"); // Empty stock
    }
}

void display_waste(const GameState *state) {
    mvprintw(0, 10, "Waste:");
    if (state->waste_size > 0) {
        Card topCard = state->waste[state->waste_size - 1];
        mvprintw(1, 10, "[%d%c]", topCard.rank, topCard.suit); // Adjust to your card representation
    } else {
        mvprintw(1, 10, "[ ]"); // Empty waste
    }
}

void display_tableau(const GameState *state) {
    mvprintw(3, 0, "Tableau:");
    for (int i = 0; i < NUM_TABLEAU; i++) {
        mvprintw(4, i * 7, "Pile %d:", i + 1);
        for (int j = 0; j < state->tableau_size[i]; j++) {
            Card card = state->tableau[i][j];
            mvprintw(5 + j, i * 7, "[%d%c]", card.rank, card.suit); // Adjust to your card representation
        }
    }
}

void display_foundations(const GameState *state) {
    mvprintw(3, 50, "Foundations:");
    for (int i = 0; i < NUM_FOUNDATIONS; i++) {
        mvprintw(4, 50 + i * 7, "Fnd %d:", i + 1);
        if (state->foundation_size[i] > 0) {
            Card card = state->foundation[i][state->foundation_size[i] - 1];
            mvprintw(5, 50 + i * 7, "[%d%c]", card.rank, card.suit); // Adjust to your card representation
        } else {
            mvprintw(5, 50 + i * 7, "[ ]"); // Empty foundation
        }
    }
}



