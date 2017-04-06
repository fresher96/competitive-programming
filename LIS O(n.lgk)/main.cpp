#include <bits/stdc++.h>
using namespace std;
//
typedef vector <int> vi;
#define PB push_back
#define Max 50000
//
vi A, L, P, lis;
int ans, src;
int x;
//
int LIS_length() // O(n lgk) : k is the length of the lis sequence
{
    // returns the length of the longest strictly increasing subsequence
    L.PB(0);
    for(int i=1; i<A.size(); i++)
    {
        if(A[i] > A[L.back()])
            L.PB(i);
        else if(A[i] == A[L.back()])
            continue;
        else
        {
            int s, e, m;
            s = 0, e = L.size()-1;
            while(s != e)
            {
                m = (s+e)/2;
                if(A[i] > A[L[m]])
                    s = m+1;
                else
                    e = m;
            }
            if(A[i] < A[L[s]])
                L[s] = i;
        }
    }
    return L.size();
}
void LIS() // O(n lgk)
{
    // 'ans' will hold the length of the longest strictly increasing subsequence
    // 'src' will hold the index where it ends
    // we can recover the actual sequence using 'P'
    
    
    P.resize(A.size());
    ans = 1, src = 0;
    L.PB(0);    P[0] = -1;
    for(int i=1; i<A.size(); i++)
    {
        if(A[i] > A[L.back()])
        {
            P[i] = L.back();
            L.PB(i);
        }
        else if(A[i] == A[L.back()])
        {
            P[i] = P[L.back()];
            continue;
        }
        else
        {
            int s, e, m;
            s = 0, e = L.size()-1;
            while(s != e)
            {
                m = (s+e)/2;
                if(A[i] > A[L[m]])      s = m+1;
                else                    e = m;
            }
            if(A[i] < A[L[s]])
            {
                if(s > 0)       P[i] = L[s-1];
                else            P[i] = -1;
                L[s] = i;
            }
            else
                P[i] = P[L[s]];
        }
        if(ans < L.size())
            ans = L.size(), src = i;
    }
}
vi LIS_table(int p[Max]) // O(n lgk)
{
    // this function will return the sequence L of length n
    // such that:
    // L[i] = the longest increasing subsequence that ends at the i-th element
    // the same definition as the dp solutoion for the LIS problem
    
    // in this function 'lis' will hold the implicit LIS indexes
    // 'p' is the array of values
    // 'L' is what this function will return
    
    
    vi lis, L(A.size());
    lis.PB(0);
    L[0] = 1;
    for(int i=1; i<A.size(); i++)
    {
        if(p[i] > p[lis.back()] )
        {
            L[i] = L[lis.back()] + 1;
            lis.PB(i);
        }
        else if(p[i] == p[lis.back()] )
        {
            L[i] = L[lis.back()];
            continue;
        }
        else
        {
            int s, e, m;
            s = 0, e = lis.size()-1;
            while(s != e)
            {
                m = (s+e)/2;
                if(p[i] > p[ lis[m] ])
                    s = m+1;
                else
                    e = m;
            }
            L[i] = L[ lis[s] ];
            if(p[i] < p[ lis[s] ])
            {
                lis[s] = i;
            }
        }
    }
    return L;
}
//
void read_file()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "rt", stdin);
    freopen("out.out", "wt", stdout);
#endif
}
void init()
{
    A.clear();
    L.clear();
    P.clear();
}
void print_lis(int cur)
{
    if(P[cur] == -1)
    {
        printf("%d\n", A[cur]);
        return;
    }
    print_lis(P[cur]);
    printf("%d\n", A[cur]);
}
void build_lis(bool theFirst = 1)
{
    int cur;
    if(theFirst)
        cur = src;
    else
        cur = L.back();
    
    lis.resize(ans);
    int i = ans-1;
    while(cur != -1)
    {
        lis[i] = A[cur];
        i--;
        cur = P[cur];
    }
}
//
int main()
{
    read_file();
    init();
    while(scanf("%d", &x) != -1)
        A.PB(x);
    LIS();
    printf("length is %d\n\n", ans);
    print_lis(L.back()), printf("\n");
    print_lis(src), printf("\n");
    build_lis();
    for(int i=0; i<lis.size(); i++)
        printf("%d\n", lis[i]);
}
