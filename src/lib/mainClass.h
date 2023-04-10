#pragma once
#include <iostream>

#ifndef ____type_size
#define ____type_size size_t
#endif

template <typename Type>
constexpr bool FLAG =
    std::is_same<Type, int>::value or std::is_same<Type, double>::value or
    std::is_same<Type, float>::value;

template <typename Type> class forward_spisok;

template <typename Type> std::ostream& operator << (std::ostream& out, const forward_spisok<Type> & obj);
template <typename Type> std::istream& operator >> (std::istream& in, forward_spisok<Type> & obj);

template <typename Type> class forward_spisok {
  static_assert(FLAG<Type>, " ");
protected:
  struct Node {
    Node *next;
    Type inf;
  } *head, *tail;
  ____type_size size;
public:
  forward_spisok(Type inf);
  forward_spisok(size_t size_, Type inf);
  forward_spisok(const forward_spisok& obj);
  ~forward_spisok();
  friend std::ostream& operator << <Type>(std::ostream& out, const forward_spisok & obj);
  friend std::istream& operator >> <Type>(std::istream& in, forward_spisok & obj);
  void operator=(const forward_spisok& obj);
  Type& operator[](size_t index);
  ____type_size length();
  forward_spisok< Type > operator+(const forward_spisok<Type >& obj);
  void push_back(Type inf);
  void push_front(Type inf);
  Type& back();
  Type& front();
};


template <typename Type> forward_spisok<Type>::forward_spisok(Type inf) {
  size = 1;
  head = tail = new Node;
  tail->inf = inf;
  tail->next = nullptr;
}

template <typename Type> forward_spisok<Type>::forward_spisok(size_t size_, Type inf) {
  if (size_ == 0) abort();
  size = size_;
  head = tail = new Node;
  tail->inf = inf;
  tail->next = nullptr;
  for (size_t i = 1; i < size_; i++) {
    tail->next = new Node;
    tail = tail->next;
    tail->inf = inf;
    tail->next = nullptr;
  }
}

template <typename Type> forward_spisok<Type>::forward_spisok(const forward_spisok<Type>& obj) {
  size = obj.size;
  head = tail = new Node;
  tail->inf = obj.head->inf;
  tail->next = nullptr;
  for (Node tmp = obj.head->next; tmp != nullptr;) {
    tail->next = new Node;
    tail = tail->next;
    tail->inf = tmp->inf;
    tail->next = nullptr;
    tmp = tmp->next;
  }
}


template <typename Type> forward_spisok<Type>::~forward_spisok() {
  for(auto temp = head->next; temp != nullptr;) {
    head = temp;
    temp = temp->next;
    delete head;
  }
}

template <typename Type> std::ostream& operator << (std::ostream& out, const forward_spisok<Type> & obj) {
  out << "\n  size = " << obj.size << "\n";
  size_t i = 0;
  for(typename forward_spisok<Type>::Node tmp = obj.head; tmp != nullptr;) {
    out << i++ << "\t" << tmp->inf << "\n";
    tmp = tmp->next;
  }
  return out;
}

template <typename Type> std::istream& operator >> (std::istream& in, forward_spisok<Type> & obj) {
  std::cout << "\n  size = " << obj.size << "\n";
  size_t i = 0;
  for(typename forward_spisok<Type>::Node tmp = obj.head; tmp != nullptr;) {
    std::cout << "  " << obj.size - i << "\t";
    in >> tmp->inf;
    tmp = tmp->next;
  }
  return in;
}

template <typename Type> void forward_spisok<Type>::operator=(const forward_spisok<Type>& obj) {
  Node tthis = head, tthat = obj.head;
  while (true) {
    tthis->inf = tthat->inf;
    tthis = tthis->next;
    tthat = tthat->next;
    if (tthis->next == nullptr) {
      tthis->inf = tthat->inf;
      tthat = tthat->next;
      while (tthat != nullptr) {
        tthis->next = new forward_spisok<Type>::Node;
        tthis = tthis->next;
        tthis->inf = tthat->inf;
        tthis->next = nullptr;
        tthat = tthat->next;
      }
      return;
    }
    if (tthat == nullptr) return;
  }

}

template <typename Type> Type& forward_spisok<Type>::operator[](size_t index) {
  if (index >= size) abort();
  if (index == size-1) return tail->inf;
  size_t i = 0;
  for (Node tmp = head; tmp != nullptr;) {
    if (index == i++) return tmp->inf;
    tmp = tmp->next;
  }
}

template <typename Type> ____type_size forward_spisok<Type>::length() {
  return this->size;
}

template <typename Type> forward_spisok<Type> forward_spisok<Type>::operator+(const forward_spisok<Type>& obj) {
  for (Node tthis = head, tthat = obj.head; tthis != nullptr || tthat != nullptr;) {
    tthis->inf += tthat->inf;
    tthis = tthis->next;
    tthat = tthat->next;
  }
}


template <typename Type> void forward_spisok<Type>::push_back(Type inf) {
  tail->next = new Node;
  tail = tail->next;
  tail->inf = inf;
  tail->next = nullptr;
  ++size;
}
template <typename Type> void forward_spisok<Type>::push_front(Type inf) {
  Node* tmp = new Node;
  tmp->inf = inf;
  tmp->next = head;
  head = tmp;
}
template <typename Type> Type& forward_spisok<Type>::back() { return tail->inf; }
template <typename Type> Type& forward_spisok<Type>::front() { return head->inf; }
