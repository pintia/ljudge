#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string round;
    cin >> round;

    if (round == "prepare") {
        int n;
        cin >> n;
        vector<pair<int, int>> edges;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            edges.emplace_back(u, v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // ---------- greedy maximum matching on tree ----------
        vector<int> deg(n + 1);
        for (int i = 1; i <= n; ++i) deg[i] = adj[i].size();
        vector<bool> matched(n + 1, false);
        queue<int> leaves;
        for (int i = 1; i <= n; ++i)
            if (deg[i] == 1) leaves.push(i);

        set<pair<int, int>> max_matching;  // stored with min(u,v), max(u,v)

        while (!leaves.empty()) {
            int v = leaves.front();
            leaves.pop();
            if (matched[v]) continue;

            int u = -1;
            for (int w : adj[v]) {
                if (!matched[w]) {
                    u = w;
                    break;
                }
            }
            if (u == -1) {
                matched[v] = true;  // v cannot be matched, remove it
                continue;
            }

            // match v and u
            max_matching.insert({min(v, u), max(v, u)});
            matched[v] = matched[u] = true;

            // decrease degree of neighbours of u (except v)
            for (int w : adj[u]) {
                if (w != v && !matched[w]) {
                    --deg[w];
                    if (deg[w] == 1) leaves.push(w);
                }
            }
        }

        // ---------- assign labels by DFS from vertex 1 ----------
        vector<int> label(n + 1, 0);
        vector<bool> visited(n + 1, false);
        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int nei : adj[node]) {
                if (!visited[nei]) {
                    int a = node, b = nei;
                    if (a > b) swap(a, b);
                    if (max_matching.count({a, b}))
                        label[nei] = 1 - label[node];
                    else
                        label[nei] = label[node];
                    dfs(nei);
                }
            }
        };
        dfs(1);

        // output the hint string s = label[2] ... label[n]
        string s;
        for (int i = 2; i <= n; ++i)
            s.push_back(char('0' + label[i]));
        cout << s << endl;
        cout.flush();

    } else {  // round == "play"
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> label(n + 1);
        label[1] = 0;
        for (int i = 2; i <= n; ++i)
            label[i] = s[i - 2] - '0';

        vector<bool> taken(n + 1, false);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            int bit = label[u] ^ label[v];
            if (bit == 1 && !taken[u] && !taken[v]) {
                cout << "take\n";
                taken[u] = taken[v] = true;
            } else {
                cout << "ignore\n";
            }
            cout.flush();
        }
    }

    return 0;
}