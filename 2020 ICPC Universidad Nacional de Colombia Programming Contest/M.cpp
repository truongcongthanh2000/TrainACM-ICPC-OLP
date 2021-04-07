#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;

int nxt[maxN][26];

void sol() {
    string s;
    cin >> s;
    int sz = (int)s.size();
    for (int i = 0; i < 26; i++) nxt[sz][i] = sz + 1;
    for (int i = sz - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i] - 'a'] = i + 1;
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string a;
        cin >> a;
        string res;
        int root = 0;
        for (int i = 0; i < (int)a.size() && nxt[root][a[i] - 'a'] <= sz; i++) {
            res += a[i];
            root = nxt[root][a[i] - 'a'];
        }
        if (res == "") cout << "IMPOSSIBLE" << '\n';
        else cout << res << '\n';
    }
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
