// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
// #include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}
// DROP DISK FUNCTION
TEST_CASE("Runtime errors with drop disk function", "[drop-disk-errors]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
}
// SEARCH FOR WINNER TEST CASES
TEST_CASE("Searching for winner horizontally", "[search-winner-horizontal]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
}
TEST_CASE("Searching for winner vertically", "[search-winner-vertically]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
}
TEST_CASE("Searching for winner right diagonally", "[search-winner-right-diagonally]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
}
TEST_CASE("Searching for winner left diagonally", "[search-winner-left-diagonally]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == true);
}
// CHECK FOR WINNER TEST CASES
TEST_CASE("Checking for winner horizontally", "[winner-check-horizontally]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
}
TEST_CASE("Checking for winner vertically", "[winner-check-vertically]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
}
TEST_CASE("Checking for winner right diagonally", "[winner-check-right-diagonally]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
}
TEST_CASE("Checking for winner left diagonally", "[winner-check-left-diagonally]") {
  Board student;
  InitBoard(student);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1) == true);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, Board::kBoardWidth) == false);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 75), std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
}
// BOARD LOCATION TEST CASE
TEST_CASE("Testing if board is in bounds", "[board-location]") {
  REQUIRE(BoardLocationInBounds(3, 5) == true);
  REQUIRE(BoardLocationInBounds(1, 15) == false);
  REQUIRE(BoardLocationInBounds(5, -3) == false);
}
// PLayer 1 first, THEN player 2
TEST_CASE("No one wins", "[no-win]") {
  Board student{};
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
}