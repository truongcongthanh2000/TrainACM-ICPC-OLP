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
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int d[maxN];
multiset<int> remain;

map<vector<int>, int> used;
vector<int> value;
vector<vector<int> > res;
int old_n;
bool Used[maxN];
void vet(int n) {
    vector<int> add = value;
    sort(add.begin(), add.end());
    if (used[add]) return;
    used[add] = 1;
    if (n == old_n) {
        res.push_back(add);
        return;
    }
    else {
        int mx = *remain.rbegin();
        for (int choose : {mx, value[1] - mx}) {
            if (choose < 0 || choose > 999 || Used[choose]) continue;
            bool ok = true;
            vector<int> del;
            for (int old : value) {
                int dist = abs(choose - old);
                if (remain.find(dist) == remain.end()) {
                    ok = false;
                    break;
                }
                del.push_back(dist);
                remain.erase(remain.find(dist));
            }
            if (ok) {
                value.push_back(choose);
                Used[choose] = true;
                vet(n + 1);
                value.pop_back();
                Used[choose] = false;
            }
            for (int rs : del) remain.insert(rs);
        }
    }
}
void sol() {
    int n;
    cin >> n;
    old_n = n;
    for (int i = 1; i <= n * (n - 1) / 2; i++) {
        cin >> d[i];
        remain.insert(d[i]);
    }
    value.push_back(0);
    Used[0] = true;
    Used[d[n * (n - 1) / 2]] = true;
    value.push_back(d[n * (n - 1) / 2]);
    remain.erase(remain.find(d[n * (n - 1) / 2]));
    vet(2);
    sort(res.begin(), res.end());
    cout << (int)res.size() << '\n';
    for (auto it : res) {
        for (int x : it) cout << x << ' ';
        cout << '\n';
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
