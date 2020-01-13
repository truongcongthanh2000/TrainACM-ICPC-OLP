#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6+5;

struct data{
    int x,y;
    data () {};
};

int n, m;
char c[2234][2234];
void doc() {
    //freopen("OB.inp","r",stdin);
    //freopen("OB.out","w",stdout);
    cin >> n >> m;
    string s;
    getline(cin,s);
    for (int i = 1; i <= n + 1; i++) {
        getline(cin,s);
        //if (i == 1) s += ' ';
        //cout << s;
        cerr << (int)s.size() << '\n';
        assert((int)s.size() == 2 * m + 1);
        for (int j = 1; j <= 2 * m + 1; j++) {
            c[i][j] = s[j - 1];
            //cerr << i << " " << j << " " << c[i][j] << '\n';
            //cout << c[i][j];
        }
        //getline(cin,s);
        //getchar();
    }
}
int D[maxN], b[maxN][22];
int KT[1234][1234][4];
vector <int> a[maxN];
void DFS(int u) {
    for (int i = 0; i <= 20; i++) {
        int v = b[u][i];
        if (v == 0) break;
        b[u][i + 1] = b[v][i];
    }
    for (int v : a[u]) {
        if (b[u][0] == v) continue;
        //cerr << u << " " << v << '\n';
        D[v] = D[u] + 1;
        b[v][0] = u;
        DFS(v);
    }
}
int LCA(int u, int v) {
    if (D[u] < D[v]) swap(u, v);
    int k = D[u] - D[v];
    for (int i = 20; i >= 0; i--) {
        if (k >= (1 << i)) {
            u = b[u][i];
            k -= (1 << i);
        }
    }
    if (u == v) return u;
    int Res = 0;
    for (int i = 20; i >= 0; i--) {
        if (b[u][i] != b[v][i]) {
            u = b[u][i];
            v = b[v][i];
        }
        else Res = b[u][i];
    }
    return Res;
}
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
void solve(){
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 4; k++) KT[i][j][k] = 1;
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= 2 * m + 1; j++) {
            if (c[i][j] == ' ') continue;
            if (c[i][j] == '|') {
                KT[i - 1][j / 2][1] = 0;
                KT[i - 1][(j + 1) / 2][3] = 0;
            }
            if (c[i][j] == '_') {
                KT[i - 1][j / 2][2] = 0;
                KT[i][j / 2][0] = 0;
            }
        }
    }
    //cerr << "OK" << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int u = (i - 1) * m + j;
            for (int k = 0; k < 4; k++) {
                if (KT[i][j][k] == 0) continue;
                int x = i + dx[k];
                int y = j + dy[k];
                //cout << i << " " << j << " " << x << " " << y << '\n';
                if (x == 0 || x == n + 1 || y == 0 || y == m + 1) continue;
                int v = (x - 1) * m + y;
                a[u].push_back(v);
            }
        }
    }
    DFS(1);
    int Q;
    cin >> Q;
    int x, y;
    cin >> x >> y;
    long long Res = 0;
    for (int i = 1; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        int S = (x - 1) * m + y;
        int T = (u - 1) * m + v;
        int Root = LCA(S, T);
        Res += D[S] + D[T] - 2 * D[Root];
        x = u;
        y = v;
    }
    cout << Res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
