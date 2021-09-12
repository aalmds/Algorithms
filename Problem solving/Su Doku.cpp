//Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=930

#include <bits/stdc++.h>

using namespace std;

bool checkRow(vector<vector<int>> &mtr, int iRow){
  vector<int> check(mtr.size() + 1, 0);
  for(int i = 0; i < mtr.size(); ++i){
    ++check[mtr[iRow][i]];
  }

  for(int i = 1; i < check.size(); ++i){
    if(check[i] > 1){
      return false;
    }
  }

  return true;
}

bool checkColumn(vector<vector<int>> &mtr, int iCol){
  vector<int> check(mtr.size() + 1, 0);
  for(int i = 0; i < mtr.size(); ++i){
    ++check[mtr[i][iCol]];
  }

  for(int i = 1; i < check.size(); ++i){
    if(check[i] > 1){
      return false;
    }
  }

  return true;
}

bool checkBlock(vector<vector<int>> &mtr, int iRow, int iCol, int n){
  vector<int> check(mtr.size() + 1, 0);
  int bRow = (iRow / n) * n;
  int bCol = (iCol / n) * n;
  for(int i = bRow; i < bRow + n; ++i){
    for(int j = bCol; j < bCol + n; ++j){
      ++check[mtr[i][j]];
    }
  }

  for(int i = 1; i < check.size(); ++i){
    if(check[i] > 1){
      return false;
    }
  }

  return true;
}

bool sudoku(vector<vector<int>> &mtr, int n, int iRow, int iCol){
  if(iRow == n * n){
    return true;
  }

  if(not (mtr[iRow][iCol])){
    for(int i = 1; i <= n * n; ++i){
      mtr[iRow][iCol] =  i;
      if(checkRow(mtr, iRow) and checkColumn(mtr, iCol) and checkBlock(mtr, iRow, iCol, n)){
        if(sudoku(mtr, n, (iCol == (n * n) - 1 ? iRow + 1: iRow), (iCol == (n * n) - 1 ? 0 : iCol + 1))){
          return true;
        }
      }
      mtr[iRow][iCol] = 0;
    }

    return false;
  } else {
    return sudoku(mtr, n, (iCol == (n * n) - 1 ? iRow + 1: iRow), (iCol == (n * n) - 1 ? 0 : iCol + 1));
  }
}

int main() {
  int n;
  int count = 0;
  while(cin >> n){
    ++count;

    vector<vector<int>> mtr(n * n, vector<int>(n * n));
    for(int i = 0; i < mtr.size(); ++i){
      for(int j = 0; j < mtr[i].size(); ++j){
        cin >> mtr[i][j];
      }
    }

    if(count > 1){
      cout << "\n";
    }

    if(sudoku(mtr, n, 0, 0)){
      for(int i = 0; i < mtr.size(); ++i){
        for(int j = 0; j < mtr[i].size(); ++j){
          cout << mtr[i][j] << (j < mtr[i].size() - 1 ? " " : "\n");
        }
      }
    } else {
      cout << "NO SOLUTION\n";
    }
  }
  return 0;
}