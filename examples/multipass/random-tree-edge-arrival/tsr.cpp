#include <bits/stdc++.h>
#define MAXN 500
using namespace std;

int n;

vector<int> e[MAXN + 5];
int f[MAXN + 5][2], from[MAXN + 5];
char s[MAXN + 5];

void dfs1(int sn, int fa) {
    int x = -1e9, y = 0;
    for (int fn : e[sn]) if (fn != fa) {
        dfs1(fn, sn);
        int mx = max(f[fn][0], f[fn][1]);
        f[sn][0] += mx; f[sn][1] += mx;
        int det = f[fn][0] - f[fn][1];
        if (det > x) x = det, y = fn;
    }

    if (x < 0) f[sn][1] += x;
    f[sn][1]++;
    from[sn] = y;
}

void dfs2(int sn, int fa, int col, int flag) {
    s[sn] = col + '0';
    for (int fn : e[sn]) if (fn != fa) {
        if (fn == from[sn] && flag == 1 && f[sn][1] > f[sn][0]) dfs2(fn, sn, col, 0);
        else dfs2(fn, sn, col ^ 1, 1);
    }
}

void prepare() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        e[x].push_back(y); e[y].push_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 0, 0, 1);
    printf("%s\n", s + 2); fflush(stdout);
}

void play() {
    scanf("%d%s", &n, s + 2);
    s[1] = '0';
    for (int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        if (s[x] == s[y]) printf("tAKe\n"), fflush(stdout);
        else printf("IgNOre\n"), fflush(stdout);
    }
}

int main() {
    char op[15]; scanf("%s", op);
    if (op[1] == 'r') prepare();
    else play();
    return 0;
}
