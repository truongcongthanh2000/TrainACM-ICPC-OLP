#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e3 + 100;
typedef pair<int, int> i2;

int n;
vector<int> d;
vector<vector<int> > a;

bool ok(int u, int u_s, int v, int v_s){
    vector<int> tu(n, 0);
    vector<int> tv(n, 0);
    for(int i = 0; i < n - 1; i++){
        int _tu = d[u_s] + a[u][u_s];
        int _tv = d[v_s] + a[v][v_s];
        int u_s_next = (u_s + 1) % n;
        int v_s_next = (v_s + 1) % n;
        tu[u_s_next] = tu[u_s] + _tu;
        tv[v_s_next] = tv[v_s] + _tv;
        u_s = u_s_next;
        v_s = v_s_next;
    }
    // for(int i = 0; i < n; i++){
    //     cout << tu[i] << ' ' << tv[i] << endl;
    // }
    for(int i = 0; i < n; i++){
        int u_l = tu[i];
        int u_r = tu[i] + a[u][i];
        int v_l = tv[i];
        int v_r = tv[i] + a[v][i];
        if (u_l >= v_l && u_l < v_r) return false;
        if (v_l >= u_l && v_l < u_r) return false;
    }
    return true;
}

vector<vector<bool> > check(int u, int v){
    vector<vector<bool> > c(n, vector<bool> (n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            c[i][j] = ok(u, i, v, j);
        }
    }
    return c;
}

void sol(){
    cin >> n;
    for(int i = 0; i < n;i++){
        int x;
        cin >> x;
        d.push_back(x);
    }
    for(int i = 0; i < 3; i++){
        vector<int> c;
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            c.push_back(x);
        }
        a.push_back(c);
    }


    vector<vector<bool> > d01 = check(0, 1);
    vector<vector<bool> > d12 = check(1, 2);
    vector<vector<bool> > d02 = check(0, 2);

    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    for(int k = 0; k < n; k++){
        if (i != j && j != k && d01[i][j] && d12[j][k] && d02[i][k]){
            cout << i + 1 << " " << j + 1 << " " << k + 1;
            return;
        }
    }
    cout << "impossible";

}


void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}