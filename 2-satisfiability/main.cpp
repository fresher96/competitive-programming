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
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in", "rt", stdin);
    if(outToFile)
    freopen("out", "wt", stdout);
#endif
}
//
struct TwoSat{
    
    // how to use:
    // 1) call init(n) to initiate an object with 'n' variables (0-base indexed)
    // let them be: X_0, X_1, ..., X_{n-1}
    // 2) use add_edge(i, j) to add the bracket (X_i || X_j)
    // use (other(i) = ~X_i) if needed in some brackets
    // 3) if solve() == 0, no solution exists
    // otherwise (val[i]) holds a possible solution for (X_i)
    
    // time complexity: O(n + m) where m is the number of brackets
    // memory complexity: O(n + m)
    
    
    #define maxn (100 * 1000 + 9)           // ToDo
    int n;
    vector <int> adj[maxn * 2];
    vector <int> adjrev[maxn * 2];
    int val[maxn];
    int marker, dfst, dfstime[maxn * 2], dfsorder[maxn * 2];
    int group[maxn * 2];

    inline int other(int v) {
        return v < n ? v + n : v - n;
    }
    inline int var(int v) {
        return v < n ? v : v - n;
    }
    inline int type(int v) {
        return v < n ? 1 : 0;
    }

    void init(int numberOfVariables){
        n = numberOfVariables;
        for (int i = 0; i < 2*numberOfVariables; i++)
        {
            adj[i].resize(0);
            adjrev[i].resize(0);
        }
    }

    void dfs(int v) {
        if (dfstime[v] != -1) return;
        dfstime[v] = -2;
        int deg = adjrev[v].size();
        for (int i = 0; i < deg; i++)
            dfs(adjrev[v][i]);
        dfstime[v] = dfst++;
    }

    void dfsn(int v) {
        if (group[v] != -1) return;
        group[v] = marker;
        int deg = adj[v].size();
        for (int i = 0; i < deg; i++)
            dfsn(adj[v][i]);
    }

    void add_edge(int a, int b) {
        adj[other(a)].push_back(b);
        adjrev[a].push_back(other(b));
        adj[other(b)].push_back(a);
        adjrev[b].push_back(other(a));
    }

    int solve() {
        dfst = 0;
        memset(dfstime, -1, sizeof dfstime);
        for (int i = 0; i < n + n; i++)
            dfs(i);
        memset(val, -1, sizeof val);
        for (int i = 0; i < n + n; i++)
            dfsorder[n + n - dfstime[i] - 1] = i;
        memset(group, -1, sizeof group);
        for (int i = 0; i < n + n; i++)
        {
            marker = i;
            dfsn(dfsorder[i]);
        }
        for (int i = 0; i < n; i++)
        {
            if (group[i] == group[i + n])
                return 0;
            val[i] = (group[i] > group[i + n]) ? 0 : 1;
        }
        return 1;
    }
};
//
const int MAXN = 2000+9;
int TC;
int n, m;
TwoSat graph;
//
int main()
{
    read_file();
    scanf("%d", &TC);
    while(TC--)
    {
        scanf("%d%d", &n, &m);
        
        // initialize with 'n' variables
        graph.init(n);
        
        // insert brackets
        for(int i=0; i<m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            
            // 0-base indexing
            u--, v--;
            
            // we need (u xor v) to be true for any (u, v)
            // so we add the brackets (u || v) && (~u || ~v)
            graph.add_edge(u, v);
            graph.add_edge( graph.other(u), graph.other(v) );
        }
        
        bool ok = graph.solve();
        
        static int mrk = 1;
        string ans = ok? "No suspicious bugs found!" : "Suspicious bugs found!";
        printf("Scenario #%d:\n", mrk++);
        printf("%s\n", ans.c_str());
    }
}
// code source: Ashley 1.2
// problem: http://www.spoj.com/problems/BUGLIFE/
