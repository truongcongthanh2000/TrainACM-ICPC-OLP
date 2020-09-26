#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

#define INP "solve"
#define OUT "solve"

using namespace std;

const int INF = 1e9;
const int MOD = 11092019;
void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;

typedef pair<int, int> i2;

i2 IT[maxN * 4];
i2 Merge(i2 Left, i2 Right) {
    if (Left.first != Right.first) return max(Left, Right);
    return {Left.first, (Left.second + Right.second) % MOD};
}

vector<i2> version[maxN];
void update(int i, int L, int R, int u, int val, int num, int reset = 0) {
    if (L > u || R < u) return;
    if (L == R) {
        if (reset) {
            version[L].pop_back();
            IT[i] = version[L].back();
        }
        else {
            if (IT[i].first == val) IT[i].second += num;
            else IT[i] = i2(val, num);
            version[L].push_back(IT[i]);
        }
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, val, num, reset);
    update(i << 1 | 1, mid + 1, R, u, val, num, reset);
    IT[i] = Merge(IT[i << 1], IT[i << 1 | 1]);
}

i2 get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return {0, 1};
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    i2 Left = get(i << 1, L, mid, u, v);
    i2 Right = get(i << 1 | 1, mid + 1, R, u, v);
    return Merge(Left, Right);
}

vector<int> adj[maxN];
int u[maxN];
i2 res;
int F[maxN], nF[maxN];
int sz;
vector<i2> id[maxN];
void DFS(int u, int pa = 0) {
    i2 oldF = version[::u[u]].back();
    //cout << ::u[u] << " " << F[u] << " " << nF[u] << '\n';
    update(1, 0, sz - 1, ::u[u], F[u], nF[u]);
    if (res.first < F[u]) {
        res = {F[u], nF[u]};
    }
    else {
        if (res.first == F[u]) res.second = (res.second + nF[u]) % MOD;
    }
    for (int v : adj[u]) {
        i2 cost = get(1, 0, sz - 1, 0, ::u[v]);
        F[v] = cost.first + 1;
        if (F[v] == 1) nF[v] = 1;
        else nF[v] = cost.second;
        DFS(v, u);
    }
    update(1, 0, sz - 1, ::u[u], oldF.first, oldF.second, 1);
}

void sol() {
    int n;
    cin >> n;
    vector<int> nen;
    for (int i = 1; i <= n; i++) {
        cin >> u[i];
        nen.push_back(u[i]);
    }
    sort(nen.begin(), nen.end());
    nen.resize(unique(nen.begin(), nen.end()) - nen.begin());
    for (int i = 1; i <= n; i++) u[i] = lower_bound(nen.begin(), nen.end(), u[i]) - nen.begin();
    sz = (int)nen.size();
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    for (int i = 0; i < sz; i++) version[i].push_back({0, 0});
    F[1] = 1; nF[1] = 1;
    DFS(1);
    cout << res.first << " " << res.second;
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
