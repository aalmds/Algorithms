// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1876

#include <iostream>

struct Node{
  int value;
  Node* next;
};

struct Queue{
  int size;
  Node* front;
  Node* rear;
};

Node* createNode(int e, Node* node){
  Node* newNode = new Node;
  newNode -> value = e;
  newNode -> next = node;
  return newNode;
}

Queue createQueue(){
  Queue q;
  q.front = q.rear = createNode(51, NULL);
  q.size = 0;
  return q;
}

void enqueue(Queue &q, int element){
  q.rear -> next = createNode(element, NULL);
  q.rear = q.rear -> next;
  ++q.size;
}

int dequeue(Queue &q){
  if(!q.size){
    throw std::runtime_error("The queue is empty!\n");
  }

  int e = q.front -> next -> value;

  Node* aux = q.front -> next;
  q.front -> next = q.front -> next -> next;
  delete aux;
  --q.size;

  if(q.front -> next == NULL){
    q.rear = q.front;
  }

  return e;
}

int frontValue(Queue &q){
  if(q.front == q.rear){
    throw std::runtime_error("The queue is empty!\n");
  }

  return q.front -> next -> value;
}


void clear(Queue &q){
  while(q.front -> next != NULL){
    Node* aux = q.front -> next;
    q.front -> next = q.front -> next -> next;
    delete aux;
    --q.size;
  }

  q.rear = q.front;
}

int length(Queue &q){
  return q.size;
}

int main() {
  Queue queue = createQueue();

  int n;
  std::cin >> n;

  while(n){
    for(int i = 1; i <= n; i++){
      enqueue(queue, i);
    }

    int* cards = new int[n - 1];
    int dsc = 0;
    while (length(queue) > 1){
      cards[dsc++] = dequeue(queue);
      enqueue(queue, frontValue(queue));
      dequeue(queue);
    }

    std::cout << "Discarded cards:";
    for(int i = 0; i < dsc; i++){
      if(i != dsc - 1){
        std::cout << " " << cards[i] << ",";
      } else{
        std::cout << " " << cards[i];
      }
    }

    std::cout << "\n" << "Remaining card: " << frontValue(queue) << "\n";

    clear(queue);
    delete[] cards;

    std::cin >> n;
  }

  return 0;
}