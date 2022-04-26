// Joshua Hahn jhahn19
// Kevin Kim kkim170
// Elissa Matlock ematloc1

#include <cassert>
#include "Game.h"
#include <sstream> 

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
    // Make a copy of the game, and get its board.
    Game next_move(*this);

    // Throw exception if the starting position is not on the board:
    if (!(start.first <= 'H' && start.first >= 'A' && start.second <= '8' && start.second >= '1')) {
      throw Exception("start position is not on board");
    }
    // Throw exception if the ending position is not on the board:
    if (!(end.first <= 'H' && end.first >= 'A' && end.second <= '8' && end.second >= '1')) {
      throw Exception("end position is not on board");
    }
    // Throw exeption if there is no piece at the starting position:
    if (next_move.board(start) == nullptr) {
      throw Exception("no piece at start position");
    }

    // Throw exception if piece color and turn do not match
    if (next_move.board(start)->is_white() != next_move.turn_white()) {
      throw Exception("piece color and turn do not match");
    }

    // Throw exception if the proposed move has an illegal shape.
    if (next_move.board(end) == nullptr && !(next_move.board(start)->legal_move_shape(start, end))) {
      throw Exception("illegal move shape");
    }

    // Throw exception if attempting to capture own piece.
    if (next_move.board(end) != nullptr && next_move.board(start)->is_white() == next_move.board(end)->is_white()) {
      throw Exception("cannot capture own piece");
    }

    // Throw exception if the proposed move has an illegal capture shape.
    if (next_move.board(end) != nullptr && !(next_move.board(start)->legal_capture_shape(start, end))) {
      throw Exception("illegal capture shape");
    }

    // Throw exception if the path is not clear.
    if (!next_move.path_clear(start, end)) {
      throw Exception("path is not clear");
    }

    char start_piece = next_move.board(start)->to_ascii();
    next_move.board.delete_piece(start);
    // If the move is not a capture
    if (next_move.board(end) == nullptr) {
      next_move.board.add_piece(end, start_piece);
    } 
    // If the move is a capture
    else {
      // Swap pieces
      next_move.board.delete_piece(end);
      next_move.board.add_piece(end, start_piece);
    }
    // If the move doesn't leave the current player in check
    if (!next_move.in_check(this->turn_white())) {
      // Now we make the changes to the actual board.

      char real_start = board(start)->to_ascii();
      // If the move is not a capture
      if (board(end) == nullptr) {
        board.add_piece(end, real_start);
        board.delete_piece(start);
      }
      // If the move is a capture
      else {
        // Swap pieces.
        board.delete_piece(start);
        board.delete_piece(end);
        board.add_piece(end, real_start);
      }
      // Pawn promotion:
      // If the white pawn reaches rank 8:
      if (board(end)->to_ascii() == 'P' && end.second == '8'){
        board.delete_piece(end);
        board.add_piece(end, 'Q');
      }
      // If the black pawn reaches rank 1:
      if (board(end)->to_ascii() == 'p' && end.second == 1) {
        board.delete_piece(end);
        board.add_piece(end, 'q');
      }
    } else {
      // If the move leaves the king in check, we make no real moves.
      throw Exception("move exposes check");
    } 

    // Switching turns
    if (this->turn_white()) {
      this->set_turn(false);
    } else {
      this->set_turn(true);
    }
  }

  // Seeing if there is a piece in the proposed path. 
  bool Game::path_clear(std::pair<char, char> start, std::pair<char, char> end) const {
    // Make copies of the game to test the function.
    Game temp_game(*this);
    Board temp_board = temp_game.get_board();

    std::pair<char, char> temp (' ', ' ');
    int vert_distance = start.second - end.second;
    int hor_distance = start.first - end.first;
    int start_pos = -1;
    int end_pos = -1;
    // Case: Moving in straight lines (vertical) with distance >= 2
    if (hor_distance == 0 && (vert_distance >= 2 || vert_distance <= -2)) {
      temp.first = start.first;
      // Determine whether to iterate from end to start or start to end. 
      if (end.second > start.second) {
        start_pos = start.second;
        end_pos = end.second;
      } else if (start.second > end.second){
        start_pos = end.second;
        end_pos = start.second;
      }
      // Iterate through the pieces in between start and end.
      for (int i = start_pos + 1; i < end_pos; i++) {
        temp.second = i;
        if (temp_board(temp) != nullptr) {
          return false;
        }
      }
    }
    // Case: Moving in striaght lines (horizontal) with distance >= 2
    // Cane.get be else since a move can't be only vertical AND only horizontal.
    else if (vert_distance == 0 && (hor_distance >= 2 || hor_distance <= -2)) {
      temp.second = start.second;
      // Determine whether to iterate from end to start or start to end. 
      if (end.first > start.first) {
        start_pos = start.first;
        end_pos = end.first;
      } else if (start.first > end.first) {
        start_pos = end.first;
        end_pos = start.first;
      }
      // Iterate through the pieces in between start and end.
      for (int i = start_pos + 1; i < end_pos; i++) {
        temp.first = i;
        if (temp_board(temp) != nullptr) {
          return false;
        }
      }
    }
    
    // Case: Moving in diagonals (along y = x)
    if (vert_distance == hor_distance) {
      if (end.first > start.first) {
        int temp_vert_distance = vert_distance;
        if (vert_distance < 0) temp_vert_distance = -1 * vert_distance;
        for (int i = 1; i < temp_vert_distance; i++) {
          temp.first = start.first + i;
          temp.second = start.second + i;
          if (temp_board(temp) != nullptr) {
            return false;
          }
        }
      }
      else if (start.first > end.first) {
        if (vert_distance < 0) vert_distance *= -1;
        for (int i = 1; i < vert_distance; i++) {
          temp.first = start.first - i;
          temp.second = start.second - i;
          if (temp_board(temp) != nullptr) {
            return false;
          }
        } 
      }
    }
    // Case: Moving in diagonals (along y = -x)
    if (vert_distance == -1 * hor_distance) {
      if (end.first > start.first) {
        if (hor_distance < 0) hor_distance *= -1;
        for (int i = 1; i < hor_distance; i++) {
          temp.first = start.first + i;
          temp.second = start.second - i;
          if (temp_board(temp) != nullptr) {
            return false;
          }
        }
      }  
      else if (start.first > end.first) {
        if (vert_distance < 0) vert_distance *= -1;
        for (int i = 1; i < vert_distance; i++) {
          temp.first = start.first - i;
          temp.second = start.second + i;
          if (temp_board(temp) != nullptr) {
            return false;
          }
        }
      }
    }
    return true;
  }

  bool Game::is_under_attack(bool white, std::pair <char, char> square) const {
    //iterate through every piece, and return true if a single enemy piece is attacking square
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
        std::pair<char, char> temp_pos (c,r);
        const Piece *temp_piece = board(temp_pos);
        //if enemy piece exists on current square
        if (temp_piece != nullptr && white != temp_piece->is_white()) {
          //if the square is in the capture shape of the piece AND path is clear
          if (temp_piece->legal_capture_shape(temp_pos, square) && this->path_clear(temp_pos, square)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool Game::in_check(bool white) const {
    std::pair<char, char> curr_king_pos = this->king_position(white);
    //return true if king square is under attack
    return is_under_attack(white, curr_king_pos);
  }

  bool Game::is_in_board(std::pair<char, char> pos) const {
    if (pos.first >= 'A' && pos.first <= 'H' && pos.second >= '1' && pos.second <= '8') return true;
    //else
    return false;
  }

  bool Game::in_mate(bool white) const {
    if (!in_check(white)) {
      // Early break if the king is not in check
      return false;
    }
    //make copy of game object
    Board temp_board(board);
    //also get position of king
    std::pair<char, char> curr_king_pos = king_position(white);
    
    //check for if king can move out of check
    std::pair<char, char> tkp = curr_king_pos;
    //array of pairs for all adjacent tiles (including ones that might be out of board)
    std::pair<char, char> adj[8] =
    {
      std::make_pair(tkp.first,tkp.second+1),
      std::make_pair(tkp.first+1,tkp.second),
      std::make_pair(tkp.first+1,tkp.second+1),
      std::make_pair(tkp.first-1,tkp.second),
      std::make_pair(tkp.first,tkp.second-1),
      std::make_pair(tkp.first-1,tkp.second-1),
      std::make_pair(tkp.first-1,tkp.second+1),
      std::make_pair(tkp.first+1, tkp.second-1)
    };
    //loop through each adjacent square
    for (int i = 0; i < 8; i++) {
      //check if square is in the board
      if (is_in_board(adj[i])) {
        //check is square is under attack or if enemy piece is capturable
        if (!(is_under_attack(white, adj[i])) && (temp_board(adj[i]) != nullptr && temp_board(adj[i])->is_white() != white)) {
          //early break if the king can move to a tile
          return false;
        }
      }
    }
    
    //determine if an ally piece can get between the checking enemy piece and the king
    //also includes captures
    std::pair<char, char> temp_pos (' ', ' ');
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
        std::pair<char, char> temp_pos(c,r);
        const Piece *temp_piece = temp_board(temp_pos);
        //if enemy piece exists
        if (temp_piece != nullptr && white == temp_piece->is_white()) {
          if(try_every_move(temp_pos)) return false;  
        }
      }
    }
    return true;
  }

  // Returns true if a move is possible.
  bool Game::try_every_move(std::pair<char, char> pos) const {
    //try every move of a piece at position pos
    Game temp_game(*this);
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
        std::pair<char, char> temp_pos(c,r);
        try {
          temp_game.make_move(pos, temp_pos);
          //return true once a single move is possible
          return true;
        } catch (const std::exception &e) {
          //empty body
        }
      }
    }
    return false;
  }

  // Returns true if the game is in stalemate.
  bool Game::in_stalemate(bool white) const {
    //break early if in check
    if (this->in_check(white)) {
      return false;
    }
    Game temp_game(*this);
    Board temp_board(board);
    //iterate through every piece
    for (char r = '8'; r >= '1'; r--) {
      for (char c = 'A'; c <= 'H'; c++) {
        std::pair<char, char> temp_pos(c,r);
        const Piece *temp_piece = temp_board(temp_pos);
        if (temp_piece != nullptr && white == temp_piece->is_white()) {
          //for every piece, try every concievable move (break immediately if a single move is possible)
          if(temp_game.try_every_move(temp_pos)) return false;
        }
      }
    }
    return true;
  }

  std::istream& operator>> (std::istream& is, Game& game) {
    //Read the board, character by character, and assign that character to the board
    //Board temp_board = game.get_board();
    //store the istream into a buffer of 65+8 characters (board + newline)
    char *buf = new char[73];
    is.read(buf, 73);
    //iterate through the buffer and add pieces when valid
    char input_char = ' ';
    //chars that store position
    char r = '8';
    char c = 'A';
    for (int i = 0; i < 72; i++) {
      //only update when buf[i] is not '\n'
      if (buf[i] != '\n') {
        input_char = buf[i];
        std::pair<char, char> temp_pos (c,r);
        //add/delete piece accordingly based on input_char
        if (game.board(temp_pos) != nullptr) {
          game.board.delete_piece(temp_pos);
        }
        if (input_char != '-') {
          game.board.add_piece(temp_pos,input_char);
        }
        //update c and r
        if (c == 'H') {
          c = 'A';
          r--;
        } else {
          c++;
        }
      }
      //clear input_char
      input_char = ' ';
    }
    //read the turn (w or b)
    input_char = buf[72];
    if (input_char == 'w') {
      game.set_turn(true);
    } else if (input_char == 'b') {
      game.set_turn(false);
    }
    delete[] buf;
    return is;
  }

  // Returns a pair of characters that gives the specified king's position
  std::pair<char, char> Game::king_position(bool white) const {
    // Use the board that the game has.
    Board temp_board(board);
    // Set the king character correctly according to color.
    char kingchar = ' ';
    if (white) {
      kingchar = 'K';
    } else {
      kingchar = 'k';
    }
    // Initializing temporary pairs to be used throughout the iteration.
    std::pair<char, char> temp_pos (' ', ' ');
    std::pair<char, char> curr_king_pos (' ', ' ');
    // Iterating through the board. 
    for (int i = 0; i < 8; i++) {
      temp_pos.first = 'A' + i;
      for (int j = 0; j < 8; j++) {
        temp_pos.second = '1' + j;
        if (board(temp_pos) != nullptr) {
          const Piece *temp = board(temp_pos);
          //determine if piece is desired king
          if ((temp->is_white() == white) && temp->to_ascii() == kingchar) {
            //store curr_king_pos if found
            curr_king_pos.first = 'A' + i;
            curr_king_pos.second = '1' + j;
            //break out of for loop
            i = 8;
            j = 8;
          }
        } 
      }
    }
    // Return the pair that we saved above.
    return curr_king_pos;
  }

  // Setter function for is_white_turn
  void Game::set_turn(bool white) {
    if(white) {
      this->is_white_turn = true;
    } else {
      this->is_white_turn = false;
    }
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }
}
