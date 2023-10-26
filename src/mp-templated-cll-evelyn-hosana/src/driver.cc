#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  // Multiple node case
  std::cout << "Multiple node case: " << std::endl;
  {
    CircularLinkedList<int> cll;
    cll.InsertInOrder(2);
    CircularLinkedList<int> cll2(cll);
    std::cout << "cll is: " << cll << std::endl;
    std::cout << "cll2 is: " << cll2 << std::endl;
    /*
    std::cout << "cll is: " << cll << std::endl;
    new CircularLinkedList<int>
    std::cout << "cll2 is: " << cll2 << std::endl;
    cll.Reverse();
    std::cout << "cll reversed is: " << cll << std::endl;
    std::cout << "cll2 should stay the same: " << cll2 << std::endl;
    */
  }
  return 0;
}