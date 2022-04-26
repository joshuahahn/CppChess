// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

namespace Chess
{
  class Pawn : public Piece {

  public:
    //determines legal move shape.
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const;

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    char to_ascii() const {
      return is_white() ? 'P' : 'p';

    }
    bool legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const;

  private:
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Pawn(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}
#endif // PAWN_H
