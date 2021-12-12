#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    string s;
    cin >> s;
    int n = (int)s.size();
    vector<vector<int> > nxt(n + 2, vector<int>(26, n + 1)), d(n + 2, vector<int>(26, -1));
    for (int i = 0; i < 26; i++) d[n][i] = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = nxt[i + 1][j];
            d[i][j] = d[i + 1][j];
        }
        nxt[i][s[i] - 'a'] = i + 1;
        d[i][s[i] - 'a']++;
    }
    vector<int> d2(26, 0);
    string t;
    cin >> t;
    for (char c : t) d2[c - 'a']++;
    auto ok = [&](int i, int c) {
        int ni = nxt[i][c];
        d2[c]--;
        bool ans = true;
        for (int i = 0; i < 26; i++) ans &= d[ni][i] >= d2[i];
        d2[c]++;
        return ans;
    };
    int cur = 0;
    string ans;
    for (int idx = 0; idx < (int)t.size(); idx++) {
        bool has = false;
        for (int c = 0; c < 26; c++) {
            if (d2[c] > 0 && ok(cur, c)) {
                cur = nxt[cur][c];
                has = true;
                ans += char(c + 'a');
                d2[c]--;
                break;
            }
        }
        if (!has) {
            cout << -1;
            return;
        }
    }
    cout << ans;
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
