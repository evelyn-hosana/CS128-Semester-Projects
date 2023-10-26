#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> DataExamples(
    const std::string& examples) {
  std::vector<std::vector<std::string>> lines;
  std::ifstream ifs(examples);
  if (!ifs.is_open()) {
    std::cout << "Error opening examples file!" << std::endl;
  }
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> comma_seperated_file =
        utilities::GetSubstrs(line, ',');
    lines.push_back(comma_seperated_file);
  }
  return lines;
}

// Function that counts longest sequence of STR
// USE SUBSTR METHOD
int CountLongestSequence(const std::string& str,
                         const std::string& given_dna_examples) {
  // count variable with count of initial sequence
  int count = 0;
  // maximum count variable being returned
  int max_count = 0;
  // loop through given_dna_examples
  for (unsigned i = 0; i < given_dna_examples.size(); i++) {
    std::string pattern_substring = given_dna_examples.substr(i, str.size());
    if (pattern_substring != str) {
      if (count > max_count) {
        max_count = count;
      }
      count = 0;
    } else {
      count++;
      i += (pattern_substring.size() - 1);
    }
  }
  if (count > max_count) {
    max_count = count;
  }
  return max_count;
}