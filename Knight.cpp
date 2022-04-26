// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#include "Knight.h"

namespace Chess {
  bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    int horizontal_distance = end.first - start.first; 
    int vertical_distance = end.second - start.second;
    //absolute value of distance 
    if (horizontal_distance < 0) horizontal_distance *= -1;
    if (vertical_distance < 0) vertical_distance *= -1;
    if (vertical_distance == 2 && horizontal_distance == 1) {	  
      return true;
    } else if (vertical_distance == 1 && horizontal_distance == 2) {
      return true;
    }
    return false;
  }
}
