#include<bits/stdc++.h>
#pragma GCC target("avx2")
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)size(x)
using namespace std;
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using pii = pair<ll, ll>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    vvi groups(601);
    rep(i,0,sz(groups)) {
        ll j = i / 31, k = i % 31;
        rep(l,0,31)
            groups[i].push_back((k + j * l) % 31 * 31 + l + 1);
    }
    rep(i,1,601) assert(sz(groups[i]) >= 30);
    vvi radj(1001);
    rep(i,0,sz(groups)) for (auto x : groups[i])
        radj[x].push_back(i);
    auto intersect = [&] (int a, int b) {
        vi c;
        set_intersection(all(radj[a]), all(radj[b]), back_inserter(c));
        return c;
    };
    //rep(i,0,1000) rep(j,0,i) assert(sz(intersect(i, j)) < 2);
    string cmd;
    cin >> cmd;
    if (cmd == "send") {
        ll k;
        cin >> k;
        rep(i,0,30) cout << groups[k][i] << ' ';
    } else {
        ll a, b;
        cin >> a >> b;
        cout << intersect(a, b)[0] << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    solve();

    return 0;
}
