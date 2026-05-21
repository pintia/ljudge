#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
const int N = 1000;
int color[N][N];
mt19937 rng(69);
int rnd(int l, int r) {return uniform_int_distribution(l,r)(rng);}
#define all(x) begin(x),end(x)

/*
Try to greedily construct some sets, such they don't have any overlapping pairs.
This does not find enough sets.
*/
int main() {
    vector<vector<int>> gs;
    for(int i=0;i<10000;++i) {
        vector<int> cands;
        for(int i=0;i<N;++i) {
            cands.push_back(i);
        }
        vector<int> cliq;
        while(cliq.size()<30 and cands.size()) {

            int nw = cands[rnd(0,int(cands.size())-1)];
            cliq.push_back(nw);
            cands.erase(find(all(cands),nw));
            cands.erase(partition(cands.begin(),cands.end(),[&](int i) {
                return !color[nw][i];
            }),cands.end());
        }
        if(cliq.size()==30) {
            // cerr << gs.size() << '\n';
            for(auto i : cliq) for(auto j : cliq) color[i][j]=gs.size()+1;
            gs.push_back(cliq);
        }
    }
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
        cout << color[a][b] << '\n';
    }
}