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

struct Map {
    int mp[6][6];
    int dist;
    friend operator < (Map A, Map B) {
        for (int i = 0; i < 6; i++) {
             for (int j = 0; j < 6; j++) {
                if (A.mp[i][j] != B.mp[i][j]) {
                    return A.mp[i][j] < B.mp[i][j];
                }
             }
        }
        return A.mp[0][0] < B.mp[0][0];
    }
};

void sol() {
    Map old, nxt;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> old.mp[i][j];
        }
    }
    auto inSide = [&](int x, int y) {
        return x >= 0 && x < 6 && y >= 0 && y < 6;
    };
    old.dist = 0;
    queue<Map> Q;
    Q.push(old);
    set<Map> used;
    used.insert(old);
    while ((int)Q.size() != 0) {
        old = Q.front(); Q.pop();
        if (old.mp[2][5] == 1) {
            for (int i = 5; i >= 0 && old.dist <= 10 && old.mp[2][i] == 1; i--, old.dist++);
            if (old.dist > 10) cout << -1 << '\n';
            else cout << old.dist << '\n';
            return;
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (old.mp[i][j] == 0) {
                    for (int h = 0; h < 4; h++) {
                        int x = i + dx[h];
                        int y = j + dy[h];
                        if (!inSide(x, y) || old.mp[x][y] == 0) continue;
                        int xx = x + dx[h];
                        int yy = y + dy[h];
                        if (!inSide(x, y) || old.mp[xx][yy] != old.mp[x][y]) continue;
                        for (; inSide(xx, yy) && old.mp[xx][yy] == old.mp[x][y]; ) {
                            xx = xx + dx[h];
                            yy = yy + dy[h];
                        }
                        xx = xx - dx[h];
                        yy = yy - dy[h];
                        nxt = old;
                        nxt.dist++;
                        swap(nxt.mp[i][j], nxt.mp[xx][yy]);
                        if (nxt.dist <= 10 && used.find(nxt) == used.end()) {
                            used.insert(nxt);
                            Q.push(nxt);
                        }
                    }
                }
            }
        }
    }
    cout << -1 << '\n';
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
