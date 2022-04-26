// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1
#include "Bishop.h"
namespace Chess {

  bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //check if no move (the user wants to move to the same square)
    if (start == end) return false;
    int horizontal_distance = end.first - start.first;
    int vertical_distance = end.second - start.second;
    //absolute value (without include math)
    if (vertical_distance < 0) vertical_distance *= -1; 
    if (horizontal_distance < 0) horizontal_distance *= -1; 
    if (vertical_distance == horizontal_distance) {
      return true;
    } //else
    return false;
  }
}
