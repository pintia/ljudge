#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
const int N = 1000;
int color[N][N];
mt19937 rng(70);
int rnd(int l, int r) {return uniform_int_distribution(l,r)(rng);}
#define all(x) begin(x),end(x)

/*
Try to make 600 random subsets, and hope not too many edges (a,b) cause an overlap.
There are way too many overlaps for this approach to work 
*/
int main() {
    vector<vector<int>> gs;
    int overlap=0;
    int iter=0;
    while(gs.size()<600) {
        vector<int> cands;
        for(int i=0;i<N;++i) {
            cands.push_back(i);
        }
        vector<int> cliq;
        iter++;
        while(cliq.size()<30 and cands.size()) {

            int nw = cands[rnd(0,int(cands.size())-1)];
            cliq.push_back(nw);
            cands.erase(find(all(cands),nw));
            // if(iter<=10000) cands.erase(partition(cands.begin(),cands.end(),[&](int i) {
            //     return !color[nw][i];
            // }),cands.end());
        }
        if(cliq.size()==30) {
            // cerr << gs.size() << '\n';
            for(auto i : cliq) for(auto j : cliq) {
                if(color[i][j]) overlap++;
                color[i][j]=gs.size();
            }
            gs.push_back(cliq);
        }
    }
    cerr<< overlap << '\n';
    string s; cin >> s;
    if(s=="send") {
        int k; cin >> k;
        k--;
        k%=gs.size();
        for(int i=0;i<30;++i) {
            cout << gs[k][i]+1;
            if(i<29) cout << ' ';
        }
        cout << '\n';
    } else {
        int a,b; cin >> a >> b;
        --a,--b;
        cout << color[a][b]+1 << '\n';
    }
}