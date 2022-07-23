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
    int m, n; cin >> m >> n;
    vector<int> arr(m + 1, 0);
    for (int i = 0; i < m; ++i) {
        cin >> arr[i];
    }
    vector<int> left(m + 1, 0), right(m + 1, 0);
    for (int i = 0; i < m; ++i) left[i + 1] = left[i] + arr[i];
    for (int i = m - 1; i >= 0; --i) right[i] = right[i + 1] + arr[i];
    while (n--) {
        bool ok = false;
        int q; cin >> q;
        for (int i = m; i >= 0; --i) {
            int id = lower_bound(left.begin(), left.end(), q - right[i]) - left.begin();
            if (id > i || left[id] != q - right[i]) continue;
            ok = true;
        }
        cout << (ok ? "Yes\n" : "No\n");
    }
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
