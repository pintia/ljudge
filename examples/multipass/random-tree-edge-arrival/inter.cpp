#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static int maxMatchingTreeSize(int n, const vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Root at 1
    vector<int> parent(n + 1, 0), order;
    order.reserve(n);
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

    // DP:
    // f1[u] = best in subtree(u) if edge (u,parent[u]) IS chosen (u matched to parent) => cannot match children
    // f0[u] = best in subtree(u) if edge (u,parent[u]) is NOT chosen
    vector<int> f0(n + 1, 0), f1(n + 1, 0);

    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        long long sumChildF0 = 0;
        int bestGain = 0;

        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            sumChildF0 += f0[v];
        }

        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            // choose edge (u,v):
            // gain over baseline sumChildF0 is 1 + f1[v] - f0[v]
            bestGain = max(bestGain, 1 + f1[v] - f0[v]);
        }

        f1[u] = (int)sumChildF0;
        f0[u] = (int)(sumChildF0 + max(0, bestGain));
    }

    return f0[1];
}

static bool isBinary(const string& s) {
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerInteraction(argc, argv);

    string mode = inf.readToken("(prepare)|(play)", "mode");
    inf.readEoln();

    if (mode == "prepare") {
        int n = inf.readInt(2, 500, "n");
        inf.readEoln();

        vector<pair<int,int>> edges;
        edges.reserve(n - 1);
        unsigned seed = n;
        for (int i = 0; i < n - 1; ++i) {
            int u = inf.readInt(1, n, "u");
            int v = inf.readInt(1, n, "v");
            inf.readEoln();
            // input guarantees u < v by statement/validator
            edges.push_back({u, v});
            seed = (seed ^ u) * 998 + v; 
        }

        vector<pair<int,int>> shuffled = edges;
        
        if (shuffled.size() == 2 && shuffled[0] == pair<int,int>(1, 2) && shuffled[1] == pair<int,int>(1, 3)) {
            // ensure to align with sample
            swap(shuffled[0], shuffled[1]);
        }
        // Now, the shuffled is decided even before reading participant's output.

        // as the edges are already permuted (in the gen stage), let's simply sort to hide the shuffle
        sort(edges.begin(), edges.end());
        
        
        // Use testlib's rnd to seed mt19937 deterministically.
        std::mt19937 rng(seed);
        shuffle(edges.begin(), edges.end(), rng);
        
        // Send to participant
        cout << "prepare\n";
        cout << n << "\n";
        for (auto [u, v] : edges) cout << u << " " << v << "\n";
        cout.flush();

        // Read assistant string s (must be length exactly n-1)
        string s = ouf.readToken("[01]{" + to_string(n - 1) + "," + to_string(n - 1) + "}", "s");
        if (!isBinary(s)) {
            quitf(_wa, "prepare: s must be binary");
        }
        if ((int)s.size() != n - 1) {
            quitf(_wa, "prepare: s must have length exactly n-1=%d, got %d", n - 1, (int)s.size());
        }
        // ouf.readEof();


        // write input to nextpass.in for the second run
        fstream tt;
        tt.open("feedback_dir/nextpass.in", ios_base::out);

        // Ensure endpoints remain u < v (they already are in edges, shuffle preserves that)
        // Write play-round input to tout
        tt << "play\n";
        tt << n << " " << s << "\n";
        for (auto [u, v] : shuffled) {
            if (u > v) swap(u, v);
            tt << u << " " << v << "\n";
        }
        tt.close();
        // avoid timing attack
        std::this_thread::sleep_for(std::chrono::milliseconds((uint32_t)rnd.next() % 123));
        quitf(_ok, "First pass completed successfully");
    }

    // ---------------- play ----------------
    int n = inf.readInt(2, 500, "n");
    string s = inf.readToken("[01]+", "s");
    inf.readEoln();

    if (!isBinary(s) || (int)s.size() != n - 1) {
        quitf(_fail, "Bad generated play input: s must be binary length n-1");
    }

    vector<pair<int,int>> edges;
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        edges.push_back({u, v});
    }

    int opt = maxMatchingTreeSize(n, edges);

    // Start interactive play
    cout << "play\n";
    cout << n << "\n" << s << "\n";
    cout.flush();

    vector<int> used(n + 1, 0);
    int taken = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u = edges[i].first, v = edges[i].second;

        cout << u << " " << v << "\n";
        cout.flush();

        string data = ouf.readToken("[a-zA-Z]{4,6}", "decision");
        
        std::transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c){ return std::tolower(c); });

        if (data == "take") {
            used[u] += 1;
            used[v] += 1;
            ++taken;
        } else if (data == "ignore") {
            // ok
        } else {
            quitf(_wa, "Unexpected word: %s", data.c_str());
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (used[i] > 1) {
            quitf(_wa, "Vectices %d used %d times", i, used[i]);
        }
    }

    if (taken != opt) {
        quitf(_wa, "Not maximum: taken=%d, optimum=%d", taken, opt);
    }

#ifndef DOMJUDGE
    tout << "ok |M|=" << taken << "\n";
#endif
    quitf(_ok, "ok |M|=%d", taken);
}
