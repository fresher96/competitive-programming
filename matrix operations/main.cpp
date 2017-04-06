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
inline void add(int &x, int v){
    x += v;
    if(x >= MOD) x -= MOD;
}
//
// these functions don't apply to empty matrices
const int matMax = 1000;
struct matrix{
    int n, m;
    int mat[matMax][matMax];
    
    matrix(){
        
    }
    
    matrix(int nn, int nm, int d=0){
        n = nn, m = nm;
        memset(mat, 0, sizeof mat);
        
        if(d)
        {
            for(int i=0; i<n; i++)
                mat[i][i] = d;
        }
    }
    
    matrix operator+ (const matrix &B) const{ // O(n*m)
        assert(n == B.n && m == B.m);

        matrix C = *this;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                add(C.mat[i][j], B.mat[i][j]);
        
        // optimization: you can add identity matrix in O(n)
        return C;
    }
    
    matrix operator* (const matrix &B) const{ // O(n*m*p)
        int p = B.m;
        assert(B.n == m);

        matrix C(n, p);
        for(int i=0; i<n; i++)
        {
            for(int k=0; k<m; k++)
            {
                if(mat[i][k] == 0) continue;
                
                for(int j=0; j<p; j++)
                    add(C.mat[i][j], 1LL * mat[i][k] * B.mat[k][j] %MOD);
            }
        }
        // you can swap the loops in any order
        // optimization: if A[i][k] = 0 || B[k][j] = 0
        // also swaping j, k is cache friendly
        
        return C;
    }
    
    matrix operator* (const int &a) const{ // O(n*m)
        matrix ret(n, m);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                ret.mat[i][j] = mat[i][j] * a;
        
        // fix ret for a correct modulo if needed
        return ret;
    }
};
//
matrix pow(matrix A, int n){ // O(A.n^3 lgn)
    // A must be square matrix
    if(n == 0)
        return matrix(A.n, A.n, 1);
    if(n&1)
        return A * pow(A, n-1);
    else
        return pow(A*A, n>>1);
}
matrix sum_of_powers(matrix A, int n){ // O(A.n^3 lgn)
    // A must be square matrix
    // return A^1 + A^2 + ... + A^n in O(A.n^3 lgn)
    if(n == 0)   return matrix(A.n, A.n);

    if(n&1)
        return A + A * sum_of_powers(A, n-1);
    
    matrix B = sum_of_powers(A, (n>>1) - 1);
    matrix C = A + A*B;
    matrix I = matrix(A.n, A.n, 1);
    B = B*-1;
    return C * (I + C + B);
}
//
int main()
{
    read_file();
    
}
