// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1998

#include <iostream>

using namespace std;

void twoPointers(int *v, int size, int total){
  int i = 0;
  int j = size - 1;
  int firstBook = 0, secondBook = -1;

  while(i < j){
    if(v[i] + v[j] > total){
      j--;
    } else if(v[i] + v[j] < total){
      i++;
    } else{
      if((v[secondBook] - v[firstBook]) > (j - i) || secondBook == -1){
        firstBook = i++;
        secondBook = j--;
      }
    }
  }

  cout << "Peter should buy books whose prices are " << v[firstBook] << " and " << v[secondBook] << ".\n\n";
}

int hoarePartition(int *v, int startPos, int endPos){
  int p = v[startPos];
  int i = startPos;
  int j = endPos + 1;

  do{
    do{
      i++;
    }while(!(v[i] >= p || i >= endPos));

    do{
      j--;
    }while(v[j] > p);

    swap(v[i], v[j]);
  }while(i < j);

  swap(v[i], v[j]);
  swap(v[startPos], v[j]);

  return j;
}

void quicksort(int *v, int startPos, int endPos){
  if(endPos > startPos){
    int pivot = hoarePartition(v, startPos, endPos);
    quicksort(v, startPos, pivot - 1);
    quicksort(v, pivot + 1, endPos);
  }
}

int main(){
  int n;

  while(cin >> n){
    int *books = new int[n];
    for(int i = 0; i < n; i++){
      cin >> books[i];
    }

    int money;
    cin >> money;

    quicksort(books, 0, n - 1);
    twoPointers(books, n, money);

    delete[] books;
  }

  return 0;
}