#include <bits/stdc++.h>
using namespace std;
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out1.out", "wt", stdout);
#endif
}
//
#define PB push_back
#define MP make_pair
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define nMax 1000+9
//
vvii G;
int n, m;
bool vis[nMax];
int SP[nMax];
//
void scan_graph(){
    cin>>n>>m;
    G.assign(n, vii());
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        //u--, v--;       // for 1-based
        G[u].PB( MP(v, w) );
        G[v].PB( MP(u, w) );
    }
}
void BFS(int u){ // O(V + E)
    memset(vis, false, sizeof vis);
    queue <int> q;      q.push(u);
    vis[u] = true;
    
    while(!q.empty())
    {
        u = q.front();  q.pop();
        cout<< u <<endl;        // process
        
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            if(!vis[v])
                vis[v] = true, q.push(v);
        }
    }
    // u now is the farthest node from the root
}
void DFS(int u){ // O(V + E)
    cout<< u <<endl;    // process
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(!vis[v])
            vis[v] = true, DFS(v);
    }
}
void SSSP(int u){ // O(V + E)
    memset(SP, -1, sizeof SP);
    queue <int> q;      q.push(u);
    SP[u] = 0;
    
    while(!q.empty())
    {
        u = q.front();  q.pop();
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            if(SP[v] == -1)
                SP[v] = SP[u] + 1, q.push(v);
        }
    }
}
void info(){
    // a given graph 'G' is a tree 'T' iff 'G' is connected and |E| = |V|-1
    // some of 'T' characteristic:
    // 'T' has no cycles
    // for any (u, v) from 'T' there exists only one unique path
}
//
int main(){
    read_file();
    scan_graph();
    
    BFS(0), printf("\n\n");
    
    memset(vis, false, sizeof vis);
    vis[0] = true, DFS(0), printf("\n\n");
    
    SSSP(0);
    for(int i=0; i<n; i++)
        printf("%d %d\n", i, SP[i]);
}
