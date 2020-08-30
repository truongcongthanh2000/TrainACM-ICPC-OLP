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

#define X first
#define Y second
const int maxN = 2e3 + 100;

const string DIRECT = "URLD";
string a[maxN];
typedef pair<int, int> ii;

ii p[maxN][maxN][4], c[maxN];
int h[maxN][maxN];
int dist[maxN][maxN];

int inv(int k){
    return 3 - k;
}

void TruyVet(int x, int y, string &res) {
    if (a[x][y] == 'E') return;
    for (int i = 3; i >= 0; i--) {
        int u = p[x][y][i].X;
        int v = p[x][y][i].Y;
        if (u != -1 && dist[u][v] == dist[x][y] - 1) {
            res += DIRECT[i];
            TruyVet(u, v, res);
            break;
        }
    }
}
void sol() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    ii Start, End;
    for(int i = 0; i < m; i++) c[i] = ii (-1, -1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            for(int k = 0; k < 4; k++) p[i][j][k] = ii(-1, -1);
            if (a[i][j] == 'S') Start = ii(i,j);
            if (a[i][j] == 'E') End = ii(i, j);
        }
    }
    for(int i = 0; i < n; i++){
        ii last = ii(-1, -1);
        for(int j = 0; j < m; j++){
            if (a[i][j] == 'X') continue;
            int x = c[j].X, y = c[j].Y;
            p[i][j][0] = c[j];
            if (x != -1)
                p[x][y][3] = ii(i, j);
            p[i][j][2] = last;
            if (last.X != -1)
                p[last.X][last.Y][1] = ii(i, j);
            last = c[j] = ii(i, j);
        }
    }

//    for(int i = 0; i < n; i++)
//    for(int j = 0; j < m; j++){
//        for(int k = 0; k < 4; k++)
//            cout << p[i][j][k].X << "-" << p[i][j][k].Y << "  /  ";
//        cout << '\n';
//    }


    queue<ii> que;
    que.push(End);
    memset(dist, -1, sizeof(dist));
    dist[End.X][End.Y] = 0;
    while(!que.empty()){
        ii u = que.front();
        que.pop();
        for(int k = 0; k < 4; k++){
            int x = p[u.X][u.Y][k].X;
            int y = p[u.X][u.Y][k].Y;
            if ( x == -1 || dist[x][y] != -1) continue;
            que.push(ii(x, y));
            h[x][y] = inv(k);
            dist[x][y] = dist[u.X][u.Y] + 1;
        }
    }

    if (dist[Start.X][Start.Y] != -1 ){
        string res;
        TruyVet(Start.X, Start.Y, res);
        cout << (int)res.size() << '\n';
        cout << res << '\n';
    }
    else cout << -1;
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
 
