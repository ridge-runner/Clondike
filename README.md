# Clondike
A solitaire card game (also know as Klondike) built using C and nCurses for CLI.

See notes in source file.

Author: Brett Vandyke

## GAME RULES

### Object of the Game
The goal is to get the four suits built onto the foundations from aces up through kings.

### The Deal
Deal out 28 cards in seven piles as follows: The first pile is one card; the second pile has two cards, and so on up to seven in the last pile. The top card of each pile is face up; all others are face down.

### The Play
The four aces form the foundations. As it becomes available, each ace must be played to a row above the piles. Cards in the appropriate suit are then played on the aces in sequence - the two, then the three, and so on - as they become available.

Any movable card may be placed on a card next-higher in rank if it is of opposite color. Example: A black five may be played on a red six. If more than one card is face up on a tableau pile, all such cards must be moved as a unit.

When there is no face-up card left on a pile, the top face-down card is turned up and becomes available.

Only a king may fill an open space in the layout. The player turns up cards from the top of the stock in groups of three, and the top card of the three may be used for building on the piles, if possible, played on a foundation. If a card is used in this manner, the card below it becomes available for play. If the up-card cannot be used, the one, two, or three cards of the group are placed face up on the waste pile, and the next group of three cards is turned up.

## PROGRAM STRUCTURE

### File List
* main.c : contains the game loop and UI logic
* game_logic.c : Implementations of functions
* game_logic.h : Game rules
* deck.h : contains the structures for card, deck, draw and shuffle functions.
* deck.c : Implements the structures and functions in deck.h


## HOW TO PLAY THE GAME
### UI OPTIONS
* q: quit program
* s: Move card from stock to waste
* w: Move from waste to tableau
* f: Move from waste to foundation
* t: Move within tableau
* m: Move from tableau to foundation
* x: Flip tableau card



