#include <bits/stdc++.h>
using namespace std;

static unsigned long long splitmix64(unsigned long long x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x ^= (x >> 31);
    return x;
}

static inline void pos3(int a, int b, int B, int &p0, int &p1, int &p2) {
    if (a > b) swap(a, b);
    unsigned long long x = ((unsigned long long)(unsigned int)a << 32) ^ (unsigned long long)(unsigned int)b;
    unsigned long long h1 = splitmix64(x ^ 0x1234567890abcdefULL);
    unsigned long long h2 = splitmix64(x ^ 0xfedcba0987654321ULL) | 1ULL;
    unsigned long long mod = (unsigned long long)B;
    p0 = (int)(h1 % mod);
    p1 = (int)((h1 + h2) % mod);
    p2 = (int)((h1 + h2 + h2) % mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode;
    cin >> mode;

    if (mode == "prepare") {
        int n;
        cin >> n;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n + 1, 0), order;
        parent[1] = -1;
        vector<int> st;
        st.push_back(1);
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != 0) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }

        vector<vector<int>> children(n + 1);
        for (int v = 2; v <= n; ++v) children[parent[v]].push_back(v);

        vector<int> f0(n + 1, 0), f1(n + 1, 0), bestChild(n + 1, -1);

        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int u = order[i];
            int sum = 0;
            for (int v : children[u]) sum += f0[v];

            int bestGain = 0, bc = -1;
            for (int v : children[u]) {
                int gain = 1 + f1[v] - f0[v];
                if (gain > bestGain) {
                    bestGain = gain;
                    bc = v;
                }
            }
            f1[u] = sum;
            f0[u] = sum + bestGain;
            bestChild[u] = bc;
        }

        vector<char> matchedToParent(n + 1, 0);
        vector<pair<int,int>> stk;
        stk.push_back({1, 0});
        while (!stk.empty()) {
            auto [u, state] = stk.back();
            stk.pop_back();
            if (state == 1) {
                for (int v : children[u]) stk.push_back({v, 0});
            } else {
                int w = bestChild[u];
                if (w != -1) {
                    matchedToParent[w] = 1;
                    stk.push_back({w, 1});
                    for (int v : children[u]) if (v != w) stk.push_back({v, 0});
                } else {
                    for (int v : children[u]) stk.push_back({v, 0});
                }
            }
        }

        int B = n - 1;
        string bf(B, '0');
        for (int v = 2; v <= n; ++v) if (matchedToParent[v]) {
            int u = parent[v];
            int p0, p1, p2;
            pos3(u, v, B, p0, p1, p2);
            bf[p0] = '1';
            bf[p1] = '1';
            bf[p2] = '1';
        }

        cout << bf << "\n" << flush;
        return 0;
    }

    if (mode == "play") {
        int n;
        string bf;
        cin >> n >> bf;
        int B = n - 1;

        vector<char> used(n + 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            int take = 0;
            if (!used[u] && !used[v]) {
                int p0, p1, p2;
                pos3(u, v, B, p0, p1, p2);
                if (bf[p0] == '1' && bf[p1] == '1' && bf[p2] == '1') take = 1;
            }
            if (take) {
                used[u] = used[v] = 1;
                cout << "take\n" << flush;
            } else {
                cout << "ignore\n" << flush;
            }
        }
        return 0;
    }

    return 0;
}
