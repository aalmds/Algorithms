// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3644

#include <iostream>
#include <vector>

using namespace std;

struct Index{
  int id;
  int initialValue;
  int value;
};

bool compare(Index a, Index b){
  if(a.value == b.value){
    if(a.id < b.id){
      return false;
    } else {
      return true;
    }
  } else {
    if(a.value < b.value){
      return false;
    } else {
      return true;
    }
  }
}

void heapBottomUp(vector<Index> &arr){
  int n = (int)arr.size() - 1;
  for(int i = n / 2; i >= 1; i--){
    int k = i;
    Index v = arr[k];
    bool heap = false;
    int j;

    while(not heap && 2 * k <= n){
      j = 2 * k;
      if(j < n){
        if(compare(arr[j], arr[j + 1])){
          j++;
        }
      }

      if(not (compare(v, arr[j]))){
        heap = true;
      } else {
        arr[k] = arr[j];
        k = j;
      }
    }

    arr[k] = v;
  }
}

void findMin(vector<Index> &heap){
  cout << heap[1].id << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string str;
  vector<Index> vtr(1);

  cin >> str;
  while(str != "#"){
    Index index;
    cin >> index.id >> index.value;
    index.initialValue = index.value;
    vtr.push_back(index);
    cin >> str;
  }

  heapBottomUp(vtr);

  int n;
  cin >> n;
  while(n--){
    findMin(vtr);
    vtr[1].value += vtr[1].initialValue;
    heapBottomUp(vtr);
  }
}