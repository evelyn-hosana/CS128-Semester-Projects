#include "dna_strand.hpp"

#include <stdexcept>

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  IfStatments(pattern, to_splice_in);
  bool pattern_found = false;
  bool current_is_head = false;
  Node* current = head_;
  Node* after_tail_of_pattern = nullptr;
  Node* head_of_pattern = nullptr;
  Node* before_pattern = nullptr;
  Node* before_current = nullptr;
  Node* before_head_pattern = nullptr;
  while (current != nullptr) { before_pattern = before_current;
    Node* copy_of_current = current;
    Node* copy_of_before_current = before_current;
    for (int i = 0; i < SizeOfPattern(pattern); i++) {
      if (copy_of_current == nullptr) { break; }
      if (pattern[i] != copy_of_current->data) { break; }
      if (i == SizeOfPattern(pattern) - 1) { pattern_found = true;
        if (current == head_) { current_is_head = true;
          head_of_pattern = head_;
          after_tail_of_pattern = copy_of_current->next;
        } else { current_is_head = false;
          head_of_pattern = before_pattern->next;
          after_tail_of_pattern = copy_of_current->next;
          before_head_pattern = before_pattern;
        } break; } copy_of_current = copy_of_current->next;
      if (before_current == nullptr) { copy_of_before_current = head_; } else { copy_of_before_current = copy_of_before_current->next; } }
    if (before_current == nullptr) { before_current = head_; } else { before_current = before_current->next; }
    if (current == nullptr) { break; } current = current->next; }
  if (!pattern_found) { throw std::runtime_error("That pattern does not exist in the DNA sequence"); }
  if (current_is_head) {
    DeallocateSpliceIn(head_, after_tail_of_pattern);
    head_ = to_splice_in.GetHead();
    to_splice_in.GetTail()->next = after_tail_of_pattern;
    to_splice_in.head_ = to_splice_in.tail_ = nullptr;
  } else {
    DeallocateSpliceIn(head_of_pattern, after_tail_of_pattern);
    before_head_pattern->next = to_splice_in.GetHead();
    to_splice_in.GetTail()->next = after_tail_of_pattern;
    to_splice_in.head_ = to_splice_in.tail_ = nullptr;
  }
}
// if to_splice_in is bigger than entire sequence, throw error
void DNAstrand::DeallocateSpliceIn(Node* head_type, Node* tail_type) {
  while (head_type != tail_type) {
    Node* next_node_to_delete = head_type->next;
    delete head_type;
    head_type = next_node_to_delete;
  }
}

int DNAstrand::SizeOfPattern(const char* input) {
  int length = 0;
  while (input[length] != '\0') {
    length++;
  }
  return length;
}

void DNAstrand::PushBack(char character) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node(character);
  } else {
    Node* temp = new Node(character);
    tail_->next = temp;
    tail_ = temp;
  }
}

DNAstrand::~DNAstrand() {  // deconstructor
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}

void DNAstrand::IfStatments(const char* pat, DNAstrand& splicing) {
  if (pat == nullptr || splicing.GetHead() == nullptr) {
    return;
  }
  if (&splicing == this) {
    return;
  }
  if (head_ == nullptr) {
    throw std::runtime_error("Head is null!");
  }
}