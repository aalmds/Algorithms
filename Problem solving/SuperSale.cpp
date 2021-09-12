//Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1071

#include <bits/stdc++.h>

using namespace std;
#define W 31

struct Object {
  int value;
  int weight;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;

  while (n--) {
    // Saving the value and weight associated to every object
    int qtdObj;
    cin >> qtdObj;
    Object* objs = new Object[qtdObj + 1];
    for (int i = 1; i <= qtdObj; ++i) {
      cin >> objs[i].value >> objs[i].weight;
    }

    // Saving the capacity of every person
    int qtdP;
    cin >> qtdP;
    int* capacity = new int[qtdP];
    for (int i = 0; i < qtdP; ++i) {
      cin >> capacity[i];
    }

    // Allocating the matrix where every row is an item and every column is a capacity
    int** mtr = new int*[qtdObj + 1];
    for (int i = 0; i <= qtdObj; ++i) {
      mtr[i] = new int[W];
    }

    // Creating solution based on knapsack problem with dynamic programming bottom up version
    for (int i = 0; i <= qtdObj; ++i) {
      for (int j = 0; j < W; ++j) {
        if (i == 0 or j == 0) {
          // When there's no item or no capacity for choose an item
          mtr[i][j] = 0;
        } else if (objs[i].weight <= j) {
          // When the object can be chosen:
            // option 1: don't choose, continuing with the same capacity and all the items selected
            // before;
            // option 2: choose, losing capacity and winning the value associated with the new chosen
            // object;
          mtr[i][j] = max(mtr[i - 1][j], objs[i].value + mtr[i - 1][j - objs[i].weight]);
        } else {
          // When the object cannot be chosen
          mtr[i][j] = mtr[i - 1][j];
        }
      }
    }

    int total = 0;
    for (int i = 0; i < qtdP; ++i) {
      total += mtr[qtdObj][capacity[i]];
    }
    cout << total << "\n";

    // Deallocating the memory
    delete[] objs;
    delete[] capacity;
    for (int i = 0; i < qtdObj; ++i) {
      delete[] mtr[i];
    }
    delete[] mtr;
  }
}