// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#include "Rook.h"
namespace Chess {
  bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    //rook moves horizontally, so check each horizontal (can't do both horizontals)
    if (start.first - end.first != 0 && start.second - end.second == 0) {
      return true;
    } else if (start.first - end.first == 0 && start.second - end.second != 0) {
      return true;
    } //else
    return false;
  }
}