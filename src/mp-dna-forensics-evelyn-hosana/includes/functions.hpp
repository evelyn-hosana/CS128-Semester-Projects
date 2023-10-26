#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"

std::vector<std::vector<std::string>> DataExamples(const std::string& examples);
int CountLongestSequence(const std::string& str,
                         const std::string& given_dna_examples);
#endif