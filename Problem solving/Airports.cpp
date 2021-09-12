// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2833

#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& ds, int x) {
  if (ds[x] == x) {
    return x;
  }

  ds[x] = find(ds, ds[x]);
  return ds[x];
}

void joint(vector<int>& ds, int a, int b) {
  int r1 = find(ds, a);
  int r2 = find(ds, b);
  if (r1 != r2) {
    ds[r2] = r1;
  }
}

void kruskal(const vector<tuple<int, int, int>>& edges,
             int locationCount,
             int airCost) {
  using E = tuple<int, int, int>;

  // Creating a heap using bottom up approach, where every position contains a tuple of the cost of
  // the edge that connects the vertex "from" to the vertex "to".
  priority_queue<E, vector<E>, greater<E>> heap(greater<E>(), edges);

  int mstCount = locationCount;
  vector<int> ds(mstCount); // vector<int> v(n)
  for (int i = 0; i < mstCount; ++i) {
    ds[i] = i; // v.push_back(i)
  }

  int totalCost = 0, airport = 0;
  while (mstCount and !heap.empty()) {
    E aux = heap.top();
    heap.pop();

    if (find(ds, get<1>(aux)) != find(ds, get<2>(aux))) {
      joint(ds, get<1>(aux), get<2>(aux));
      if (airCost <= get<0>(aux)) {
        ++airport;
      } else {
        totalCost += get<0>(aux);
      }
      --mstCount;
    }
  }

  for (int i = 0; i < ds.size(); ++i) {
    if (ds[i] == i) {
      ++airport;
    }
  }
  totalCost += airport * airCost;
  cout << totalCost << " " << airport << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int k = 0;
  while (n--) {
    int location, roads, airCost;
    cin >> location >> roads >> airCost;

    vector<tuple<int, int, int>> edges;

    // Setting edges to the graph
    for (int i = 0; i < roads; ++i) {
      int u, v, weight;
      cin >> u >> v >> weight;
      edges.emplace_back(weight, --u, --v);
    }

    cout << "Case #" << ++k << ": ";
    kruskal(edges, location, airCost);
  }
}