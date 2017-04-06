#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define endl '\n'
#define PB push_back
#define MP make_pair
#define OO (1000000000)         // ToDo
#define EPS (1e-9)              // ToDo
#define MOD (1000000007)        // ToDo
#define all(v) ((v).begin()),((v).end())
#define DEBUG(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
#define vMax 1000
int n, m;
int par[vMax];
int src, snk; // be careful that src != snk
int flow;
// for max_flow()
vvi G;
int res[vMax][vMax];
// for max_flow1()
struct Edge{
    int u, v;
    int w;
    int prv;
    
    Edge(int u, int v, int w, int prv): u(u), v(v), w(w), prv(prv){
    }
};
typedef vector <Edge> EdgeList;
EdgeList E;
int idxer;
int last[vMax];
//
void init(){
    G.assign(n, vi());
    memset(res, 0, sizeof res);
}
void init1(){
    memset(last, -1, sizeof last);
    E.clear();
    idxer = 0;
}
void add_edge(int u, int v, int w, int rw){
    
    G[u].PB(v);
    G[v].PB(u);

    res[u][v] += w;
    res[v][u] += rw;
}
void add_edge1(int u, int v, int dw, int rw){
    
    Edge de = Edge(u, v, dw, last[u]);
    Edge re = Edge(v, u, rw, last[v]);
    
    last[u] = idxer++;
    last[v] = idxer++;
    
    E.PB(de);
    E.PB(re);
    
    // recall
    // if( (i&1) == 0 ) then E[i] is a direct edge
    // if( (i&1) == 1 ) then E[i] is a reversed edge
    // E[i^1] = the reverse of E[i]
}
void scan_graph(){
    cin>>n>>m;
    init();
    init1();
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        
        // form an edge from u to v for direct flows
        // and from v to u for reversed flows
        // we can pass a flow with value w from u to v
        // we can pass a flow with value 0 from v to u
        add_edge(u, v, w, 0);
        add_edge1(u, v, w, 0);
    }
    cin>>src>>snk;
}
// max_flow()
bool BFS(int u = src, int t = snk){ // O(V + E)
    
    queue <int> Q;
    Q.push(u);
    
    memset(par, -1, sizeof par);
    par[u] = -2;
    
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        
        if(u == t)    return true;
        
        for(int i=0, sz=G[u].size(); i<sz; i++)
        {
            int v = G[u][i];
            
            if(par[v] != -1 || res[u][v] == 0) continue;
            
            par[v] = u;
            Q.push(v);
        }
    }
    
    return false;
}
void augment(int v = snk, int minEdge = OO){ // O(V)
    // augment the founded path with the possible flow
    if(v == src)
    {
        flow = minEdge;
        return;
    }
    
    int u = par[v];
    augment(u, min(minEdge, res[u][v]));
    res[u][v] -= flow;
    res[v][u] += flow;
}
int max_flow(){ // O(V * E^2) time, O(V^2) memory
    
    int mf = 0;
    
    // while there exists an augmenting path
    while(BFS())
    {
        // O(V * E) iterations
        
        augment();
        mf += flow;
    }
    
    return mf;
}
// max_flow1()
bool BFS1(int u = src, int t = snk){ // O(V + E)
    
    queue <int> Q;
    Q.push(u);
    
    memset(par, -1, sizeof par);
    par[u] = -2;
    
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        
        if(u == t) return true;
        
        for(int i=last[u]; i!=-1; i=E[i].prv)
        {
            Edge e = E[i];
            
            int v = e.v;
            int w = e.w;
            
            if(par[v] != -1 || w == 0) continue;
            
            par[v] = i;
            Q.push(v);
        }
    }
    
    return false;
}
void augment1(int v = snk, int minEdge = OO){ // O(V)
    // augment the founded path with the possible flow
    if(v == src)
    {
        flow = minEdge;
        return;
    }
    
    int idx = par[v];
    augment1(E[idx].u, min(minEdge, E[idx].w) );
    
    E[idx].w -= flow;
    E[idx ^ 1].w += flow;
}
int max_flow1(){ // O(V * E^2) time, O(V + E) memory
    
    int mf = 0;
    
    // while there exists an augmenting path
    while(BFS1())
    {
        // O(V * E) iterations
        
        augment1();
        mf += flow;
    }
    
    return mf;
}
//
int main()
{
    read_file();
    
    int TC;
    cin>>TC;
    while(TC--)
    {
        scan_graph();
        cout<< max_flow1() <<endl;
    }
}
