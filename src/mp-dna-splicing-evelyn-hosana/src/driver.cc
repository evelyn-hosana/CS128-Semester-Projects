#include <iostream>

#include "dna_strand.hpp"

int main() {
  DNAstrand dna2;
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  dna2.PushBack('a');
  char pattern3[] = "aaa";

  DNAstrand dna1;
  dna1.PushBack('a');
  dna1.PushBack('c');
  dna1.PushBack('t');

  dna2.SpliceIn(pattern3, dna1);
  Node* curr = dna2.GetHead();
  while (curr != nullptr) {
    std::cout << curr->data << std::endl;
    curr = curr->next;
  }
  // std::cout << "\n" << std::endl;
  return 0;
}

/*
ASAN:
clang++ -std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic
-fsanitize=address,null -fno-omit-frame-pointer ./src/driver.cc
./src/dna_strand.cc ./src/utilities.cc -Iincludes
*/

/*
USAN: clang++ -std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror
-pedantic -fsanitize=undefined
*/

/*
Valgrind: valgrind --tool=memcheck --leak-check=yes ./bin/exec
*/