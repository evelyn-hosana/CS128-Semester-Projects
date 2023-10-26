#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void PushBack(char character);
  void IfStatments(const char* pat, DNAstrand& splicing);
  void DeallocateSpliceIn(Node* head_type, Node* tail_type);

  bool PatternFound();
  int SizeOfPattern(const char* input);

  Node* GetHead() const { return head_; };
  Node* GetTail() const { return tail_; };

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif