/*
    /////  CLONDIKE  /////
    A solitaire game built with C & nCurses.
    Author: Brett Vandyke

    A simple version of Klondike using the nCurses (new curses) library as a GUI.

*/

// - TODO - 

// <DONE> 1. Init ncurses mode & setup I/O settings.
// <DONE> 2. card & deck functions: shuffling, dealing
// <STARTED> 3. Logic: Implement rules of Klodike. How cards shift piles, illegal moves
// 4. UI: ncurses functions to create a UI - display cards, player I/O, refresh
// <STARTED> 5. Main Loop: update UI based on User interactions.
// 6. Testing & Debugging: Test each component for function and memory leaks.

// ====================== //
//      MAIN.C 
// ====================== //

#include <ncurses.h>    // curses is a CLI-based GUI library
#include <stdbool.h>    // adds boolean datatypes true/false
#include "deck.h"       // cards and deck structs, functions
#include "game_logic.h" // how cards behave in game, rules.

int main (void) {

/* *******************
    nCurses UI Setup
**********************/
    // init ncurses
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    keypad(stdscr, TRUE);   // Enable function and arrow keys.

    // Check if the terminal supports color
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1; // throw error to stderror.
    }

    start_color(); // start color funct

    // define color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
        // other pairs can be included.

    /**************************
    // Main Game setup & Loop
    ***************************/
    Deck deck = create_deck();
    shuffle_deck(&deck);
    
    GameState gameState = initialize_game();
        int ch;
        bool gameRunning = true;
        int fromIndex, toIndex; // index of cards moving between piles

    // Main Game Loop
    while (gameRunning) {
        
        // Clear the screen
        clear();
        
        // Display teh game state
        display_stock(&gameState);
        display_waste(&gameState);
        display_tableau(&gameState);
        display_foundations(&gameState);

        // Refresh teh screen to show changes
        refresh();

        // Get user input
        ch = getch();

        // Process input <TODO: Break UI code into module.>
        switch(ch) {
            case 'q': // Quit the game
                gameRunning = false;
                break;
            
            case 's': // Move from stock to waste
                move_stock_to_waste(&gameState);
                break;
            
            case 'w': // Move from waste to tableau
                printw("Move to which tableau pile? ");
                scanw("%d", &toIndex);
                move_waste_to_tableau(&gameState, toIndex - 1); // Assuming user enters 1-based index
                break;
            
            case 'f': // Move from waste to foundation
                printw("Move to which foundation? ");
                scanw("%d", &toIndex);
                move_waste_to_foundation(&gameState, toIndex - 1);
                break;
            
            case 't': // Move within tableau
                printw("Move from which tableau pile? ");
                scanw("%d", &fromIndex);
                printw("Move to which tableau pile? ");
                scanw("%d", &toIndex);
                move_within_tableau(&gameState, fromIndex - 1, toIndex - 1);
                break;
            
            case 'm': // Move from tableau to foundation
                printw("Move from which tableau pile? ");
                scanw("%d", &fromIndex);
                move_tableau_to_foundation(&gameState, fromIndex - 1);
                break;
            
            case 'x': // Flip tableau card
                printw("Flip card in which tableau pile? ");
                scanw("%d", &toIndex);
                flip_tableau_card(&gameState, toIndex - 1);
                break;
            
            // <TODO: Add other cases for different actions ...>
            default:
                break;
        }

        display_game_state(gameState);
        UserAction action = get_user_action();
        update_game_state(&gameState, action);
    }

    // Clean up
    endwin();
    return 0;

} //endMain