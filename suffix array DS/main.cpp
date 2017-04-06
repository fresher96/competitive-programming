#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <vii> vvii;
typedef vector <int> vi;
typedef vector <vi> vvi;
#define all(v) ((v).begin()),((v).end())
#define PB push_back
#define MP make_pair
#define OO (1000000000)
#define EPS (1e-9)
#define DEBUG(x) cout << #x << " = " <<"\""<< (x) <<"\""<<endl
void read_file(bool outToFile = true){
#ifdef LOCAL_TEST
    freopen("in.in", "rt", stdin);
    if(outToFile)
    freopen("out.out", "wt", stdout);
#endif
}
//
// n is the length of T
#define nMax 100000+1+1+9 // must be >= 256
char T[nMax];
int SA[nMax], tSA[nMax];
int RA[nMax], tRA[nMax];
int LCP[nMax], PLCP[nMax];
int CA[nMax], phi[nMax];
int n, K;
//
bool cmp(int a, int b){ // O( min( length(a), length(b) ) )
    return strcmp(T+a, T+b) < 0;
}
void construct_slow(){  // O(n^2 lgn)
    T[n++] = '$', T[n] = '\0';
    for(int i=0; i<n; i++)
        SA[i] = i;
    sort(SA, SA+n, cmp);
}
//
bool cmp1(int a, int b){
    ii l = MP(RA[a], a+K<n ? RA[a+K] : 0);
    ii r = MP(RA[b], b+K<n ? RA[b+K] : 0);
    return l < r;
}
void construct_mid(){   // O(n lg^2n)
    T[n++] = '$', T[n] = '\0';
    for(int i=0; i<n; i++)
        SA[i] = i, RA[i] = int(T[i]);
    
    for(int k=1; k<n; k*=2)
    {
        K = k;
        sort(SA, SA+n, cmp1);
        
        int r = 0;
        tRA[SA[0]] = r;
        for(int i=1; i<n; i++)
            tRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k])? r : ++r;
        
        for(int i=0; i<n; i++)
            RA[i] = tRA[i];
        
        if(RA[SA[n-1]] == n-1)
            break;
    }
}
//
void radix_sort(int k){ // O(n)
    int maxi = max(256, n);
    
    memset(CA, 0, sizeof CA);
    for(int i=0; i<n; i++)
        CA[i+k<n ? RA[i+k] : 0]++;
    
    for(int i=1; i<maxi; i++)
        CA[i] += CA[i-1];
    
    for(int i=n-1; i>=0; i--)
        tSA[ --CA[SA[i]+k<n ? RA[SA[i]+k] : 0] ] = SA[i];
        
    for(int i=0; i<n; i++)
        SA[i] = tSA[i];
}
void construct(){       // O(n lgn)
    T[n++] = '$', T[n] = '\0';
    for(int i=0; i<n; i++)
        SA[i] = i, RA[i] = int(T[i]);
    
    for(int k=1; k<n; k*=2)
    {
        radix_sort(k), radix_sort(0);
        
        int r = 0;
        tRA[SA[0]] = r;
        for(int i=1; i<n; i++)
            tRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k])? r : ++r;
        
        for(int i=0; i<n; i++)
            RA[i] = tRA[i];
        
        if(RA[SA[n-1]] == n-1)
            break;
    }
}
//
ii match(char *p, int m){  // O(m lgn)
    ii ret;
    int lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        int res = strncmp(T+SA[md], p, m);
        
        if(res >= 0)
            hi = md;
        else
            lo = md+1;
    }
    if(strncmp(T+SA[lo], p, m) != 0)
        lo = n;
    
    ret.first = lo;
    lo = 0, hi = n-1;
    while(lo != hi)
    {
        int md = (lo+hi)/2;
        int res = strncmp(T+SA[md], p, m);
        
        if(res <= 0)
            lo = md+1;
        else
            hi = md;
    }
    if(strncmp(T+SA[lo], p, m) <= 0)
        lo = n;
    
    ret.second = lo;
    return ret;
}
void LCP_slow(){
    LCP[0] = 0;
    for(int i=1; i<n; i++)
    {
        int L = 0;
        while(T[SA[i] + L] == T[SA[i-1] + L])
            L++;
        LCP[i] = L;
    }
}
void build_LCP(){ // longest common prefix in O(n)
    phi[SA[0]] = -1;
    for(int i=1; i<n; i++)
        phi[SA[i]] = SA[i-1];
    
    int L = 0;
    for(int i=0; i<n; i++)
    {
        if(phi[i] == -1)
            PLCP[i] = 0;
        else
        {
            while(T[i + L] == T[phi[i] + L])
                L++;
            PLCP[i] = L;
            L = max(L-1, 0);
        }
    }
    
    for(int i=0; i<n; i++)
        LCP[i] = PLCP[SA[i]];
}
int LRS(){ // longest repeated substring in O(n)
    int ret = 0;
    for(int i=1; i<n; i++)
        if(LCP[ret] < LCP[i])
            ret = i;
    return ret;
}
int owner(int x){
    return (x < K)? 1 : 2;
}
int LCS(){ // longest common substring in O(n)
    int ret = 0;
    for(int i=1; i<n; i++)
        if(owner(SA[i-1]) != owner(SA[i]) && LCP[ret] < LCP[i])
            ret = i;
    return ret;
}
void debug(){
    
    for(int i=0; i<n; i++)
        printf("%d \t %d \t %s\n", i, SA[i], T+SA[i]);
    
    for(int i=0; i<n; i++)
        ;//printf("%d \t %d \t %d \t %d \t %s\n", i, SA[i], LCP[i], owner(SA[i]), T+SA[i]);
    
    printf("\n");
}
//
void test1(){
    gets(T);
    n = strlen(T);
    construct();
    debug();
    
    int m;
    char p[100+1+9];
    while(gets(p))
    {
        m = strlen(p);
        ii pos = match(p, m);
        
        if(pos.second <= pos.first)
        {
            printf("%s was not found\n", p);
            continue;
        }
        
        printf("%s found in\n", p);
        for(int i=pos.first; i<pos.second; i++)
            printf("%d %s%c", SA[i], T+SA[i], "\t\n"[i == pos.second-1]);
    }
}
void test2(){
    while(gets(T))
    {
        n = strlen(T);
        construct();
        build_LCP();
        
        int idx = LRS();
        char lrs[100];
        strncpy(lrs, T+SA[idx], LCP[idx]);
        lrs[LCP[idx]] = '\0';
        
        DEBUG(lrs);
    }
}
void test3(){
    char T1[100+1+9], T2[100+1+9];
    int n1, n2;
    
    while(gets(T1) && gets(T2))
    {
        n1 = strlen(T1), n2 = strlen(T2);
        strcpy(T, T1), strcat(T, "@"), strcat(T, T2);
        n = n1 + 1 + n2, K = n1+1;
        construct();
        build_LCP();
        //DEBUG(T);
        //debug();
        
        int idx = LCS();
        char lcs[100];
        strncpy(lcs, T+SA[idx], LCP[idx]);
        lcs[LCP[idx]] = '\0';
        
        DEBUG(lcs);
    }
}
//
int main()
{
    // to solve a problem think about suffix tree
    // then convert it to a solution via suffix array
    read_file();
    
    //test1();
    test2();
    //test3();
}
