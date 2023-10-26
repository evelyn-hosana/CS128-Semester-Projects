#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::string data_file = argv[1];
  std::string dna_sequence = argv[2];
  std::vector<std::vector<std::string>> data_test = DataExamples(data_file);
  std::vector<int> v1;
  for (unsigned i = 1; i < data_test[0].size(); i++) {
    std::string strs_as_strings = data_test[0][i];
    int count_of_longest_str =
        CountLongestSequence(strs_as_strings, dna_sequence);
    v1.push_back(count_of_longest_str);
  }
  std::string name;
  bool matching = true;
  for (unsigned a = 1; a < data_test.size(); a++) {
    std::string name_of_people = data_test[a][0];
    for (unsigned b = 1; b < data_test[a].size(); b++) {
      int convert = std::stoi(data_test[a][b]);
      if (convert != v1.at(b - 1)) {
        matching = false;
        break;
      }
      matching = true;
    }
    if (matching) {
      std::cout << name_of_people << std::endl;
      break;
    }
  }
  if (!matching) {
    std::cout << "No match" << std::endl;
  }
  return 0;
}