// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#include "Queen.h"
namespace Chess {
  bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //note queen is just rook+bishop, so this is copy/paste logic from both
    //check if no move (the user wants to move to the same square)
    if (start == end) return false;
    int horizontal_distance = end.first - start.first;
    int vertical_distance = end.second - start.second;
    //absolute value (without include math)
    if (vertical_distance < 0) vertical_distance *= -1;
    if (horizontal_distance < 0) horizontal_distance *= -1;
    //check if straight movement AND diagonal
    if (start.first - end.first != 0 && start.second - end.second == 0) {
      return true;
    } else if (start.first - end.first == 0 && start.second - end.second != 0) {
      return true;
    } else if (vertical_distance == horizontal_distance) { //check diagonal movement
      return true;
    } //else
    return false;
  }
}
