/*
    GAME LOGIC HEADER FILE
    AUTHOR: Brett Vandyke
    
    This header file contains the logic for the game.
    Card movement between card piles. Game rules for piles,
    winning and losing.

    Objects:
    Foundation (4 piles)
    Tableau (7 piles)

    Each pile is an array (or list.)
    Game state tracks pile status.
    
    Functions: 
        move_waste_to_tableau
        move_waste_to_foundation

*/

// Inclusion guard
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "deck.h"

// constants defining no of piles.
#define NUM_TABLEAU 7
#define NUM_FOUNDATIONS 4

/* Game state struct
    Creates the tableau, foundation, stock, & waste piles.
*/
typedef struct {
    Card tableau[NUM_TABLEAU][52];
    int tableau_size[NUM_TABLEAU];

    Card foundation[NUM_FOUNDATIONS][13];
    int foundation_size[NUM_FOUNDATIONS];
    
    Card stock[52]; // stock pile array
    int stock_size;

    Card waste[52]; // waste pile array
    int waste_size;

} GameState;

GameState initialize_game();

// movement functions
bool move_waste_to_tableau(GameState *state, int tableauIndex);
bool move_waste_to_foundation(GameState *state, int foundationIndex);
bool move_within_tableau(GameState *state, int fromIndex, int toIndex);
bool move_tableau_to_foundation(GameState *state, int tableauIndex, int foundationIndex);
bool flip_tableau_card(GameState *state, int tableauIndex); // If applicable

// Prototypes for validation functions
bool is_valid_move(Card card1, Card card2);
bool is_valid_foundation_move(Card card1, Card card2);

// Display piles
void display_stock(const GameState *state);
void display_waste(const GameState *state);
void display_tableau(const GameState *state);
void display_foundations(const GameState *state);
#endif // GAME_LOGIC_H