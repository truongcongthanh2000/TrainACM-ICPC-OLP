#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int p[maxN];
int find_root(int u) {
    if (p[u] == u) return u;
    return p[u] = find_root(p[u]);
}

void del(int u) {
    int v = find_root(u + 1);
    p[u] = v;
}

struct query {
    int i, k, a;
    char c;
    query(){};
};

query q[maxN];
void sol() {
    string s;
    cin >> s;
    int n = (int)s.size();
    int Q;
    cin >> Q;
    for (int i = 1; i <= Q; i++) cin >> q[i].i >> q[i].a >> q[i].k >> q[i].c;
    for (int i = 1; i <= n + 1; i++) p[i] = i;
    for (int id = Q; id >= 1; id--) {
        for (int i = q[id].i, a = q[id].a; i <= n && (i - q[id].i) / a <= q[id].k; i += a) {
            while (i <= n && (i - q[id].i) / a <= q[id].k && p[i] != i) {
                i = find_root(i);
                int remain = (a - (i - q[id].i) % a) % a;
                i += remain;
            }
            if (i > n || (i - q[id].i) / a > q[id].k) break;
            s[i - 1] = q[id].c;
            del(i);
        }
    }
    cout << s;
}

void solve() {
    int T;
    //cin >> T;
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
