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

const int maxN = 2e6 + 10;

bool pre[maxN], suf[maxN];

int a[maxN];

void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    pre[0] = true;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= a[i - 1]) pre[i] = true;
        else break;
    }
    suf[n + 1] = true;
    a[n + 1] = INF;
    for (int i = n; i >= 1; i--) {
        if (a[i] <= a[i + 1]) suf[i] = true;
        else break;
    }
    for (int i = 1; i <= n; ) {
        if (pre[i - 1]) {
            if (suf[i + 1] && a[i] <= a[i + 1]) {
                cout << i << " " << i;
                return;
            }
            if (i == n) {
                cout << "impossible";
                return;
            }
            int j = i + 1;
            while (j <= n && a[j] <= a[j - 1]) {
                if (suf[j + 1] && a[j] >= a[i - 1] && a[i] <= a[j + 1]) {
                    cout << i << " " << j;
                    return;
                }
                j++;
            }
            i = j;
        }
        else i++;
    }
    cout << "impossible";
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
