#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
 typedef pair<int, int> ii;
// typedef pair<int, ii> i2;

const int maxN = 1e5 + 5;
const long long INF_LL = 1e15;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 100;
const int dx[] = {-1, 0, 1, 0, -1, 1, -1, 1};
const int dy[] = {0, 1, 0, -1, -1, -1, 1, 1 };
const string direct = "URDL";

void doc(){
    #ifdef THEMIS
        freopen("OB.inp", "r", stdin);
        freopen("OB.out", "w", stdout);
    #endif // THEMIS
}


void solve(){
    int n, m;
    while(cin >> n >> m){
        if (n == 0 && m == 0) return;
        vector<string> s(n);
        for(int i = 0; i < n; i++) cin >> s[i];
//        if (s[0][0] == '#' || s[n - 1][m - 1] == '#'){
//            cout << 0 << '\n';
//            return;
//        }
        int ss = n * m, t = n * m + 1;
        auto out = [&](int i, int j){
            return m * i + j;
        };
        vector<vector<int>> a(n * m + 5);
        for(int i = 0; i < n; i++){
            int v = out(i, 0);
            if (s[i][0] != '@'){
                a[t].push_back(v);
                a[v].push_back(t);
            }
            v = out(i, m - 1);
            if (s[i][m - 1] != '@'){
                a[ss].push_back(v);
                a[v].push_back(ss);
            }
        }
        for(int j = 0; j < m; j++){
            int v = out(n - 1, j);
            if (s[n - 1][j] != '@'){
                a[t].push_back(v);
                a[v].push_back(t);
            }
            v = out(0, j);
            if (s[0][j] != '@'){
                a[ss].push_back(v);
                a[v].push_back(ss);
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if (s[i][j] == '@') continue;
                int u = out(i, j);
                for(int k = 0; k < 8; k++){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m && s[x][y] != '@'){
                        int v = out(x, y);
                        a[u].push_back(v);
                        a[v].push_back(u);
                    }
                }
            }
        }

        priority_queue<ii, vector<ii>, greater<ii> > heap;
        vector<int> d(t + 5);
        for(int i = 0; i <= t; i++) d[i] = INF;
        d[ss] = 0;
        heap.push(ii(d[ss], ss));
        while(!heap.empty()){
            int u = heap.top().Y;
            int du = heap.top().X;
//            cerr << u / n << ' ' << u % n << '\n';
            heap.pop();
            if (d[u] != du) continue;
            for(int v : a[u]){
                int x = v / m;
                int y = v % m;
                int cost;
                if (v == n * m || v == n * m + 1) cost = 0;
                else cost = s[x][y] == '.';
                if (d[v] > d[u] + cost){
                    d[v] = d[u] + cost;
                    heap.push(ii(d[v], v));
                }
            }
        }
        if (d[t] == INF) cout << -1 << '\n';
        else cout << d[t] << '\n';
    }
}

int main(){
    doc();
    solve();
}
