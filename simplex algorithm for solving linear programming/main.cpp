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
struct LPSolver {
    
    // Two-phase simplex algorithm for solving linear programs of the form
    //
    // maximize cˆT x
    // subject to Ax <= b
    // x >= 0
    //
    // INPUT: A -- an m * n matrix
    // b -- an m-dimensional vector
    // c -- an n-dimensional vector
    // x -- a vector where the optimal solution will be stored
    //
    // OUTPUT: value of the optimal solution (infinity if unbounded
    // above, nan if infeasible)
    //
    // To use this code, create an LPSolver object with A, b, and c as
    // arguments. Then, call Solve(x).
    
    // personal notes:
    // the average time complexity is believed to be O( n*m )
    // this algorithm usually runs fast in practice
    // memory complexity is O(n*m)
    // to invert ('max' to 'min') or ('<' to '>') multiply by '-1'
    
    typedef long double DOUBLE;
    typedef vector<DOUBLE> VD;
    typedef vector<VD> VVD;
    typedef vector<int> VI;
    
    int m, n;
    VI B, N;
    VVD D;

    LPSolver(const VVD &A, const VD &b, const VD & c) :
    m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2))
    {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++)
            D[i][j] = A[i][j];
        
        for (int i = 0; i < m; i++)
        {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++)
        {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void Pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++) if (i != r)
                for (int j = 0; j < n + 2; j++) if (j != s)
                        D[i][j] -= D[r][j] * D[i][s] / D[r][s];
                
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
        
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }

    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true)
        {
            int s = -1;
            for (int j = 0; j <= n; j++)
            {
                if (phase == 2 && N[j] == -1) continue;
                if ( s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] &&
                        N[j] < N[s] ) s = j;
            }
            
            if (D[x][s] > -EPS) return true;
            
            int r = -1;
            for (int i = 0; i < m; i++)
            {
                if (D[i][s] < EPS) continue;
                if ( r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                        (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) &&
                         B[i] < B[r] ) r = i;
            }
            
            if (r == -1) return false;
            Pivot(r, s);
        }
    }

    DOUBLE Solve(VD &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        
        if (D[r][n + 1] < -EPS)
        {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -EPS)
                return -numeric_limits<DOUBLE>::infinity();
            
            for (int i = 0; i < m; i++) if (B[i] == -1)
            {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if ( s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s]
                                && N[j] < N[s] ) s = j;
                    
                    Pivot(i, s);
                }
        }
        
        if (!Simplex(2))
            return numeric_limits<DOUBLE>::infinity();
        
        x = VD(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};
//
int main()
{
    read_file();
    
}
// code source: Stanford notebook (2015-2016)
