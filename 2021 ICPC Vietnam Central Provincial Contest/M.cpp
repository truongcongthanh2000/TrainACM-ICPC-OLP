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
vector<int> a[maxN];
int cha[maxN], node[maxN], p = 0;
long long f[maxN];

void DFS(int u){
    node[p]++;
    for(int v : a[u]){
        if (cha[v] == 0){
            cha[v] = u;
            DFS(v);
        }
    }
}

void sol() {
    int n, m;
    cin >> n >> m;
    vector<int> students;
    vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
        students.push_back(x[i]);
        students.push_back(y[i]);
    }
    sort(students.begin(), students.end());
    students.resize(unique(students.begin(), students.end()) - students.begin());
    for (int i = 0; i < m; i++) {
        x[i] = lower_bound(students.begin(), students.end(), x[i]) - students.begin() + 1;
        y[i] = lower_bound(students.begin(), students.end(), y[i]) - students.begin() + 1;
        a[x[i]].push_back(y[i]);
        a[y[i]].push_back(x[i]);
    }
    n = (int)students.size();
    p = 0;
    for(int i = 1; i <= n; i++){
        if (cha[i] == 0){
            cha[i] = -1;
            DFS(i);
            p++;
        }
    }

    f[0] = 1;
    for(int i = 1; i <= n; i++)
        f[i] = (f[i - 1] * i) % MOD;

    long long res = 0;
    for(int i = 0; i < p; i++){
        if (node[i] > 2)
            res = (res + f[node[i]]) % MOD;
    }
    cout << res << endl;
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
