#pragma once
#include <iostream>

#ifndef ____type_size
#define ____type_size size_t
#endif

template <typename Type>
constexpr bool FLAG =
    std::is_same<Type, int>::value or std::is_same<Type, double>::value or
    std::is_same<Type, float>::value;

template <typename Type> class connectedList {
  static_assert(FLAG<Type>, " ");

protected:
  struct Node {
    Node *next;
    Type inf;
  } *head, *tail;
  ____type_size size;

public:
  ____type_size length();
};

template <typename Type> ____type_size connectedList<Type>::length() {
  return this->size;
}
