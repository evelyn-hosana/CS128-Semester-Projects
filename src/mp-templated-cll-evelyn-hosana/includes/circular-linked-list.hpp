#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  // MY helper functions
  void InsertAscending(const T& data);
  void InsertDescending(const T& data);

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);
  return os;
}

// DEFINE FUNCTIONS HERE

// Copy constructor
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  // conditional
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return;
  }
  if (source.head_ == source.tail_) {
    head_ = new Node<T>(source.head_->data);
    tail_ = head_;
    head_->next = head_;
    return;
  }
  // perform deep copy
  head_ = new Node<T>(source.head_->data);
  Node<T>* temp1 = head_;
  Node<T>* temp2 = source.head_->next;
  while (temp2 != source.head_) {
    temp1->next = new Node<T>(temp2->data);
    if (temp2 == source.tail_) {
      tail_ = temp1->next;
    }
    temp1 = temp1->next;
    temp2 = temp2->next;
  }
  tail_->next = head_;
}

// Copy assignment operator
template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  if (this == &source) {  // self-assignment conditional
    return *this;
  }
  // delete/deallocate
  if (head_ != nullptr) {
    tail_->next = nullptr;
    while (head_ != nullptr) {
      Node<T>* next = head_->next;
      delete head_;
      head_ = next;
    }
    head_ = tail_ = nullptr;
  }  // conditional
  if (source.head_ == nullptr) {
    return *this;
  }
  if (source.head_ == source.tail_) {
    head_ = new Node<T>(source.head_->data);
    tail_ = head_;
    head_->next = head_;
    return *this;
  }  // perform deep copy
  head_ = new Node<T>(source.head_->data);
  Node<T>* temp1 = head_;
  Node<T>* temp2 = source.head_->next;
  while (temp2 != source.head_) {
    temp1->next = new Node<T>(temp2->data);
    if (temp2 == source.tail_) {
      tail_ = temp1->next;
    }
    temp1 = temp1->next;
    temp2 = temp2->next;
  }
  tail_->next = head_;
  return *this;
}

// InsertInOrder(T data)
template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (node_order_ == Order::kASC) {
    InsertAscending(data);
  }
  if (node_order_ == Order::kDESC) {
    InsertDescending(data);
  }
}

// Destructor
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) {
    return;
  }
  tail_->next = nullptr;
  while (head_ != nullptr) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  head_ = tail_ = nullptr;
}

// Reverse()
template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else if (node_order_ == Order::kDESC) {
    node_order_ = Order::kASC;
  }
  if (tail_ == nullptr) {
    return;
  }
  Node<T>* current = tail_->next;
  Node<T>* nextnode = current->next;
  if (tail_ == head_) {
    return;
  }
  while (current != tail_) {
    Node<T>* prevnode = current;
    current = nextnode;
    nextnode = current->next;
    current->next = prevnode;
  }
  head_ = tail_;
  nextnode->next = tail_;
  tail_ = nextnode;
}

// HELPER FUNCTIONS
template <typename T>
void CircularLinkedList<T>::InsertAscending(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data);
    tail_ = head_;
    head_->next = head_;
  } else {
    Node<T>* current = head_;
    Node<T>* prev = nullptr;
    while (current != tail_ && current->data < data) {
      prev = current;
      current = current->next;
    }
    if (current == tail_ && current->data < data) {
      prev = current;
      current = current->next;
    }
    // insert at beginning
    if (prev == nullptr) {  // if previous does not exist
      auto pointer = new Node<T>(data);
      pointer->next = head_;
      head_ = pointer;
      tail_->next = head_;
    } else if (prev == tail_) {  // insert at the end
      auto pointer = new Node<T>(data);
      pointer->next = head_;
      tail_->next = pointer;
      tail_ = pointer;
    } else if (prev &&
               current) {  // if current and previous exist insert in the middle
      auto pointer = new Node<T>(data);
      pointer->next = prev->next;
      prev->next = pointer;
    }
  }
}
template <typename T>
void CircularLinkedList<T>::InsertDescending(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data);
    tail_ = head_;
    head_->next = head_;
  } else {
    Node<T>* current = head_;
    Node<T>* prev = nullptr;
    while (current != tail_ && current->data > data) {
      prev = current;
      current = current->next;
    }
    if (current == tail_ && current->data > data) {
      prev = current;
      current = current->next;
    }
    // insert at beginning
    if (prev == nullptr) {  // if previous does not exist
      auto pointer = new Node<T>(data);
      pointer->next = head_;
      head_ = pointer;
      tail_->next = head_;
    }
    // insert in the middle
    if (prev && current) {  // if current and previous exist
      auto pointer = new Node<T>(data);
      pointer->next = prev->next;
      prev->next = pointer;
    }
    // insert at the end
    if (prev == tail_) {
      auto pointer = new Node<T>(data);
      pointer->next = head_;
      tail_->next = pointer;
      tail_ = pointer;
    }
  }
}

#endif