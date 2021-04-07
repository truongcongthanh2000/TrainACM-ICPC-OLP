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
const int dx[6] = {0, 0, 1, -1, 1, -1};
const int dy[6] = {1, -1, 0, 0, 1, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e3 + 10;

map<pair<vector<vector<int> >, int>, int> dp;
map<pair<vector<vector<int> >, int>, int> used;

int a[10][10], pos[10][10];
pair<int, int> pPair[20];

long long F(int mask, int type, vector<vector<int> > a) {
    auto getBit = [&](int mask, int i) {
        return (mask >> i) & 1;
    };
    vector<int> bit1, bit0;
    for (int i = 0; i < 15; i++) {
        int bit = getBit(mask, i);
        if (bit) bit1.push_back(i);
        else bit0.push_back(i);
    }
    if (used[{a, type}]) return dp[{a, type}];
    used[{a, type}] = 1;
    auto cvPair = [&](int id) -> pair<int, int> {
        return pPair[id];
    };

    auto cvInt = [&](int x, int y) {
        return pos[x][y];
    };

    bool has = false;
    int &res = dp[{a, type}];
    for (int id : bit1) {
        pair<int, int> xy = cvPair(id);
        int x = xy.first;
        int y = xy.second;
        for (int h = 0; h < 6; h++) {
            vector<vector<int> > b = a;
            bool canChoose = true;
            int cost = 1;
            int next_mask = mask ^ (1 << id);
            int pre = 0;
            int u = x, v = y;
            for (int k = 0; k < 2; k++) {
                u += dx[h];
                v += dy[h];
                if (u >= 0 && u < 5 && v >= 0 && v <= u) {
                    int old = cvInt(u, v);
                    int bit = getBit(mask, old);
                    if (bit == 1) canChoose = false;
                    else {
                        cost *= b[u][v];
                        pre = b[u][v];
                        b[u][v] = 0;
                        next_mask ^= (1 << old);
                    }
                }
                else canChoose = false;
            }
            if (canChoose) {
                b[x][y] = pre;
                int nxtF = F(next_mask, type ^ 1, b);
                if (type) {
                    if (!has) res = nxtF + cost;
                    else res = max(res, nxtF + cost);
                    has = true;
                }
                else {
                    if (!has) res = nxtF - cost;
                    else res = min(res, nxtF - cost);
                    has = true;
                }
            }
        }
    }
    return res;
}
void sol() {
    int mask = 0;
    vector<vector<int> > a(5);
    for (int i = 0, id = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++, id++) {
            int x;
            cin >> x;
            a[i].push_back(x);
            pPair[id] = make_pair(i, j);
            pos[i][j] = id;
            if (a[i][j] == 0) mask ^= 1 << id;
        }
    }
    cout << F(mask, 1, a);
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
