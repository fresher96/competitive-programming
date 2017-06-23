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
#define fi first
#define se second
#define OO (1000000000)         // ToDo
#define EPS (1e-9)              // ToDo
#define MOD (1000000007)        // ToDo
#define all(v) ((v).begin()),((v).end())
#define WT(x) cout<< #x <<" = "<<"\""<< (x) <<"\""<<endl
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void read_file(bool outToFile = true) {
#ifdef LOCAL_TEST
    freopen("in", "rt", stdin);
    if (outToFile)
        freopen("out", "wt", stdout);
#endif
}
//
struct PushRelabel {
    // Adjacency list implementation of FIFO push relabel maximum flow
    // with the gap relabeling heuristic. This implementation is
    // significantly faster than straight Ford-Fulkerson. It solves
    // random problems with 10000 vertices and 1000000 edges in a few
    // seconds, though it is possible to construct test cases that
    // achieve the worst-case.
    //
    // Running time:
    // O(|V|^3)
    //
    // INPUT:
    // - graph, constructed using AddEdge()
    // - source
    // - sink
    //
    // OUTPUT:
    // - maximum flow value
    // - To obtain the actual flow values, look at all edges with
    // capacity > 0 (zero capacity edges are residual edges).
    
    // personal notes:
    // the capacity of an edge is stored in a 32-bit signed integer
    // the vertexes are 0-based indexed
    
    typedef long long LL;

    struct Edge {
        int from, to, cap, flow, index;
        
        Edge(int from, int to, int cap, int flow, int index) :
        from(from), to(to), cap(cap), flow(flow), index(index)
        {
        }
    };

    int N;
    vector < vector<Edge> > G;
    vector <LL> excess;
    vector <int> dist, active, count;
    queue <int> Q;

    PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2 * N)
    {
    }

    void AddEdge(int from, int to, int cap) {
        G[from].push_back( Edge(from, to, cap, 0, G[to].size()) );
        if (from == to) G[from].back().index++;
        G[to].push_back( Edge(to, from, 0, 0, G[from].size() - 1) );
    }

    void Enqueue(int v) {
        if (!active[v] && excess[v] > 0) {
            active[v] = true;
            Q.push(v);
        }
    }

    void Push(Edge & e) {
        int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
        if (dist[e.from] <= dist[e.to] || amt == 0) return;
        e.flow += amt;
        G[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
        Enqueue(e.to);
    }

    void Gap(int k) {
        for (int v = 0; v < N; v++)
        {
            if (dist[v] < k) continue;
            count[dist[v]]--;
            dist[v] = max(dist[v], N + 1);
            count[dist[v]]++;
            Enqueue(v);
        }
    }

    void Relabel(int v) {
        count[dist[v]]--;
        dist[v] = 2 * N;
        
        for (int i = 0; i < G[v].size(); i++)
            if (G[v][i].cap - G[v][i].flow > 0)
                dist[v] = min(dist[v], dist[G[v][i].to] + 1);
        
        count[dist[v]]++;
        Enqueue(v);
    }

    void Discharge(int v) {
        
        for (int i = 0; excess[v] > 0 && i < G[v].size(); i++)
            Push(G[v][i]);
        
        if (excess[v] > 0)
        {
            if (count[dist[v]] == 1)
                Gap(dist[v]);
            else
                Relabel(v);
        }
    }

    LL GetMaxFlow(int s, int t) {
        
        count[0] = N - 1;
        count[N] = 1;
        dist[s] = N;
        active[s] = active[t] = true;
        
        for (int i = 0; i < G[s].size(); i++)
        {
            excess[s] += G[s][i].cap;
            Push(G[s][i]);
        }
        
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            active[v] = false;
            Discharge(v);
        }
        
        LL totflow = 0;
        for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
        return totflow;
    }
};
//
int n, m;
//
int main()
{
    read_file();
    while(scanf("%d%d", &n, &m) != -1)
    {
        // n = the number of vertexes
        PushRelabel pr(n);
        
        for(int i=0; i<m; i++)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (a == b) continue;
            
            // adding directed edge from 'a-1' to 'b-1' with capacity c
            pr.AddEdge(a - 1, b - 1, c);
            
            // adding directed edge from 'b-1' to 'a-1' with capacity c
            pr.AddEdge(b - 1, a - 1, c);
        }
        
        // source = 0, sink = n-1
        printf("%lld\n", pr.GetMaxFlow(0, n - 1));
    }
}
// code source: Stanford notebook (2015-2016)
// problem: http://www.spoj.com/problems/FASTFLOW/
// description: given directed weighted graph with 'n' vertexes and 'm' edges
// find the maximum flow from node '1' to node 'n'
// vertexes are 1-base indexed
