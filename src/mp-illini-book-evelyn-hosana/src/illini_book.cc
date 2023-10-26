#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <set>

#include "utilities.hpp"

// Constructor
IlliniBook::IlliniBook(const std::string& people_fpath, const std::string& relations_fpath) {
  // ifstream parameters
  std::ifstream people_file{people_fpath};
  std::ifstream relations_file{relations_fpath};
  // check if either file has issues with opening
  if (!(people_file.is_open())) { throw std::runtime_error("Error opening people file!"); }
  if (!(relations_file.is_open())) { throw std::runtime_error("Error opening relations file!"); }
  // Update key and list_value while reading from files
  for (std::string people_line; std::getline(people_file, people_line); people_line = "") { // for loop reads from people's file, line by line
    std::map<int, std::string> map_of_relationships;
    graph_.insert({std::stoi(people_line), map_of_relationships});
  }
  for (std::string relations_line; std::getline(relations_file, relations_line); relations_line = "") { // for loop reads from relations's file, line by line
    std::vector<std::string> vector_values = utilities::Split(relations_line, ',');  // further seperate .csv file to split by each commas, needs to be a vector according to utillities.hpp
    for (size_t i = 0; i < vector_values.size(); i ++) {
      graph_[std::stoi(vector_values.at(0))][std::stoi(vector_values.at(1))] = vector_values.at(2);
      graph_[std::stoi(vector_values.at(1))][std::stoi(vector_values.at(0))] = vector_values.at(2);
    }
  }
}

// Checks if two nodes are connected
bool IlliniBook::AreRelated(int uin_1, int uin_2) const { bool relation = true; if (GetRelated(uin_1, uin_2) == -1) { relation = false; } return relation; }
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string& relationship) const { bool relation = true; if (GetRelated(uin_1, uin_2, relationship) == -1) { relation = false; } return relation; }

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  if (uin_1 == uin_2) { return 0; }
  int level = 1;
  std::set<int> visited;
  std::queue<int> q;
  visited.insert(uin_1);
  q.push(uin_1);
  size_t nodes_in_level = q.size();
  while (!q.empty()) {
    while (nodes_in_level != 0) {
      nodes_in_level--;
      uin_1 = q.front();
      q.pop();
      auto iter  = graph_.find(uin_1);
      for (auto i = iter->second.begin(); i != iter->second.end(); i++) {
        if (i->first == uin_2) {
          return level;
        }
        if (visited.count(i->first) == 0) {
          visited.insert(i->first);
          q.push(i->first);
        }
      }
    }
    if (nodes_in_level == 0) {
      level++;
      nodes_in_level = q.size();
    }
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string& relationship) const {
  if (uin_1 == uin_2) { return 0; }
  int level = 1;
  std::set<int> visited;
  std::queue<int> q;
  visited.insert(uin_1);
  q.push(uin_1);
  size_t nodes_in_level = q.size();
  while (!q.empty()) {
    while (nodes_in_level != 0) {
      nodes_in_level--;
      uin_1 = q.front();
      q.pop();
      auto iter  = graph_.find(uin_1);
      for (auto i = iter->second.begin(); i != iter->second.end(); i++) {
        if (graph_.at(uin_1).at(i->first) == relationship) {
          if (i->first == uin_2) { return level; }
        } 
        if (graph_.at(uin_1).at(i->first) == relationship) {
          if (visited.count(i->first) == 0) {
            visited.insert(i->first);
            q.push(i->first);
          }
        }
      }
    }
    if (nodes_in_level == 0) {
      level++;
      nodes_in_level = q.size();
    }
  }
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> steps_away;
  if (n == 0) { return steps_away; }
  int level = 1;
  std::set<int> visited;
  std::queue<int> q;
  visited.insert(uin);
  q.push(uin);
  size_t nodes_in_level = q.size();
  while (!q.empty()) {
    while (nodes_in_level != 0) {
      nodes_in_level--;
      uin = q.front();
      q.pop();
      auto iter  = graph_.find(uin);
      for (auto i = iter->second.begin(); i != iter->second.end(); i++) {
        if (level > n) { break; }
        if (level == n) {
          if (visited.count(i->first) == 0) {
            visited.insert(i->first);
            steps_away.push_back(i->first);
          }
        }
        if (level < n) {
          if (visited.count(i->first) == 0) {
            visited.insert(i->first);
            q.push(i->first);
          } } } }
    if (level == n) { return steps_away; }
    if (level != n) { level++; nodes_in_level = q.size();
    } }
  return steps_away;
}

size_t IlliniBook::CountGroups() const {
  size_t groups = 0;
  std::set<int> visited;
  for (auto iter = graph_.begin(); iter != graph_.end(); iter++) {
    if (visited.count(iter->first) == 0) {
      visited.insert(iter->first);
      std::queue<int> q;
      q.push(iter->first);
      while (!q.empty()) {
        for (auto it = graph_.at(q.front()).begin(); it != graph_.at(q.front()).end(); it++) {
          if(visited.count(it->first) == 0) {
            visited.insert(it->first);
            q.push(it->first);
          }
        }
        q.pop();
      }
      groups++;
    }
  }
  return groups;
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  size_t groups = 0;
  std::set<int> visited;
  for (auto iter = graph_.begin(); iter != graph_.end(); iter++) {
    if (visited.count(iter->first) == 0) {
      visited.insert(iter->first);
      std::queue<int> q;
      q.push(iter->first);
      while (!q.empty()) {
        for (auto it = graph_.at(q.front()).begin(); it != graph_.at(q.front()).end(); it++) {
          if(visited.count(it->first) == 0) {
            if (graph_.at(q.front()).at(it->first) == relationship) {
              visited.insert(it->first);
              q.push(it->first);
            }
          }
        }
        q.pop();
      }
      groups++;
    }
  }
  return groups;
}
size_t IlliniBook::CountGroups(const std::vector<std::string>& relationships) const {
  std::set<std::string> relations(relationships.begin(), relationships.end());
  size_t group_relations = 0;
  std::set<int> visited;
  for (auto iter = graph_.begin(); iter != graph_.end(); iter++) {
    if (visited.count(iter->first) == 0) {
      visited.insert(iter->first);
      std::queue<int> q;
      q.push(iter->first);
      while (!q.empty()) {
        for (auto it = graph_.at(q.front()).begin(); it != graph_.at(q.front()).end(); it++) {
            if (visited.count(it->first) == 0) {
              if (relations.count(graph_.at(q.front()).at(it->first)) > 0) {
                visited.insert(it->first);
                q.push(it->first);
              }
            }
          }
        q.pop();
      }
      group_relations++;
    }
  }
  return group_relations;
}