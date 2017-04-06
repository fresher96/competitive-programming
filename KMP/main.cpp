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
typedef vector <int> vi;
#define PB push_back
#define all(v) v.begin(), v.end()
//
vi prefix_function(string pat){ // O(m)
    int m = pat.length();
    vi longestPrefix(m);
    
    int k = 0;
    longestPrefix[0] = 0;
    for(int i=1; i<m; i++)
    {
        while(k && pat[k] != pat[i])
            k = longestPrefix[k-1];
        
        if(pat[k] == pat[i])
            longestPrefix[i] = ++k;
        else
            longestPrefix[i] = k;
    }
    
    return longestPrefix;
    
    // prefix_function[i] = the longest post-prefix that is equal to
    // the suffix in the sub-string pat[0 ... i]
    
    // for example:
    // pat = "ababbaba"
    // prefix_function = {0, 0, 1, 2, 0, 1, 2, 3}
}
vi KMP(string str, string pat){ // O(n + m)
    // search for 'pat' in 'str'
    
    vi ret;
    int n = str.length();
    int m = pat.length();
    vi longestPrefix = prefix_function(pat);
    
    int k = 0;
    for(int i=0; i<n; i++)
    {
        // as long as we're failing go to the next best prefix
        while(k && pat[k] != str[i])
            k = longestPrefix[k-1];
        
        // match
        if(str[i] == pat[k])
            k++;
        
        // here k is the number of matched elements
        // i is the index of the last matched element
        // that is: pat[0 ... k-1] == str[i-k+1 ... i]
        
        
        // full match, move to the next match
        if(k == m)
            ret.PB(i-m+1), k = longestPrefix[k-1];
    }
    
    return ret;
    
    // we can substitute the use of KMP by only using the prefix fuction
    // calculate prefix function for 'ult' = pat + '@' + str
    // then for each 'i' in the range [m+1, ult.length()[
    // we will have prefix_function[i] = the maximum k such that
    // pat[0 ... k-1] == str[i-k+1 ... i]
}
vi prefix_frequency(string s){
    int n = s.length();
    vi frq(n+1, 0), pf = prefix_function(s);

    for(int i=0; i<n; i++)
        frq[pf[i]]++;

    for(int i=n-1; i>=2; i--)
        frq[pf[i-1]] += frq[i];

    frq.erase(frq.begin());
    for(int i=0; i<n; i++)  frq[i]++;

    return frq;
}
int count_unique_prefix(string s){
    int n = s.length();
    vi pf = prefix_function(s);
    vector <bool> vis(n, false);
    
    for(int i=0; i<n; i++)
    {
        int k = pf[i];
        if(k)   vis[k-1] = true;
    }
    return count(all(vis) , false);
}
int count_unique_substr(string s, int l){
    if(l == 0)  return 0;
    
    int ret = count_unique_prefix(s);
    s.erase(s.begin());
    ret += count_unique_substr(s, l-1);
    return ret;
}
//
void print(vi v, string s = ""){
    printf("%s\t", s.c_str() );
    int n = v.size();
    for(int i=0; i<n; i++)
        cout<< v[i] <<" \n"[i == n-1];
}
//
int main(){
    //read_file();
    // formula to find x,p such that x^p == s
    // if(n % (n-pf[n-1]) == 0) p = n / (n - pf[n-1])
    // else p = 1
    
}
