#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;

void prepare () {
	int n;
	cin >> n;

	vector < vector <int> > adj(n + 1);
	for (int i = 0; i < n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector <int> fa(n + 1, 0), ord;
	fa[1] = -1;
	{
		vector <int> st;
		st.push_back(1);
		while (!st.empty()) {
			int u = st.back(); st.pop_back();
			ord.push_back(u);
			for (auto v : adj[u]) {
				if (v == fa[u]) continue;
				if (fa[v] != 0) continue;
				fa[v] = u;
				st.push_back(v);
			}
		}
	}

	vector < vector <int> > ch(n + 1);
	for (int v = 2; v <= n; v ++) ch[fa[v]].push_back(v);

	vector <int> f0(n + 1, 0), f1(n + 1, 0), bch(n + 1, -1);

	for (int i = (int)ord.size() - 1; i >= 0; i --) {
		int u = ord[i];
		int sum = 0;
		for (auto v : ch[u]) sum += f0[v];

		int best = 0, bc = -1;
		for (auto v : ch[u]) {
			int gain = 1 + f1[v] - f0[v];
			if (gain > best) best = gain, bc = v;
		}
		f1[u] = sum;
		f0[u] = sum + best;
		bch[u] = bc;
	}

	vector <int> mfa(n + 1, 0);
	{
		vector <pii> st;
		st.push_back({1, 0});
		while (!st.empty()) {
			auto [u, state] = st.back(); st.pop_back();
			if (state == 1) {
				for (auto v : ch[u]) st.push_back({v, 0});
			} else {
				int w = bch[u];
				if (w != -1) {
					mfa[w] = 1;
					st.push_back({w, 1});
					for (auto v : ch[u]) if (v != w) st.push_back({v, 0});
				} else {
					for (auto v : ch[u]) st.push_back({v, 0});
				}
			}
		}
	}

	vector <int> c(n + 1, 0);
	for (int i = 1; i < (int)ord.size(); i ++) {
		int v = ord[i];
		c[v] = c[fa[v]] ^ mfa[v];
	}

	string s;
	for (int i = 2; i <= n; i ++) s.push_back(char('0' + c[i]));
	cout << s << '\n';
}

void play () {
	int n;
	string s;
	cin >> n >> s;

	vector <int> c(n + 1, 0);
	for (int i = 2; i <= n; i ++) c[i] = s[i - 2] - '0';

	vector <int> used(n + 1, 0);
	for (int i = 0; i < n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		if (c[u] != c[v] && !used[u] && !used[v]) {
			used[u] = used[v] = 1;
			cout << "take" << endl;
		} else {
			cout << "ignore" << endl;
		}
	}
}

int main () {
	ios::sync_with_stdio(false); cin.tie(0);

	string mode;
	cin >> mode;
	if (mode == "prepare") prepare();
	else play();
}
