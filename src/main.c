/*
    /////  CLONDIKE  /////
    A solitaire game built with C & nCurses.
    Author: Brett Vandyke

    A simple version of Klondike using the nCurses (new curses) library as a GUI.

*/

// - TODO - 
// Define structures for a card, deck, and game state.
// Use enums for suits and ranks.

// - Structure - 
// 1. Init ncurses mode & setup I/O settings.
// 2. card & deck functions: shuffling, dealing
// 3. Logic: Implement rules of Klodike. How cards shift piles, illegal moves
// 4. UI: ncurses functions to create a UI - display cards, player I/O, refresh
// 5. Main Loop: update UI based on User interactions.
// 6. Testing & Debugging: Test each component for fuction and memory leaks.

// ====================== //
//      MAIN.C 
// ====================== //

#include <ncurses.h>
#include "deck.h"
#include "game_logic.h"