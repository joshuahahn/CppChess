// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

//TODO: make sure includes are correct

#include "King.h"
namespace Chess {
  bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //check if no move (the user wants to move to the same square)
    if (start == end) return false;
    int horizontal_distance = end.first - start.first;
    int vertical_distance = end.second - start.second;
    //absolute value
    if (vertical_distance < 0) vertical_distance *= -1; 
    if (horizontal_distance < 0) horizontal_distance *= -1; 
    if (vertical_distance <= 1 && horizontal_distance <= 1) {
      return true;
    } //else
    return false;
  }
}
