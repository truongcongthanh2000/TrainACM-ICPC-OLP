#pragma GCC diagnostic ignored "-Wunused-parameter"

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
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e2 + 10;
string RES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int n, m;
int numTreasure[maxN][maxN];
int numRock[maxN][maxN];
string res[maxN], old[maxN];

int typeFill(int x, int y, int size, int &d) {
    int u = x + size - 1;
    int v = y + size - 1;
    if (u > n || v > m) return 2;
    for (int i = x; i <= u; i++) {
        if (res[i][v] != '$' && res[i][v] != '.') return 2;
        if (res[i][v] == '$') {
            d++;
            if (d > 1) return 2;
        }
    }
    for (int i = y; i < v; i++) {
        if (res[u][i] != '$' && res[u][i] != '.') return 2;
        if (res[u][i] == '$') {
            d++;
            if (d > 1) return 2;
        }
    }
    return d == 1;
}

void fill(int x, int y, int size, char c) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[x + i][y + j] = c;
        }
    }
}

void reset(int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[x + i][y + j] = old[x + i][y + j];
        }
    }
}

bool canFill(int x, int y, int d) {
    while (x <= n) {
        if (res[x][y] != '$' && res[x][y] != '.') {
            y++;
            if (y > m) {
                y = 1;
                x++;
            }
        }
        else break;
    }
    if (x > n) return true;
    int size = 1;
    int num = 0;
    int old = 0;
    while (true) {
        int nxt = typeFill(x, y, size, num);
        if (nxt == 2) {
            size--;
            num = old;
            break;
        }
        old = num;
        if (nxt == 1) break;
        size++;
    }
    if (num == 0) return false;
    num = old;
    do {
        fill(x, y, size, RES[d]);
        int v = y + size;
        int u = x;
        if (v > m) {
            u++;
            v = 1;
        }
        if (canFill(u, v, d + 1)) return true;
        size++;
    } while (typeFill(x, y, size, num) == 1);
    reset(x, y, size - 1);
    return false;
}
void sol() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> old[i];
        old[i] = "#" + old[i];
        res[i] = old[i];
        for (int j = 1; j <= m; j++) {
            numTreasure[i][j] = numTreasure[i][j - 1] + numTreasure[i - 1][j] - numTreasure[i - 1][j - 1];
            numRock[i][j] = numRock[i][j - 1] + numRock[i - 1][j] - numRock[i - 1][j - 1];
            if (old[i][j] == '#') numRock[i][j]++;
            if (old[i][j] == '$') numTreasure[i][j]++;
        }
    }
    if (canFill(1, 1, 0) == false) cout << "elgnatcer";
    else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cout << res[i][j];
            cout << '\n';
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
