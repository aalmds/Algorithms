// Problem's source: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2733

#include <bits/stdc++.h>

using namespace std;

struct Graph{
  vector<vector<int>> adj;
  vector<bool> mark;
  vector<int> timeOut;
  int count;
};

void setEdge(Graph &g, int u, int v){
  g.adj[u].push_back(v);
}

void toposort(Graph &g, int currentPos, stack<int> &st){
  g.mark[currentPos] = true;

  //Visiting a list, not the position
  for(int w : g.adj[currentPos]){
    if(!g.mark[w]){
      toposort(g, w, st);
    }
  }

  g.timeOut[currentPos] = ++g.count;
  st.push(currentPos);
}

void graphTraverse(Graph &g){
  stack<int> st;
  g.mark = vector<bool>(g.adj.size());
  g.timeOut = vector<int>(g.adj.size());
  g.count = 0;

  for(int i = 0; i < g.adj.size(); ++i){
    if(!g.mark[i]){
      toposort(g, i, st);
    }
  }

  int acyclic = true;
  for(int i = 0; i < g.adj.size(); ++i){
    for(int w : g.adj[i]){
      if(g.timeOut[w] > g.timeOut[i]){
        acyclic = false;
        break;
      }
    }
  }

  if(acyclic){
    while(!st.empty()){
      cout << st.top() + 1 << endl;
      st.pop();
    }
  } else {
    cout << "IMPOSSIBLE" << endl;
  }

}

int main(){
  int n, m;
  cin >> n >> m;
  while(n and m){
    Graph g;
    g.adj = vector<vector<int>>(n);
    int u, v;
    for(int i = 0; i < m; i++){
      cin >> u >> v;
      setEdge(g, --u, --v);
    }

    graphTraverse(g);
    cin >> n >> m;
  }
  return 0;
}
