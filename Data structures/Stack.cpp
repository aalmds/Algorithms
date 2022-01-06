#include <bits/stdc++.h>

using namespace std;

class Node {
 public:
  int value;
  Node* next;
  Node(int e, Node* node = nullptr) : value(e), next(node) {
  }
};

class Stack {
  Node* top;
  int size;

 public:
  Stack() {
    top = NULL;
    size = 0;
  }

  ~Stack() {
    clear();
  }

  void clear() {
    while (top != NULL) {
      Node* aux = top;
      top = top->next;
      delete aux;
      --size;
    }
  }

  void push(int e) {
    top = new Node(e);
    size++;
  }

  int pop() {
    if (top == NULL) {
      throw runtime_error("The stack is empty!\n");
    }

    int e = top->value;
    Node* aux = top;
    top = top->next;
    delete aux;
    --size;
    return e;
  }

  int topValue() {
    if (top == NULL) {
      throw runtime_error("The stack is empty!\n");
    }
    return top->value;
  }

  int length() {
    return size;
  }
};