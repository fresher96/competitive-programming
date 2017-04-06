#include <bits/stdc++.h>
using namespace std;
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
#define PB push_back
#define MP make_pair
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef vector <vii> vvii;
#define nMax 1000+9
//
vvii G;
int n, m;
int par[nMax], num[nMax], low[nMax], color[nMax];
int timer, root, rootChildren, SCCNum;
bool isArticulation[nMax];
bool isBridge[nMax][nMax];
bool inComp[nMax], vis[nMax];
stack <int> S;
vi task;
int beg[nMax], end[nMax];
//
void scan_graph(bool directed = false){
    cin>>n>>m;
    G.assign(n, vii());
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v;
        w = 1;
        //u--, v--;       // for 1-based
        G[u].PB( MP(v, w) );
        if(!directed)
            G[v].PB( MP(u, w) );
    }
}
void check(int u, int v, string state, int b = 0){
    if(state == "u<->v")
        printf(" Two ways (%d, %d)-(%d, %d)\n", u, v, v, u);
    else if(state == "u<-v")
        printf(" Back Edge (%d, %d) (Cycle)\n", u, v);
    else if(state == "u->v")
        if(b == 0)
            printf(" Forward/Cross Edge (%d, %d)\n", u, v);
        else if(b == 1)
            printf(" Forward Edge (%d, %d)\n", u, v);
        else
            printf(" Cross Edge (%d, %d)\n", u, v);
    else
        printf("Undefined state for check() function!\n");
}
void edge_check(int u=0){ // O(V + E)
    num[u] = 1;
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(num[v] == -1)                        // tree edge: explored -> unvisited
            par[v] = u, edge_check(v);
        else if(num[v] == 1)                    // explored -> explored
            if(v == par[u])                     // bidirectional edge
                check(u, v, "u<->v");
            else                                // back edge
                check(u, v, "u<-v");
        else                                    // forward/cross edge: explored -> visited
            check(u, v, "u->v");
    }
    num[u] = 2;
}
bool is_cyclic(int u=0){ // O(V + E)
    num[u] = 1;
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(num[v] == -1)
        {
            par[v] = u;
            if(is_cyclic(v))
                return true;
        }
        else if(num[v] == 1)
            if(v != par[u])     // comment this condition if the graph is directed
                return true;
    }
    num[u] = 2;
    return false;
}
void DFS_timer(int u){ // O(V + E)
    beg[u] = timer++;
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(beg[v] == -1)                        // tree edge
            par[v] = u, DFS_timer(v);
        else if(end[v] == -1)
            if(par[u] == v)                     // bidirectional edge
                check(u, v, "u<->v");
            else                                // back edge
                check(u, v, "u<-v");
        else if(beg[v] > beg[u])                // forward edge
            check(u, v, "u->v", 1);
        else
            check(u, v, "u->v", 2);             // cross edge
    }
    end[u] = timer++;
}
void detect(int u=0){  // O(V + E)
    // does not work in case of multi-edges
    num[u] = low[u] = timer++;
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(num[v] == -1)
        {
            par[v] = u, detect(v);
            
            if(u == root)
                rootChildren++;
            if(low[v] >= num[u])
                isArticulation[u] = true;
            if(low[v] > num[u])
                isBridge[u][v] = isBridge[v][u] = true;
            
            low[u] = min(low[u], low[v]);
        }
        else if(v != par[u])
            low[u] = min(low[u], num[v]);
    }
}
void SCC(int u){ // O(V + E)
    num[u] = low[u] = timer++;
    inComp[u] = true;
    S.push(u);
    
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(num[v] == -1)
            SCC(v);
        if(inComp[v])
            low[u] = min(low[u], low[v]);
    }
    
    if(num[u] == low[u])
    {
        printf("SCC %d:", ++SCCNum);
        while(true)
        {
            int v = S.top();    S.pop();
            inComp[v] = false;
            printf(" %d", v);
            if(u == v)  break;
        }
        printf("\n");
    }
}
void topo_sort(int u){ // O(V + E)
    vis[u] = true;
    int sz = G[u].size();
    for(int i=0; i<sz; i++)
    {
        int v = G[u][i].first;
        if(!vis[v])
            topo_sort(v);
    }
    task.PB(u);
}
bool is_bipartite(int u=0){ // O(V + E)
    queue <int> q;      q.push(u);
    memset(color, -1, sizeof color);
    color[u] = 0;
    while(!q.empty())
    {
        u = q.front();  q.pop();
        int sz = G[u].size();
        for(int i=0; i<sz; i++)
        {
            int v = G[u][i].first;
            if(color[v] == -1)
                color[v] = !color[u], q.push(v);
            else if(color[v] == color[u])
                return false;
        }
    }
    return true;
}
//
void test1(){
    memset(num, -1, sizeof num);
    
    int compNum = 1;
    for(int i=0; i<n; i++)
        if(num[i] == -1)
            printf("Component %d:\n", compNum++), edge_check(i);
}
void test2(){
    timer = 0;
    memset(num, -1, sizeof num);
    memset(isArticulation, false, sizeof isArticulation);
    memset(isBridge, false, sizeof isBridge);
    
    for(int i=0; i<n; i++)
    {
        if(num[i] == -1)
        {
            root = i, rootChildren = 0, detect(i);
            isArticulation[i] = (rootChildren > 1)? true : false;
        }
    }
    
    printf("Bridges:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(isBridge[i][j])
                printf("Edge %d %d\n", i, j);
        
    printf("Articulations:\n");
    for(int i=0; i<n; i++)
        if(isArticulation[i])
            printf("Vertex %d\n", i);
}
void test3(){
    memset(num, -1, sizeof num);
    memset(inComp, false, sizeof inComp);
    
    timer = SCCNum = 0;
    for(int i=0; i<n; i++)
        if(num[i] == -1)
            SCC(i);
}
void test4(){
    task.clear();
    memset(vis, false, sizeof vis);
    for(int u=0; u<n; u++)
        if(!vis[u])
            topo_sort(u);
    
    for(int i=0; i<n; i++)
        printf("%d%c", task[i]+1, " \n"[i == n-1]);
}
void test5(){
    test1(), cout<<endl;
    
    memset(beg, -1, sizeof beg);
    memset(end, -1, sizeof end);
    
    timer = 0;
    int compNum = 1;
    for(int i=0; i<n; i++)
        if(beg[i] == -1)
            printf("Component %d:\n", compNum++), DFS_timer(i);
}
//
int main()
{
    read_file(true);
    scan_graph(true);
    
    //test1();
    test2();
    //test3();
    //test4();
    //test5();
}
