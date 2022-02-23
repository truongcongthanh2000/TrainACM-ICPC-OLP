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
    int n, m;
    cin >> m >> n;
    vector<string> s(n);
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }
    string T;
    cin >> T;
    int sz = (int)T.size();
    vector<int> dir(sz);
    for (int i = 0; i < sz; i++) {
        if (T[i] == 'N') dir[i] = 0;
        if (T[i] == 'S') dir[i] = 2;
        if (T[i] == 'E') dir[i] = 1;
        if (T[i] == 'W') dir[i] = 3;
    }
    vector<vector<int> > d(n, vector<int>(m, -1));
    {
        queue<pair<int, int> > Q;
        Q.push({x, y});
        d[x][y] = 0;
        for (; (int)Q.size() > 0; ) {
            int x = Q.front().first;
            int y = Q.front().second;
            Q.pop();
            for (int h = 0; h < 4; h++) {
                int u = x + dx[h];
                int v = y + dy[h];
                if (u >= 0 && u < n && v >= 0 && v < m && s[u][v] != '#' && d[u][v] == -1) {
                    d[u][v] = d[x][y] + 1;
                    Q.push({u, v});
                }
            }
        }
    }
    {
        vector<vector<int> > used(n, vector<int>(m, 0));
        vector<pair<int, int> > old;
        old.push_back({x, y});
        used[x][y] = 1;
        for (int i = 0; i < sz && (int)old.size() > 0; i++) {
            vector<pair<int, int> > nxt;
            for (auto it : old) {
                int x = it.first;
                int y = it.second;
                for (int h = 0; h < 4; h++) {
                    if (h == dir[i]) continue;
                    int u = x + dx[h];
                    int v = y + dy[h];
                    if (u >= 0 && u < n && v >= 0 && v < m && s[u][v] != '#' && d[x][y] + 1 == d[u][v] && used[u][v] == 0) {
                        used[u][v] = 1;
                        nxt.push_back({u, v});
                    }
                }
            }
            swap(old, nxt);
        }
        for (auto it : old) {
            int x = it.first;
            int y = it.second;
            s[x][y] = '!';
        }
    }
    for (int i = 0; i < n; i++) cout << s[i] << endl;
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
