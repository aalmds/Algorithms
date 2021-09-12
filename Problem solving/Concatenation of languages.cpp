// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1828

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  int caseCount = 1;
  while(t--){
    int m, n;
    cin >> m >> n;
    cin.ignore();

    vector<string> firstVector, secondVector;
    string str;

    for(int i = 0; i < m; i++){
      getline(cin, str);
      firstVector.push_back(str);
    }

    for(int i=0;i<n;i++){
      getline(cin, str);
      secondVector.push_back(str);
    }

    vector<string> finalVector;
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        finalVector.push_back(firstVector[i]+secondVector[j]);
      }
    }

    sort(finalVector.begin(), finalVector.end());
    int ans = unique(finalVector.begin(),finalVector.end()) - finalVector.begin();

    cout << "Case " << caseCount++ << ": " << ans << endl;
  }

  return 0;
}