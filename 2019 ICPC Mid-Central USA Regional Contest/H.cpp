#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-7;
const int BLOCK = 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

struct query {
    int L, R, id;
    query(){};
    bool operator < (const query &A) {
        if (L / BLOCK != A.L / BLOCK) {
            return L / BLOCK < A.L / BLOCK;
        }
        return R < A.R;
    }
};

int vl[maxN];
multiset<int> S;
map<int, int> deg;
void add(int x) {
    if (deg[x]) S.erase(S.find(deg[x]));
    deg[x]++;
    S.insert(deg[x]);
}

void del(int x) {
    S.erase(S.find(deg[x]));
    deg[x]--;
    if (deg[x]) S.insert(deg[x]);
}

query q[maxN];
string res[maxN];
void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (char c : s) {
            if (c == '.') continue;
            vl[i] = vl[i] * 10 + (c - '0');
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> q[i].L >> q[i].R;
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    int L = 1, R = 0;
    for (int i = 1; i <= m; i++) {
        while (R < q[i].R) add(vl[++R]);
        while (R > q[i].R) del(vl[R--]);
        while (L < q[i].L) del(vl[L++]);
        while (L > q[i].L) add(vl[--L]);
        int cost = *S.rbegin();
        if (cost >= (q[i].R - q[i].L + 1) / 2 + 1) res[q[i].id] = "usable";
        else res[q[i].id] = "unusable";
    }
    for (int i = 1; i <= m; i++) cout << res[i] << '\n';
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
