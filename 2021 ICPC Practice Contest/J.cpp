#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

bool match(vector<int> a, vector<int> b) {
    for (int i : a) {
        for (int j : b) {
            if (i == j) {
                return true;
            }
        }
    }
    return false;
}

void sol() {
    int n; cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> q[i];
    int start = 0;
    int res = 0;
    while (start < n) {
        if (start == n - 1) {
            res++;
            break;
        }
        vector<vector<int>> keys(4);
        keys[0] = {p[start], p[start + 1]};
        keys[1] = {q[start], p[start + 1]};
        keys[2] = {p[start], q[start + 1]};
        keys[3] = {q[start], q[start + 1]};
        map<vector<int>, int> cnt;
        for (int i = 0; i < 4; ++i) {
            for (int id = start + 2; id < n; ++id) {
                if (match(keys[i], {p[id], q[id]})) {
                    // cout << keys[i][0] << ' ' << keys[i][1] << ' ';
                    // cout << p[id] << ' ' << q[id] << '\n';
                    cnt[keys[i]]++;
                }
                else break;
            }
        }
        int mx = 0;
        for (auto it : cnt) mx = max(mx, it.second);
        // cout << start << ' ' << mx << '\n';
        res++;
        start = start + 2 + mx;
    }
    cout << res;
}

void solve() {
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
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
