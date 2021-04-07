#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
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

const int maxN = 5e5 + 1000;
vector<int> a[maxN];
int order[maxN * 10];
void sol(){
    int n;
    int t[6][6] = {{4,3,1,2,5,6},{3,4,2,1,5,6},{6,5,3,4,1,2},{5,6,3,4,2,1},{1,2,5,6,4,3},{1,2,6,5,3,4}};
    cin >> n;
    for(int i = 0; i < n; i++){
        a[i].assign(6,0);
        for(int j = 0; j < 6; j++)
            cin >> a[i][j];
    }
    auto hash = [&](vector<int> &a) {
        int res = 0;
        for (int x : a) res = res * 10 + x;
        return res;
    };
    auto genVector = [&](vector<int> a, int id) -> vector<int> {
        queue<vector<int> > Q;
        vector<int> res;
        Q.push(a);
        order[hash(a)] = id;
        while(!Q.empty()){
            vector<int> u = Q.front();
            res.push_back(hash(u));
            Q.pop();
            for(int i = 0; i < 6; i++){
                vector<int> v(6);
                for(int j = 0; j < 6; j++)
                    v[j] = u[t[i][j] - 1];
                if (order[hash(v)] != id) {
                    Q.push(v);
                    order[hash(v)] = id;
                }
            }
        }
        return res;
    };
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        vector<int> res = genVector(a[i], i + 1);
        for (int x : res) M[x]++;
    }
    int res = 0;
    for (auto it : M) res = max(res, it.second);
    cout << res;
}

void solve() {
    int T;
//    cin >> T;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
