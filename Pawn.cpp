// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#include "Pawn.h"

namespace Chess {
  bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    // Break early; if the pieces' columns are different, break.
    if (start.first != end.first) {
      return false;
    }   
    // If the pawn is white:
    if (this->is_white()) {
      int distance = end.second - start.second;
      if (start.second == '2') {
        return (distance == 2 || distance == 1); 
      } else if (start.second > '2') {
        return (distance == 1); 
      }   
      // Break early so it does not go into the black pawn's loop.
      return false;
    }  

    // If the pawn is black:
    if (!this->is_white()) {
      int distance = start.second - end.second;
      if (start.second == '7') {
        return (distance == 2 || distance == 1); 
      } else if (start.second < '7') {
        return (distance == 1); 
      }   
        return false;
    }
    return false;
  }
    
  bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    int horizontal_distance = end.first - start.first;
    if (horizontal_distance < 0) horizontal_distance *= -1;
    // If the pawn is white
    if (this->is_white()) {
      if (horizontal_distance == 1 && end.second - start.second == 1) {
        return true;
      }
      return false;
    }
    // If the pawn is black 
    if (!this->is_white()) { 
      if (horizontal_distance == 1 && start.second - end.second == 1) {
        return true;
      }
      return false; 
    }
    return false;
  } 

}