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
#define nChild 26
struct trie{
    bool isLeaf;
    trie *child[nChild];       
    
    // to avoid the nChild factor in complexity
    // use a vector of chars to store active (non-Null) nodes
    
    // to save memory use map <int, trie*> mp;
    // ex. in case of having a long tree branch like
    // a -> b -> c -> d -> e -> ...
    // in each node we are using array with size nChild but only
    // using one of them
    
    
    trie(){                     
        isLeaf = false;
        for(int i=0; i<nChild; i++)
            child[i] = NULL;
    }
    
    ~trie(){
        // start from the root (ie. type: delete root;)
        // be sure root != NULL
        for(int i=0; i<nChild; i++)
            if(child[i])
                delete child[i];
    }
};
void insert(trie *cur, char *str){
    // O(length of the inserted string)
    
    if(!*str)
    {
        cur->isLeaf = true;
        return;
    }
    
    int idx = *str - 'a';
    if(!cur->child[idx])
        cur->child[idx] = new trie;
    insert(cur->child[idx], str+1);
}
bool search(trie *cur, char *str){
    // O(length of the searched-for string)
    
    if(!*str)
        return cur->isLeaf;
    
    int idx = *str - 'a';
    if(!cur->child[idx])
        return false;
    return search(cur->child[idx], str+1);
}
void init(trie *cur){
    // start from the root (ie. type: init(root);) and be sure root != NULL
    // either use delete root with the destructor
    // or use init() but you have to erase the destructor code
    for(int i=0; i<nChild; i++)
        if(cur->child[i])
            init(cur->child[i]);
    delete cur;
}
//
int main()
{
    read_file();
    
    trie *root = new trie;
    
    string s = "abcd";
    insert(root, (char*)s.c_str());
    insert(root, (char*)"xyz");
    insert(root, (char*)"abf");
    insert(root, (char*)"xn");
    insert(root, (char*)"ab");
    insert(root, (char*)"bcd");

    cout<<search(root, (char*)"xyz")<<"\n";
    cout<<search(root, (char*)"xy")<<"\n";
    cout<<search(root, (char*)"ab")<<"\n";
    cout<<search(root, (char*)"abc")<<"\n";
    cout<<search(root, (char*)"bcd")<<"\n";
    cout<<search(root, (char*)"axcd")<<"\n";
    
    delete root; // use this to avoid memory leak
}
