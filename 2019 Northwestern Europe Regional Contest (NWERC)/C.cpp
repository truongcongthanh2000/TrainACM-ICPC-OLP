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

#define X first
#define Y second

const int maxN = 2e5 + 10;

typedef pair<int, int> i2;
typedef pair<long long, int> i2LL;
typedef pair<long long, i2> i3;
vector<i2> a;
map<int, int> d;

int cnt[maxN];

void sol() {
    int n, m;
    cin >> n;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
    }
    cin >> m;

    auto add = [&](int x) {
        d[x] = 1;
        for (int j = 0; j < n; j++) {
            if (x >= a[j].first && x <= a[j].second) cnt[j]++;
        }
    };
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        add(x);
    }
    vector<int> res;
    for(int i = 0; i < n; i++){
        if (cnt[i] > 2) {
            cout << "impossible";
            return;
        }
        else{
            if (cnt[i] == 1){
                int k;
                if (d[a[i].Y] == 0 && i < n - 1 && cnt[i + 1] < 2) k = a[i].Y;
                else {
                    k = a[i].Y - 1;
                    while (k >= a[i].X && d[k] == 1) k--;
                    if (k < a[i].X) {
                        cout << "impossible";
                        return;
                    }
                }
                add(k);
                res.push_back(k);
            }
            else {
                if (cnt[i] == 0){
                    int k = a[i].Y;
                    if (i < n - 1 && cnt[i + 1] == 2) {
                        k = a[i].Y - 1;
                        if (k <= a[i].X + 1) {
                            cout << "impossible";
                            return;
                        }
                    }
                    add(k);
                    add(k - 1);
                    res.push_back(k - 1);
                    res.push_back(k);

                }
            }
        }
    }

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << ' ';
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

