//Problem's source: https://codeforces.com/problemset/problem/892/A

#include <iostream>

using namespace std;

int HoarePartition(int *v, int startPos, int endPos){
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
    int pivot = HoarePartition(v, startPos, endPos);
    quicksort(v, startPos, pivot - 1);
    quicksort(v, pivot + 1, endPos);
  }
}

int main(){
  int n;
  cin >> n;

  if(n == 2){
    cout << "YES\n";
  } else {
    int* colaVol = new int[n];
    long long int colaSum = 0;

    for(int i = 0; i < n; i++){
      cin >> colaVol[i];
      colaSum += colaVol[i];
    }

    delete[] colaVol;

    int* canCpt = new int[n];

    for(int i = 0; i < n; i++){
      cin >> canCpt[i];
    }

    quicksort(canCpt, 0, n - 1);

    if((canCpt[n - 2] + canCpt[n - 1]) >= colaSum){
      cout << "YES\n";
    } else{
      cout << "NO\n";
    }

    delete[] canCpt;
  }

  return 0;
}