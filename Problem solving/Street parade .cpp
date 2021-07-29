//Problem's source: https://www.spoj.com/problems/STPAR/en/

#include <iostream>

using namespace std;

class Node{
public:
  int value;
  Node* next;

  Node(int e, Node *node = nullptr) : value(e), next(node){}
};

class Stack{
  Node* top;
  int size;

public:
  Stack(){
    top = nullptr;
    size = 0;
  }

  ~Stack(){
    clear();
  }

  void clear(){
    while(top != nullptr){
      Node* aux = top;
      top = top -> next;
      delete aux;
      --size;
    }
  }

  void push(int e){
    top = new Node(e, top);
    size++;
  }

  int pop(){
    if(top == nullptr){
      throw runtime_error("The stack is empty!\n");
    }

    int e = top -> value;

    Node* aux = top;
    top = top -> next;
    delete aux;
    --size;

    return e;
  }

  int topValue(){
    if(top == nullptr){
      throw runtime_error("The stack is empty!\n");
    }

    return top -> value;
  }

  int length(){
    return size;
  }
};

int main(){
  Stack stack;

  int n;
  cin >> n;

  while(n){
    int *p = new int[n];
    for(int i = 0; i < n; i++){
      cin >> p[i];
    }

    int smaller = 1;
    for(int i = 0; i < n; i++){
      if(p[i] != smaller){
        stack.push(p[i]);
      } else {
        smaller++;
        while(stack.length() && stack.topValue() == smaller){
          stack.pop();
          smaller++;
        }
      }
    }

    delete[] p;
    stack.clear();

    if(smaller == n + 1){
      cout << "yes\n";
    } else {
      cout << "no\n";
    }

    cin >> n;
  }
}