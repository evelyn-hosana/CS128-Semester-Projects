#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

// THIS FUNCTION WORKS
void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}
std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
void DropDiskToBoard(Board& b, DiskType disk, int col) {
  bool slot_found = false;
  if (!(BoardLocationInBounds(0, col))) {
    throw std::runtime_error("Invalid column provided, board is not that big");
  }
  for (unsigned a = 0; a < Board::kBoardWidth; a++) {
    if (b.board[a][col] == DiskType::kEmpty) {
      b.board[a][col] = disk;
      slot_found = true;
      break;
    }
  }
  if (!slot_found) {
    throw std::runtime_error("Row is filled");
  }
}

// CREATE HELPER FUNCTIONS TO CHECK HORIZONTAL, VERTICLE, LEFT, AND RIGHT
// WINNINGS
bool WinningDirectionHorizontal(Board& b, DiskType disk) {
  bool four_in_row = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (j + 3 >= Board::kBoardWidth) {
        break;
      }
      if (b.board[i][j] == disk && b.board[i][j + 1] == disk &&
          b.board[i][j + 2] == disk && b.board[i][j + 3] == disk) {
        four_in_row = true;
      }
    }
  }
  return four_in_row;
}
bool WinningDirectionVertical(Board& b, DiskType disk) {
  bool four_in_col = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (i + 3 >= Board::kBoardHeight) {
        break;
      }
      if (b.board[i][j] == disk && b.board[i + 1][j] == disk &&
          b.board[i + 2][j] == disk && b.board[i + 3][j] == disk) {
        four_in_col = true;
      }
    }
  }
  return four_in_col;
}
bool WinningDirectionRightDiag(Board& b, DiskType disk) {
  bool four_in_right_diag = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (i + 3 >= Board::kBoardHeight) {
      break;
    }
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (i + 3 >= Board::kBoardHeight || j + 3 >= Board::kBoardWidth) {
        break;
      }
      if (b.board[i][j] == disk && b.board[i + 1][j + 1] == disk &&
          b.board[i + 2][j + 2] == disk && b.board[i + 3][j + 3] == disk) {
        four_in_right_diag = true;
        break;
      }
    }
  }
  return four_in_right_diag;
}
bool WinningDirectionLeftDiag(Board& b, DiskType disk) {
  bool four_in_left_diag = false;
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (i + 3 >= Board::kBoardHeight) {
      break;
    }
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (j - 3 >= Board::kBoardWidth) {
        break;
      }
      if (b.board[i][j] == disk && b.board[i + 1][j - 1] == disk &&
          b.board[i + 2][j - 2] == disk && b.board[i + 3][j - 3] == disk) {
        four_in_left_diag = true;
        break;
      }
    }
  }
  return four_in_left_diag;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  bool winner = false;
  if (to_check == WinningDirection::kHorizontal) {
    winner = WinningDirectionHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    winner = WinningDirectionVertical(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    winner = WinningDirectionRightDiag(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    winner = WinningDirectionLeftDiag(b, disk);
  }
  return winner;
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool winner = false;
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    winner = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    winner = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    winner = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    winner = true;
  }
  return winner;
}

// THIS FUNCTION WORKS
bool BoardLocationInBounds(int row, int col) {
  bool within_range = false;
  if (col >= 0 && row >= 0) {
    if (col <= Board::kBoardHeight && row <= Board::kBoardWidth) {
      within_range = true;
    }
  } else {
    within_range = false;
  }
  return within_range;
}
