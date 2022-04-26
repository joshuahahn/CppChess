#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"

// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  // Board Copy Constructor
  Board::Board(const Board &rhs) {
    std::map<std::pair<char, char>, Piece*>::const_iterator it;
    for (it = rhs.occ.begin(); it != rhs.occ.end(); it++) {
      add_piece(it->first, it->second->to_ascii());
    }
  }

  // Board Destructor
  Board::~Board() {
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.cbegin(); it != occ.cend(); it++) {
      delete it->second;
    }
    occ.clear();
  }

  const Piece* Board::operator()(std::pair<char, char> position) const {
    // This is an iterator that iteratres through a map of type position and Piece*.
    // We want this iterator to go through the board and look for the Piece
    // stored at the position. If no piece is there, the iterator should reach the
    // end of the map at the end of the find() sequence.
    
    std::map<std::pair<char, char>, Piece*>::const_iterator it; 
    it = this->occ.find(position);
    if (it != occ.end()) {
      return it->second;
    }
    return nullptr;
  }
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    this->occ[position] = create_piece(piece_designator);
    return true;
  }

  // Deletes the piece at the given position.
  void Board::delete_piece(std::pair<char, char> position) {
    if ((*this)(position) != nullptr) {
      delete occ[position];
      occ.erase(position);
    }
  }

  bool Board::has_valid_kings() const {
    // Variables used to work through the boolean.
    std::pair<char, char> temp_pos; 
    char temp_piece;
    unsigned num_kings = 0;
    
    // Iterate through all positions of the chessboard by using a nested for loop.
    for (int i = 'A'; i < 'I'; i++) {
      temp_pos.first = i;
      for (int j = '1'; j < '9'; j++) {
        temp_pos.second = j;
        // Set a char to be the ascii of the piece at the position if the 
        // position is not a nullptr (has a piece).
        if ((*this)(temp_pos) != nullptr) {
          temp_piece = (*this)(temp_pos)->to_ascii();
          // If we find a king, we increase the number of kings.
          if (temp_piece == 'k' || temp_piece == 'K') {
            num_kings++;
          }
        }
        if (num_kings == 2) {
          return true;
        }
      }
    }
    // If we iterate through all of the positions and haven't found 2 kings, 
    // it means that there are an incorrect number of kings. Return false.
    return false;
  }

  void Board::display() const {
    // A temporary position pair to iterate through all of the board's positions.
    std::pair<char, char> position;
    std::map<std::pair<char, char>, Piece*> map = this->occ;
    std::map<std::pair<char, char>, Piece*>::const_iterator it;
    std::cout << " ╔═══════════════╗" << std::endl;
    // Iterate through the 8 rows, starting from row 8.
    for (int i = 0; i < 8; i++) {
      int row = 8 - i;
      std::cout << row << "║";
      position.second = '8' - i;
      for (char j = 'A'; j < 'H'; j++) {
        position.first = j;
        it = this->occ.find(position);
        if (it != occ.end()) {
          std::cout << map.at(position)->to_ascii() << ".";
        } else {
          std::cout << " .";
        }
      }
      position.first = 'H';
      it = this->occ.find(position);
      if (it != occ.end()) {
          std::cout << map.at(position)->to_ascii() << "║" << std::endl;
        } else {
          std::cout << " ║" << std::endl;
        }
      }
    std::cout << " ╚═══════════════╝" << std::endl;
    std::cout << "  a b c d e f g h" << std::endl;
  }
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

}
