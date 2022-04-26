// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

  class Game {

  public:
    // This default constructor initializes a board with the standard
    // piece positions, and sets the state to white's turn
    Game();

    // Returns a constant reference to the board
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    const Board& get_board() const { return board; }

    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }

    // Attemps to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(std::pair<char, char> start, std::pair<char, char> end);
    
    //returns true if the path is clear between two positions (enemy or ally piece)
    bool path_clear(std::pair<char, char> start, std::pair<char, char> end) const;

    //returns true if the square is under attack by enemy player
    bool is_under_attack (bool white, std::pair <char, char> square) const;

    // Returns true if the designated player is in check
    bool in_check(bool white) const;

    // Returns true if the designated position is in the board
    bool is_in_board(std::pair<char, char> pos) const;

    // Returns true if the designated player is in mate
    bool in_mate(bool white) const;

    // Returns true if there is a possible move from the piece
    bool try_every_move(std::pair<char, char> pos) const;

    // Returns true if the designated player is in mate
    bool in_stalemate(bool white) const;

    // Setter function for is_white_turn
    void set_turn(bool white);

    // Reads the board in from a stream
    friend std::istream& operator>>(std::istream& is, Game& game);

  private:
    // The board
    Board board;

    // Is it white's turn?
    bool is_white_turn;

    // Helper function that returns the position of the specified color's king.
    std::pair<char, char> king_position(bool white) const;

  };

  // Writes the board out to a stream
  std::ostream& operator<< (std::ostream& os, const Game& game);
}
#endif // GAME_H
