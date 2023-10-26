#include <fstream>
#include <iostream>

#include "illini_book.hpp"
#include "utilities.hpp"

int main() {
  IlliniBook insert_files_to_map("./example/persons.csv", "./example/relations.csv");
  // std::vector<int> get_steps = insert_files_to_map.GetSteps(1, 1); // THIS WORKS
  //std::vector<int> get_steps = insert_files_to_map.GetSteps(3, 2); // THIS FAILS
  //for (size_t i = 0; i < get_steps.size(); i++) {
    //std::cerr << "UIN: " << get_steps[i] << std::endl;
  //}
  //std::vector<std::string> relationships = { "128", "124" };
  std::cout << "Counting groups: " << insert_files_to_map.CountGroups("128") << std::endl;
  //std::cout << "Counting groups in 128 and 124: " << insert_files_to_map.CountGroups(relationships) << std::endl; // output should be 2??
  //return 0;
}
