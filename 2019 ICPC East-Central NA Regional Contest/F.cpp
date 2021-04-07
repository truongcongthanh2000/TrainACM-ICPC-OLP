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

const int maxN = 2e5 + 10;

int a[maxN];
int ok[maxN];
void sol() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int x = 0, len = n;
    while (len > 1) {
        int y = a[x] % len;
        y = (y + len - 1) % len;
        int d = 0;
        while (d < y) {
            if (ok[x]) {
                x = (x + 1) % n;
                continue;
            }
            d++;
            x = (x + 1) % n;
        }
        while (ok[x]) {
            x = (x + 1) % n;
        }
        ok[x] = 1;
        while (ok[x]) {
            x = (x + 1) % n;
        }
        len--;
    }
    cout << x + 1;
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
