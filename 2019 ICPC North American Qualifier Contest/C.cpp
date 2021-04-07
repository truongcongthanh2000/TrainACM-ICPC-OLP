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

const int maxN = 1e6 + 10;

int res[maxN][2];
void sol() {
    int n, D;
    cin >> n >> D;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int di;
        cin >> di;
        int a, b;
        cin >> a >> b;
        sum += a + b;
        res[di][0] += a;
        res[di][1] += b;
    }
    int suma = 0, sumb = 0;
    for (int i = 1; i <= D; i++) {
        int cost = (res[i][0] + res[i][1]) / 2;
        if (res[i][0] > res[i][1]) {
            cout << 'A' << ' ';
            res[i][0] = max(0, res[i][0] - cost - 1);
        }
        else {
            cout << 'B' << ' ';
            res[i][1] = max(0, res[i][1] - cost - 1);
        }
        cout << res[i][0] << " " << res[i][1] << '\n';
        suma += res[i][0];
        sumb += res[i][1];
    }
    cout << fixed << setprecision(10) << (long double)abs(suma - sumb) / sum;
}

void solve() {
    int T;
    //cin >> T;
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
