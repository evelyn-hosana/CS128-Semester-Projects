#include <iostream>

#include "board.hpp"

int main() {
  Board student{};
  InitBoard(student);
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
  std::cout << BoardToStr(student) << std::endl;
  return 0;
}