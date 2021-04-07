#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 10;

int M[maxN];
void sol() {
    string s, t;
    cin >> s >> t;
    if (s == t) {
        cout << 0;
        return;
    }
    queue<string> Q;

    auto hash = [&](string s) {
        int res = 0;
        for (char c : s) {
            res = res * 6 + (c - 'A' + 1);
        }
        return res;
    };

    auto add = [&](string s, int hs, int d) {
        Q.push(s);
        if (s == t) {
            cout << d - 1;
            exit(0);
        }
        M[hs] = d;
    };

    auto rot = [&](char c) {
        return char(((c - 'A' + 1) % 6) + 'A');
    };

    add(s, hash(s), 1);
    int d = 0;
    while ((int)Q.size() != 0) {
        string u = Q.front(); Q.pop();
        int hu = hash(u);
        for (int i = 0; i < 8; i++) {
            string v = u;
            if (u[i] == 'A') {
                for (int dx = -1; dx <= 1; dx += 2) {
                    if (i + dx >= 0 && i + dx < 8) v[i + dx] = rot(v[i + dx]);
                }
            }
            if (u[i] == 'B') {
                if (i == 0 || i == 7) continue;
                v[i + 1] = v[i - 1];
            }
            if (u[i] == 'C') {
                v[7 - i] = rot(v[7 - i]);
            }
            if (u[i] == 'D') {
                if (i <= 3) {
                    for (int j = 0; j < i; j++) v[j] = rot(v[j]);
                }
                else {
                    for (int j = i + 1; j < 8; j++) v[j] = rot(v[j]);
                }
            }
            if (u[i] == 'E') {
                if (i == 0 || i == 7) continue;
                int dist = min(i, 7 - i);
                for (int dx = -dist; dx <= dist; dx += 2 * dist) {
                    v[i + dx] = rot(v[i + dx]);
                }
            }
            if (u[i] == 'F') {
                int j = i + 1;
                if (j & 1) {
                    j = (j + 9) / 2;
                }
                else {
                    j = j / 2;
                }
                v[j - 1] = rot(v[j - 1]);
            }
            int hv = hash(v);
            if (M[hv] == 0) {
                add(v, hv, M[hu] + 1);
            }
        }
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
